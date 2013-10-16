#include "hadoop_rpc.h"
#include "hadoop_rpc_utils.h"
#include "client_rm_protocol_impl.h"
#include "am_rm_protocol_impl.h"
#include "container_manager_impl.h"
#include "net_utils.h"
#include "pbc_utils.h"
#include "str_utils.h"
#include "hadoop_rpc_constants.h"

#include "ext/pbc/pbc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/* local variables */
bool is_env_initialize = false;
struct pbc_env* env;
const char* hadoop_version = NULL;

/******************
 * global methods *
 ******************/
hadoop_rpc_proxy_t* new_hadoop_rpc_proxy(
    const char* host,
    int port,
    hadoop_client_type_t client_type, 
    hadoop_server_type_t server_type) {
    int rc;

    // check initialize
    if (!check_init_and_print()) {
        return NULL;
    }

    // insanity check
    if (!host) {
        opal_output(0, "server cannot be null.\n");
        return NULL;
    }

    if ((server_type == NN) || (server_type == DN)) {
        opal_output(0, "not support such server type now.\n");
        return NULL;
    }

    hadoop_rpc_proxy_t* proxy =
        (hadoop_rpc_proxy_t*)malloc(sizeof(hadoop_rpc_proxy_t));
    proxy->caller_id = 0;
    proxy->client_type = client_type;
    proxy->server_type = server_type;
    proxy->app_attempt_id = 1; // start attempt id is "1"

    if (NM == proxy->server_type) {
        proxy->protocol_name = CONTAINER_MANAGER_PROTOCOL_NAME;
    } else if (RM == proxy->server_type) {
        if (CLIENT == proxy->client_type) {
            proxy->protocol_name = CLIENT_RM_PROTOCOL_NAME;
        } else if (AM == proxy->client_type) {
            proxy->protocol_name = AM_RM_PROTOCOL_NAME;
        }
    }

    // init socket for proxy, and connect to server
    proxy->socket_id = socket(AF_INET, SOCK_STREAM, 0);
    rc = connect_to_server(proxy->socket_id, host, port);

    if (rc != 0) {
        free(proxy);
        return NULL;
    }

    // write connection header to this socket
    rc = write_connection_header(proxy);
    if (rc != 0) {
        opal_output(0, "write connection header failed.\n");
        return NULL;
    }

    // succeed created
    proxy->app_id = -1;
    proxy->cluster_timestamp = -1;

    rc = pthread_mutex_init(&proxy->lock, NULL);
    if (rc != 0) {
        opal_output(0, "error when init lock for this proxy.\n");
        return NULL;
    }

    return proxy;
}

int init_pb_env(const char* pb_dir, const char* hd_version) {
    env = pbc_new();

    if (is_env_initialize) {
        opal_output(0, "env is already initialized.\n");
        return 0;
    }
    int pb_count = init_pbc_env_with_dir(pb_dir, env);
    if (pb_count <= 0) {
        opal_output(0, "initialize pb env failed.\n");
        return 1;
    }
    
    // initialize succeed
    is_env_initialize = true;
    if (NULL != hd_version) {
        int i;
        hadoop_version = strdup(hd_version);
        for (i = 0; i < strlen(hd_version); i++) {
            ((char*)hadoop_version)[i] = tolower(hd_version[i]);   
        }
        if ((strcmp(hadoop_version, APACHE_HADOOP_202_VER) == 0) || 
            (strcmp(hadoop_version, APACHE_HADOOP_203_VER) == 0)) {
            return 0;
        } else {
            opal_output(0, "unknown version given, %s.\n", hadoop_version);
            return -1;
        }
    }

    // by default, we using the latest version
    hadoop_version = APACHE_HADOOP_203_VER;
    return 0;
}

void destory_pb_env() {

}

/**
 * destory proxy
 */
void destory_hadoop_rpc_proxy(hadoop_rpc_proxy_t** pproxy) {
    hadoop_rpc_proxy_t* proxy = *pproxy;
    pthread_mutex_destroy(&proxy->lock);

    if ((proxy) && (proxy->socket_id >= 0)) {
        close(proxy->socket_id);
    }
    free(proxy);
    *pproxy = NULL;
}

/**
 * submit application to YARN-RM from client
 * return 0 if succeed, otherwise, it's failed
 */
int submit_application(
    hadoop_rpc_proxy_t* proxy, 
    submit_application_context_t* context) {
    int rc = get_new_app_impl(proxy);
    if (rc != 0) {
        opal_output(0, "get new application invoke failed.\n");
        return -1;
    }
    return 0;
}

/**
 * register app master, like register to RM, init proxy-app-id, etc.
 * return 0 if succeed, otherwise, it's failed
 */
int register_app_master(hadoop_rpc_proxy_t* proxy) {
    int rc = pthread_mutex_lock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to lock proxy failed in get_completed_containers.\n");
        return -1;
    }
    rc = register_app_master_impl(proxy);
    if (rc != 0) {
        pthread_mutex_unlock(&proxy->lock);
        opal_output(0, "register app master failed.\n");
        return -1;
    }
    rc = pthread_mutex_unlock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to unlock proxy failed in get_completed_containers.\n");
        return -1;
    }
    return 0;
}

/**
 * tell RM this app master is finished
 */
int finish_app_master(hadoop_rpc_proxy_t* proxy, 
    final_am_status_t status, 
    const char* diagnostics_msg) {
    int rc = pthread_mutex_lock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to lock proxy failed in get_completed_containers.\n");
        return -1;
    }
    rc = finish_app_master_impl(proxy, status, diagnostics_msg);
    if (rc != 0) {
        pthread_mutex_unlock(&proxy->lock);
        opal_output(0, "finish app master failed.\n");
        return -1;
    }
    rc = pthread_mutex_unlock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to unlock proxy failed in get_completed_containers.\n");
        return -1;
    }
    return 0;
}

/**
 * submit resource request to YARN-RM, and get response.
 * please free resouces of return value and context
 * return NULL if failed, otherwise, it's succeed
 *
 * if max_wait_time(in ms) <= 0, it will try to allocate 
 * resource forever, otherwise, it will failed of this 
 * allocation after max_wait_time exceeded.
 */
allocate_resource_response_t* allocate_resource(
    hadoop_rpc_proxy_t* proxy,
    allocate_resource_context_t* context,
    int max_wait_time) {
    int rc;
    rc = pthread_mutex_lock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to lock proxy failed in get_completed_containers.\n");
        return NULL;
    }
    allocate_resource_response_t* response = allocate_resource_impl(proxy, context, max_wait_time);
    rc = pthread_mutex_unlock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to unlock proxy failed in get_completed_containers.\n");
        return NULL;
    }
    if (!response) {
        opal_output(0, "allocate resource from RM failed.\n");
        return NULL;
    }
    return response;
}

int release_resource(hadoop_rpc_proxy_t* proxy,
   allocate_resource_context_t* context)
{
    int rc;
    allocate_resource_response_t * release_reponse;

    rc = pthread_mutex_lock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to lock proxy failed in release_resource.\n");
        return NULL;
    }

    release_reponse = release_resource_impl(proxy, context);
    rc = pthread_mutex_unlock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to unlock proxy failed in release_resource.\n");
        return NULL;
    }
    if (!release_reponse) {
        return -1;
    } else {
        destory_allocate_resource_response(release_reponse);
        return 0;
    }

    return release_reponse;
}

/**
 * get completed status, will return containers_status_array_t if succeed
 * otherwise, will return NULL
 */
containers_status_array_t* get_completed_containers(hadoop_rpc_proxy_t* proxy) {
    int rc;
    rc = pthread_mutex_lock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to lock proxy failed in get_completed_containers.\n");
        return NULL;
    }
    containers_status_array_t* ret = get_completed_containers_impl(proxy);
    rc = pthread_mutex_unlock(&proxy->lock);
    if (rc != 0) {
        opal_output(0, "try to unlock proxy failed in get_completed_containers.\n");
        return NULL;
    }
    return ret;
}

/**
 * query container state.
 * container is input parameter, state/retval/diag_msg is output param
 * when succeed, state will always be set, and retval/diag_msg will be
 * set when container completed. And 0 will be returned 
 * when failed, will return other value.
 */
int query_container_state(
    allocated_container_t* container,
    container_state_t* state, 
    int* retval,
    char** diag_msg) { 
    int rc = query_container_state_impl(container, state, retval, diag_msg);
    if (rc != 0) {
        opal_output(0, "launch failed.\n");
        return -1;
    }
    return 0;
}

/**
 * launch <launch_context> in specified container
 * return 0 if launch succeed
 * any other value if launch failed.
 */
int launch_containers(
   containers_launch_context_t* launch_context,
   allocated_container_t* container) {
    int rc = launch_containers_impl(launch_context, container);
    if (rc != 0) {
        opal_output(0, "launch failed.\n");
        return -1;
    }
    return 0;
}

/**
 * destory allocate_resource_response_t
 */
void destory_allocate_resource_response(allocate_resource_response_t* response) {
    int i;
    if (!response){
        return;
    }
    for (i = 0; i < response->num_containers; i++) {
        allocated_container_t* c = response->containers[i];
        if (c) {
            if (c->host) {
                free(c->host);
            }
            free(c);
        }
    }
    if (response->containers) {
        free(response->containers);
    }
    destory_container_status_array(response->completed_containers);
    free(response);
}

/*
 * destory container_status_array_t
 */
void destory_container_status_array(containers_status_array_t* array) {
    int i;
    if (!array) {
        return;
    }
    for (i = 0; i < array->num_containers; i++) {
        container_status_t* status = array->containers[i];
        if (status) {
            if (status->diagnostics_msg) {
                free(status->diagnostics_msg);
            }
            free(status);
        }
    }
    if (array->containers) {
        free(array->containers);
    }
    free(array);
}
