#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "hadoop_rpc.h"
#include "am_rm_protocol_impl.h"
#include "hadoop_rpc_constants.h"
#include "hadoop_rpc_utils.h"
#include "net_utils.h"
#include "ext/pbc/pbc.h"

static int response_id = 0;

/**
 * set release message
 */
static int set_release(struct pbc_wmessage *m,
        const char *release_key,
        hadoop_rpc_proxy_t* proxy,
        allocate_resource_context_t* context);

/**
 * generate register app master protobuf request
 */
static int generate_register_app_master_request(
        char** buffer,
        int* size,
        hadoop_rpc_proxy_t* proxy,
        const char* host,
        int port);

/**
 * generate finish app master protobuf request
 */
static int generate_finish_app_master_request(
        char** buffer,
        int* size,
        hadoop_rpc_proxy_t* proxy,
        final_am_status_t status,
        const char* diagnostics_msg);

/**
 * generate allocate resource request
 */
static int generate_allocate_resource_request(
    char** buffer,
    int* size,
    hadoop_rpc_proxy_t* proxy,
    allocate_resource_context_t* context);

/**
 * ask RM for resource allocation, return NULL when failed
 */
static allocate_resource_response_t* allocate_resource_once(
    hadoop_rpc_proxy_t* proxy,
    allocate_resource_context_t* context);

static void copy_allocated_container_t(allocated_container_t* tgt, const allocated_container_t* src) {
    tgt->container_id = src->container_id;
    tgt->port = src->port;
    tgt->host = strdup(src->host);
}

/* sort container by host name and port */
static void sort_container(allocated_container_t** containers, int num);

/* qsort container_t comparison function */ 
int container_comparer(const void *a, const void *b);

/**
 * submit resource request to YARN-RM, and get response.
 * return NULL if failed, otherwise, it's succeed
 *
 * if max_wait_time(in ms) <= 0, it will try to allocate 
 * resource forever, otherwise, it will failed of this 
 * allocation after max_wait_time exceeded.
 */
allocate_resource_response_t* allocate_resource_impl(
    hadoop_rpc_proxy_t* proxy,
    allocate_resource_context_t* context,
    int max_wait_time) {

    if (proxy->server_type != RM) {
        opal_output(0, "this proxy is not used for communicate with RM, please check.\n");
        return -1;
    }
    
    // check does proxy contains app-id info
    if ((proxy->app_id <= 0) || (proxy->cluster_timestamp <= 0)) {
        opal_output(0, "proxy doesn't contains any app info.\n");
        return NULL;
    }

    // check if other parameter valid
    if (context->resource_num <= 0) {
        opal_output(0, "request for slot number <= 0.\n");
        return NULL;
    }

    // allocate if user asked container number not satisfy
    allocate_resource_response_t* response = allocate_resource_once(proxy, context);
    if (!response) {
        opal_output(0, "Oops, something wrong happened during allocate.\n");
        return NULL;
    }

    /* sleep for a while avoid make YARN RM too busy */
    usleep(100 * 1000); 

    // sort container by host and port
    sort_container(response->containers, response->num_containers);

    return response;
}

/**
 * release containers via allocate_resource_once
 */
allocate_resource_response_t* release_resource_impl(hadoop_rpc_proxy_t* proxy,
        allocate_resource_context_t* context)
{
    if (proxy->server_type != RM) {
        opal_output(0, "this proxy is not used for communicate with RM, please check.\n");
        return -1;
    }

    // check does proxy contains app-id info
    if ((proxy->app_id <= 0) || (proxy->cluster_timestamp <= 0)) {
        opal_output(0, "proxy doesn't contains any app info.\n");
        return NULL;
    }

    /* release containers via 'allocate_resource_once' */
    allocate_resource_response_t* release_response = allocate_resource_once(proxy, context);

    if (!release_response) {
        opal_output(0, "Oops, something wrong happened during release_resource_impl.\n");
        return NULL;
    }

    return release_response;
}

/**
 * get completed status, will return containers_status_array_t if succeed
 * otherwise, will return NULL
 */
containers_status_array_t* get_completed_containers_impl(hadoop_rpc_proxy_t* proxy) {
    if (proxy->server_type != RM) {
        opal_output(0, "this proxy is not used for communicate with RM, please check.\n");
        return -1;
    }
    
    // check does proxy contains app-id info
    if ((proxy->app_id <= 0) || (proxy->cluster_timestamp <= 0)) {
        opal_output(0, "proxy doesn't contains any app info.\n");
        return NULL;
    }

    // create an empty allocate resource request
    allocate_resource_context_t ctx;
    ctx.resource_num = 0;
    ctx.release_containers.num_containers = 0;
    ctx.release_containers.containerid_array = NULL;

    // send this request and only return completed_containers_status_array
    allocate_resource_response_t* response = allocate_resource_once(proxy, &ctx);
    if (!response) {
        opal_output(0, "Oops, something wrong happened during allocate.\n");
        return NULL;
    }

    return response->completed_containers;
}

/**
 * implementation of register app master
 */
int register_app_master_impl(hadoop_rpc_proxy_t* proxy) {
    if (proxy->server_type != RM) {
        opal_output(0, "this proxy is not used for communicate with RM, please check.\n");
        return -1;
    }

    char* request = NULL;
    int request_len;
    int rc;

    // init app_id/cluster_timestamp from envar
    rc = init_app_id_from_env(proxy);
    if (rc != 0) {
        opal_output(0, "init app-id from env failed.\n");
        return -1;
    }

    /*****************************************************
     * first, we will submit register app master request *
     *****************************************************/

    // generate new_application_request
    char* localhost = get_local_hostname();
    if (!localhost) {
        opal_output(0, "get localhost failed.\n");
        return -1;
    }

    rc = generate_register_app_master_request(&request, &request_len, proxy, localhost, 8999);
    if (0 != rc) {
        free(localhost);
        opal_output(0, "generate register_app_master_request failed.\n");
        return -1;
    }
    free(localhost);

    // send request
    rc = send_rpc_request(proxy, request, request_len);
    if (0 != rc) {
        opal_output(0, "send register_app_master_request failed.\n");
        free(request);
        return -1;
    }

    // now we will not use it anymore
    free(request);
    struct pbc_slice slice;
    slice.buffer = NULL;
    slice.len = 0;

    // read response
    response_type_t response_type;
    response_type = recv_rpc_response(proxy, (char**)(&(slice.buffer)), &(slice.len));
    if (RESPONSE_SUCCEED == response_type) {
        // read response
        struct pbc_rmessage* rmsg = pbc_rmessage_new(env, "RegisterApplicationMasterResponseProto", &slice);
        if (!rmsg) {
            opal_output(0, "deserialize RegisterApplicationMasterResponseProto from buffer failed.\n");
            free(slice.buffer);
            return -1;
        }
        pbc_rmessage_delete(rmsg);
        free(slice.buffer);
        return 0;
    } else {
        process_bad_rpc_response(proxy, response_type);
        return -1;
    }
}

/**
 * implementation of finish app master
 */
int finish_app_master_impl(hadoop_rpc_proxy_t* proxy, final_am_status_t status, const char* diagnostics_msg) {
    if (proxy->server_type != RM) {
        opal_output(0, "this proxy is not used for communicate with RM, please check.\n");
        return -1;
    }

    if (proxy->app_id == -1) {
        /* if app_id not defined. report error */
        opal_output(0, "app id is not defined, please check.\n");
        return -1;
    }

    if (proxy->cluster_timestamp == -1) {
        /* if cluster ts not defined. report error */
        opal_output(0, "cluster time stamp is not defined, please check.\n");
        return -1;
    }

    char* request = NULL;
    int request_len;
    int rc;

    /*****************************************************
     * first, we will submit register app master request *
     *****************************************************/

    // generate new_application_request
    rc = generate_finish_app_master_request(&request, &request_len, proxy, status, diagnostics_msg);
    if (0 != rc) {
        opal_output(0, "generate finish_app_master_request failed.\n");
        return -1;
    }

    // send request
    rc = send_rpc_request(proxy, request, request_len);
    if (0 != rc) {
        opal_output(0, "send finish_app_master_request failed.\n");
        free(request);
        return -1;
    }

    // now we will not use it anymore
    free(request);
    struct pbc_slice slice;
    slice.len = 0;
    slice.buffer = NULL;

    // read response
    response_type_t response_type;
    response_type = recv_rpc_response(proxy, (char**)(&(slice.buffer)), &(slice.len));

    if (RESPONSE_SUCCEED == response_type) {
        // read response
        struct pbc_rmessage* rmsg = pbc_rmessage_new(env, "FinishApplicationMasterResponseProto", &slice);
        if (!rmsg) {
            opal_output(0, "deserialize FinishApplicationMasterResponseProto from buffer failed.\n");
            free(slice.buffer);
            return -1;
        }
        pbc_rmessage_delete(rmsg);
        free(slice.buffer);
        return 0;
    } else {
        process_bad_rpc_response(proxy, response_type);
        return -1;
    }
}

/*
 *  generate RegisterApplicationMasterRequestProto:
 *
 *  message RegisterApplicationMasterRequestProto {
 *    optional ApplicationAttemptIdProto application_attempt_id = 1;
 *    optional string host = 2;
 *    optional int32 rpc_port = 3;
 *    optional string tracking_url = 4;
 *  }
 */
static int generate_register_app_master_request(
        char** buffer,
        int* size,
        hadoop_rpc_proxy_t* proxy,
        const char* host,
        int port) {

    int rc;
    struct pbc_wmessage* register_request = pbc_wmessage_new(env, "RegisterApplicationMasterRequestProto");
    if (!register_request) {
        opal_output(0, "get RegisterApplicationMasterRequestProto message failed.\n");
        return -1;
    }

    /* pack host */
    rc = pbc_wmessage_string(register_request, "host", host, 0);
    if (rc != 0) {
        opal_output(0, "pack host failed. \n");
        pbc_wmessage_delete(register_request);
        return -1;
    }

    /* pack port */
    rc = pbc_wmessage_integer(register_request, "rpc_port", port, 0);
    if (rc != 0) {
        opal_output(0, "pack rpc_host failed. \n");
        pbc_wmessage_delete(register_request);
        return -1;
    }

    /* pack app_attempt */
    rc = set_app_attempt_id(register_request, "application_attempt_id", proxy);
    if (rc != 0) {
        opal_output(0, "pack app_id failed.\n");
        pbc_wmessage_delete(register_request);
        return -1;
    }

    struct pbc_slice slice;
    pbc_wmessage_buffer(register_request, &slice);

    /* try to create HadoopRpcRequestProto */
    rc = generate_hadoop_request((const char*)(slice.buffer),
        slice.len,
        AM_RM_PROTOCOL_NAME,
        REGISTER_APPLICATION_MASTER_METHOD_NAME,
        buffer,
        size);
    if (0 != rc) {
        opal_output(0, "create HadoopRpcRequestProto failed.\n");
        pbc_wmessage_delete(register_request);
        return -1;
    }

    pbc_wmessage_delete(register_request);
    return 0;
}

/*
 *  generate RegisterApplicationMasterRequestProto:
 *
 *  message FinishApplicationMasterRequestProto {
 *   optional ApplicationAttemptIdProto application_attempt_id = 1;
 *   optional string diagnostics = 2;
 *   optional string tracking_url = 3;
 *   optional FinalApplicationStatusProto final_application_status = 4;
 *  }
 *  
 *  enum FinalApplicationStatusProto {
 *   APP_UNDEFINED = 0;
 *   APP_SUCCEEDED = 1;
 *   APP_FAILED = 2;
 *   APP_KILLED = 3;
 *  }
 */
static int generate_finish_app_master_request(
        char** buffer,
        int* size,
        hadoop_rpc_proxy_t* proxy,
        final_am_status_t status,
        const char* diagnostics_msg) {

    int rc;
    struct pbc_wmessage* finish_request = pbc_wmessage_new(env, "FinishApplicationMasterRequestProto");
    if (!finish_request) {
        opal_output(0, "get FinishApplicationMasterRequestProto message failed.\n");
        return -1;
    }

    /* pack diagnostics_msg if have */
    if (diagnostics_msg) {
        rc = pbc_wmessage_string(finish_request, "diagnostics", diagnostics_msg, 0);
        if (rc != 0) {
            opal_output(0, "pack diagnostics failed. \n");
            pbc_wmessage_delete(finish_request);
            return -1;
        }
    }

    /* pack status */
    rc = pbc_wmessage_integer(finish_request, "final_application_status", status, 0);
    if (rc != 0) {
        opal_output(0, "pack final_application_status failed. \n");
        pbc_wmessage_delete(finish_request);
        return -1;
    }

    /* pack app_attempt */
    rc = set_app_attempt_id(finish_request, "application_attempt_id", proxy);
    if (rc != 0) {
        opal_output(0, "pack app_id failed.\n");
        pbc_wmessage_delete(finish_request);
        return -1;
    }

    struct pbc_slice slice;
    pbc_wmessage_buffer(finish_request, &slice);

    /* try to create HadoopRpcRequestProto */
    rc = generate_hadoop_request((const char*)(slice.buffer),
        slice.len,
        AM_RM_PROTOCOL_NAME,
        FINISH_APPLICATION_MASTER_METHOD_NAME,
        buffer,
        size);
    if (0 != rc) {
        opal_output(0, "create HadoopRpcRequestProto failed.\n");
        pbc_wmessage_delete(finish_request);
        return -1;
    }

    pbc_wmessage_delete(finish_request);
    return 0;
}

static allocate_resource_response_t* allocate_resource_once(
    hadoop_rpc_proxy_t* proxy,
    allocate_resource_context_t* context) {
    char* request = NULL;
    int request_len;
    int rc;
    int i;

    /*****************************************************
     * first, we will submit allocate_resource request *
     *****************************************************/

    // generate new_application_request
    rc = generate_allocate_resource_request(&request, &request_len, proxy, context);
    if (0 != rc) {
        opal_output(0, "generate allocate_resource_request failed.\n");
        return NULL;
    }
    response_id++;

    // send request
    rc = send_rpc_request(proxy, request, request_len);
    if (0 != rc) {
        opal_output(0, "send allocate_resource_request failed.\n");
        free(request);
        return NULL;
    }

    // now we will not use it anymore
    free(request);
    struct pbc_slice slice;
    slice.len = 0;
    slice.buffer = NULL;

    // read response
    response_type_t response_type;
    response_type = recv_rpc_response(proxy, (char**)(&(slice.buffer)), &(slice.len));

    if (RESPONSE_SUCCEED == response_type) {
        // read response
        /*
         *  message AllocateResponseProto {
         *   optional AMResponseProto AM_response = 1;
         *   optional int32 num_cluster_nodes = 2;
         *  }
         *
         *  message AMResponseProto {
         *   optional bool reboot = 1;
         *   optional int32 response_id = 2;
         *   repeated ContainerProto allocated_containers = 3;
         *   repeated ContainerStatusProto completed_container_statuses = 4;
         *   optional ResourceProto limit = 5;
         *   repeated NodeReportProto updated_nodes = 6;
         *  }
         *
         *  message ContainerProto {
         *    optional ContainerIdProto id = 1;
         *    optional NodeIdProto nodeId = 2;
         *    optional string node_http_address = 3;
         *    optional ResourceProto resource = 4;
         *    optional PriorityProto priority = 5;
         *    optional ContainerStateProto state = 6;
         *    optional hadoop.common.TokenProto container_token = 7;
         *    optional ContainerStatusProto container_status = 8;
         *  }
         */
        struct pbc_rmessage* rmsg = pbc_rmessage_new(env, "AllocateResponseProto", &slice);
        if (!rmsg) {
            opal_output(0, "deserialize AllocateResponseProto from buffer failed.\n");
            free(slice.buffer);
            return NULL;
        }

        /* get AMResponseProto */
        struct pbc_rmessage* am_response_msg = pbc_rmessage_message(rmsg, "AM_response", 0);
        if (!am_response_msg) {
            opal_output(0, "get AMResponseProto failed.\n");
            pbc_rmessage_delete(rmsg);
            return NULL;
        }

        /* we didn't get any container */
        int n_container = pbc_rmessage_size(am_response_msg, "allocated_containers");

        /* start parse container */
        allocate_resource_response_t* response =
            (allocate_resource_response_t*)malloc(sizeof(allocate_resource_response_t));
        response->num_containers = n_container;
        response->containers = NULL;

        if (n_container > 0) {
            response->containers = (allocated_container_t**)malloc(sizeof(allocated_container_t*) * n_container);
            for (i = 0; i < n_container; i++) {
                struct pbc_rmessage* container_msg = pbc_rmessage_message(
                    am_response_msg, "allocated_containers", i);
                if (!container_msg) {
                    opal_output(0, "get container from list failed.\n");
                    pbc_rmessage_delete(rmsg);
                    return NULL;
                }
                struct pbc_rmessage* container_id_msg = pbc_rmessage_message(container_msg, "id", 0);
                if (!container_id_msg) {
                    opal_output(0, "get container-id-msg failed\n");
                    pbc_rmessage_delete(rmsg);
                    return NULL;
                }
                int container_id = pbc_rmessage_integer(container_id_msg, "id", 0, NULL);
                struct pbc_rmssage* node_id_msg = pbc_rmessage_message(container_msg, "nodeId", 0);
                if (!node_id_msg) {
                    opal_output(0, "get node-id-msg failed.\n");
                    pbc_rmessage_delete(rmsg);
                    return NULL;
                }
                
                const char* host = pbc_rmessage_string(node_id_msg, "host", 0, NULL);
                if (!host) {
                    printf("get host from node-id-msg failed.\n");
                    pbc_rmessage_delete(rmsg);
                    return NULL;
                }
                int port = pbc_rmessage_integer(node_id_msg, "port", 0, NULL);

                /* now, we parsed all data we need, we will append this container to end of array */
                response->containers[i] = (allocated_container_t*)malloc(sizeof(allocated_container_t));
                allocated_container_t* container = response->containers[i];
                container->container_id = container_id;
                container->port = port;
                container->host = strdup(host);
            }
        }

        /* start parse completed containers */
        response->completed_containers = (containers_status_array_t*)malloc(sizeof(containers_status_array_t));
        containers_status_array_t* completed_containers = response->completed_containers;
        n_container = pbc_rmessage_size(am_response_msg, "completed_container_statuses");
        completed_containers->num_containers = n_container;

        if (n_container > 0) {
            completed_containers->containers = 
                (container_status_t**)malloc(sizeof(container_status_t*) * n_container);
            for (i = 0; i < n_container; i++) {
                struct pbc_rmessage* container_msg = pbc_rmessage_message(am_response_msg, "completed_container_statuses", i);
                if (!container_msg) {
                    opal_output(0, "get completed container status from list failed.\n");
                    pbc_rmessage_delete(rmsg);
                }
                struct pbc_rmessage* container_id_msg = pbc_rmessage_message(container_msg, "container_id", 0);
                if (!container_id_msg) {
                    opal_output(0, "get container-id-msg failed\n");
                    pbc_rmessage_delete(rmsg);
                }
                completed_containers->containers[i] = (container_status_t*)malloc(sizeof(container_status_t));
                completed_containers->containers[i]->container_id = pbc_rmessage_integer(container_id_msg, "id", 0, NULL);
                completed_containers->containers[i]->state = CONTAINER_COMPLETE;
                completed_containers->containers[i]->exit_status = pbc_rmessage_integer(container_msg, "exit_status", 0, NULL);
                completed_containers->containers[i]->diagnostics_msg = NULL; // abondon diag_msg
            }
        } else {
            // make it to NULL to keep a good style
            completed_containers->containers = NULL;
        }
        pbc_rmessage_delete(rmsg);
        free(slice.buffer);
        return response;
    } else {
        process_bad_rpc_response(proxy, response_type);
        return NULL;
    }
}

static int set_resource_request(struct pbc_wmessage* allocate_msg, const yarn_resource_t* resource_request) {
    int rc;
    if (!resource_request) {
        opal_output(0, "resource_request passed in is NULL");
        return -1;
    }

    /* get ask msg */
    struct pbc_wmessage* ask_msg = pbc_wmessage_message(allocate_msg, "ask");
    if (!ask_msg) {
        opal_output(0, "create ask_msg failed.\n");
        return -1;
    }

    /* set host_name to "*" */
    char* host;
    if (resource_request->host) {
        host = resource_request->host;
    } else {
        host = "*";
    }
    rc = pbc_wmessage_string(ask_msg, "host_name", host, 0);
    if (0 != rc) {
        opal_output(0, "serialize host_name to resource failed.\n");
        return -1;
    }

    /* set priority, simply make it = 0 */
    struct pbc_wmessage* priority_msg = pbc_wmessage_message(ask_msg, "priority");
    if (!priority_msg) {
        opal_output(0, "get priority_msg failed.\n");
        return -1;
    }
    rc = pbc_wmessage_integer(priority_msg, "priority", 20, NULL);
    if (0 != rc) {
        opal_output(0, "set priority failed.\n");
        return -1;
    }

    /* get resource msg */
    struct pbc_wmessage* resource_msg = pbc_wmessage_message(ask_msg, "capability");
    if (!resource_msg) {
        opal_output(0, "create ResourceRequestProto failed.\n");
        return -1;
    }

    /* set resource.memory */
    rc = pbc_wmessage_integer(resource_msg, "memory", resource_request->memory_per_slot, 0);
    if (rc != 0) {
        opal_output(0, "pack memory to resource failed.\n");
        return -1;
    }

    /* TODO, set cpu but need to check version */

    /* set num_containers */
    rc = pbc_wmessage_integer(ask_msg, "num_containers", resource_request->slot_num, 0);
    if (rc != 0) {
        opal_output(0, "pack container request number to ask failed.\n");
        return -1;
    }

    return 0;
}

/**
 * generate allocate resource request
 * message AllocateRequestProto {
 *   optional ApplicationAttemptIdProto application_attempt_id = 1;
 *   repeated ResourceRequestProto ask = 2;
 *   repeated ContainerIdProto release = 3;
 *   optional int32 response_id = 4;
 *   optional float progress = 5;
 * }
 *
 * message ResourceRequestProto {
 *   optional PriorityProto priority = 1;
 *   optional string host_name = 2;
 *   optional ResourceProto capability = 3;
 *   optional int32 num_containers = 4;
 * }
 *
 * message ResourceProto {
 *   optional int32 memory = 1;
 *   optional int32 virtual_cores = 2;
 * }
 */
static int generate_allocate_resource_request(
    char** buffer,
    int* size,
    hadoop_rpc_proxy_t* proxy,
    allocate_resource_context_t* context) {
    int rc, i;

    struct pbc_wmessage* allocate_msg = pbc_wmessage_new(env, "AllocateRequestProto");
    if (!allocate_msg) {
        opal_output(0, "create allocate resource msg failed.");
        return -1;
    }

    /* pack response_id */
    rc = pbc_wmessage_integer(allocate_msg, "response_id", response_id, NULL);
    if (rc != 0) {
        pbc_wmessage_delete(allocate_msg);
        opal_output(0, "pack response_id failed.\n");
        return -1;
    }

    rc = set_release(allocate_msg, "release", proxy, context);
    if (0 != rc) {
        pbc_wmessage_delete(allocate_msg);
        opal_output(0, "pack release failed.\n");
        return -1;
    }

    /* pack app id */
    rc = set_app_attempt_id(allocate_msg, "application_attempt_id", proxy);
    if (rc != 0) {
        pbc_wmessage_delete(allocate_msg);
        opal_output(0, "pack app_attempt_id failed.\n");
        return -1;
    }

    /* pack ask list */
    for (i = 0; i < context->resource_num; i++) {
        if (0 != (rc = set_resource_request(allocate_msg, &(context->resources[i])))) {
            opal_output(0, "pack resource to ask list failed.");
            pbc_wmessage_delete(allocate_msg);
            return -1;
        }
    }

    struct pbc_slice slice;
    pbc_wmessage_buffer(allocate_msg, &slice);

    /* try to create HadoopRpcRequestProto */
    rc = generate_hadoop_request((const char*)(slice.buffer),
        slice.len,
        AM_RM_PROTOCOL_NAME,
        ALLOCATE_RESOURCE_METHOD_NAME,
        buffer,
        size);
    if (0 != rc) {
        opal_output(0, "create HadoopRpcRequestProto failed.\n");
        pbc_wmessage_delete(allocate_msg);
        return -1;
    }

    pbc_wmessage_delete(allocate_msg);
    return 0;
}

int container_comparer(const void *a, const void *b) {
    const allocated_container_t* ia = *(const allocated_container_t**)a;
    const allocated_container_t* ib = *(const allocated_container_t**)b;
    
    int strcmp_ret = strcmp(ia->host, ib->host);
    if (strcmp_ret == 0) {
        return ia->port - ib->port;
    } else {
        return strcmp_ret;
    }
}

static void sort_container(allocated_container_t** containers, int num) {
    qsort(containers, num, sizeof(allocated_container_t*), container_comparer);
}

/*
message AllocateRequestProto {
   optional ApplicationAttemptIdProto application_attempt_id = 1;
   repeated ResourceRequestProto ask = 2;
   repeated ContainerIdProto release = 3;  //to be packed
   optional int32 response_id = 4;
   optional float progress = 5;
}

message ContainerIdProto {
  optional ApplicationIdProto app_id = 1;
  optional ApplicationAttemptIdProto app_attempt_id = 2;
  optional int32 id = 3;
}

message ApplicationIdProto {
  optional int32 id = 1;
  optional int64 cluster_timestamp = 2;
}

message ApplicationAttemptIdProto {
  optional ApplicationIdProto application_id = 1;
  optional int32 attemptId = 2;
}
 */
static int set_release(struct pbc_wmessage *m,
        const char *release_key,
        hadoop_rpc_proxy_t* proxy,
        allocate_resource_context_t* context)
{
    int i, rc;

    if (context->release_containers.num_containers == 0) {
        return 0;
    }

    for (i = 0; i < context->release_containers.num_containers; i++) {
        struct pbc_wmessage *release_msg = pbc_wmessage_message(m, release_key);
        if (!release_msg) {
            opal_output(0, "create release_msg failed.\n");
            return -1;
        }

        //pack 'id'
        rc = pbc_wmessage_integer(release_msg, "id", context->release_containers.containerid_array[i], 0);
        if (0 != rc) {
            opal_output(0, "pack container id in release_msg failed.\n");
            pbc_wmessage_delete(release_msg);
            return -1;
        }

        // pack 'app_attempt_id' via function 'set_app_attempt_id'
        rc = set_app_attempt_id(release_msg, "app_attempt_id", proxy);
        if (0 != rc) {
            opal_output(0, "pack app_attempt_id failed in release_msg\n");
            pbc_wmessage_delete(release_msg);
            return -1;
        }


        //pack 'app_id' via
        rc = set_app_id(release_msg, "app_id", proxy);
        if (0 != rc) {
            opal_output(0, "pack app_id failed in release_msg\n");
            pbc_wmessage_delete(release_msg);
            return -1;
        }
    }
    return 0;
}
