#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "hadoop_rpc.h"
#include "container_manager_impl.h"
#include "hadoop_rpc_constants.h"
#include "hadoop_rpc_utils.h"
#include "ext/pbc/pbc.h"
#include "str_utils.h"

/*
 * static global variables 
 */
const char* last_nm_host = NULL;
int last_nm_port = -1;
hadoop_rpc_proxy_t* cm_proxy = NULL;

/**
 * generate launch container PB request
 */
static int generate_launch_container_request(
        char** buffer,
        int* size,
        hadoop_rpc_proxy_t* proxy,
        int container_id,
        containers_launch_context_t* launch_context);

/**
 * launch a container
 */
static int launch_container_internal(hadoop_rpc_proxy_t* proxy,
    containers_launch_context_t* launch_context, 
    int container_id);

/**
 * query a container
 */
static int query_container_state_internal(hadoop_rpc_proxy_t* proxy, 
    int container_id,
    container_state_t* state,
    int* retval,
    char** diag_msg);

static int generate_query_container_state_request(
    char** buffer,
    int* size,
    hadoop_rpc_proxy_t* proxy,
    int container_id);

/*
 * check if current container's NM equals to last one, 
 * if no, create a new rpc cm_proxy and init it.
 */
static int refresh_cm_proxy(allocated_container_t* container) {
    if ((!last_nm_host) || (strcmp(last_nm_host, container->host) != 0) ||
        (last_nm_port == -1) || (last_nm_port != container->port)) {
        int rc;

        last_nm_host = container->host;
        last_nm_port = container->port;

        // release previous proxy if it's not NULL
        if (cm_proxy) {
            destory_hadoop_rpc_proxy(&cm_proxy);
        }

        // create new one
        cm_proxy = new_hadoop_rpc_proxy(last_nm_host, last_nm_port, AM, NM);
        if (!cm_proxy) {
            opal_output(0, "create cm_proxy for NM failed, host:%s, port:%d.\n", last_nm_host, last_nm_port);
            return -1;
        }
        rc = init_app_id_from_env(cm_proxy);
        if (rc != 0) {
            opal_output(0, "init app_id from env for cm_proxy failed.\n");
            return -1;
        }
    }
    return 0;
}

/**
 * query container state.
 * container is input parameter, state/retval/diag_msg is output param
 * when succeed, state will always be set, and retval/diag_msg will be
 * set when container completed. And 0 will be returned 
 * when failed, will return other value.
 */
int query_container_state_impl(
    allocated_container_t* container,
    container_state_t* state, 
    int* retval,
    char** diag_msg) {
    if (!container) {
        opal_output(0, "container is NULL, please check.\n");
        return -1;
    }

    int rc;
    rc = refresh_cm_proxy(container);
    if (rc != 0) {
        opal_output(0, "create proxy for container manager failed.\n");
        return -1;
    }

    rc = query_container_state_internal(cm_proxy, container->container_id, 
        state, retval, diag_msg);
    if (rc != 0) {
        opal_output(0, "query container state internal failed.\n");
        return -1;
    }

    return 0;
}

/**
 * launch <launch_context> in specified container
 * return 0 if launch succeed
 * any other value if launch failed.
 */
int launch_containers_impl(
    containers_launch_context_t* launch_context,
    allocated_container_t* container) {
    if (!container) {
        opal_output(0, "container is NULL, please check.\n");
        return -1;
    }

    if (!launch_context) {
        opal_output(0, "launch_context is NULL, please check");
        return -1;
    }

    int rc;
    rc = refresh_cm_proxy(container);
    if (rc != 0) {
        opal_output(0, "create proxy for container manager failed.\n");
        return -1;
    }

    rc = launch_container_internal(cm_proxy, launch_context, container->container_id);
    if (rc != 0) {
        opal_output(0, "launch container id=%d failed.\n", container->container_id);
        return -1;
    }

    return 0;
}

static int launch_container_internal(hadoop_rpc_proxy_t* proxy,
    containers_launch_context_t* launch_context, int container_id) {

    char* request = NULL;
    int request_len;
    int rc;

    rc = generate_launch_container_request(&request, &request_len, proxy, container_id, launch_context);
    if (0 != rc) {
        opal_output(0, "generate launch_container_request failed.\n");
        return -1;
    }

    // send request
    rc = send_rpc_request(proxy, request, request_len);
    if (0 != rc) {
        opal_output(0, "send launch_container_request failed.\n");
        free(request);
        return -1;
    }

    // now we will not use it anymore
    free(request);
    struct pbc_slice slice;

    // read response
    response_type_t response_type;
    response_type = recv_rpc_response(proxy, (char**)(&(slice.buffer)), &(slice.len));
    if (RESPONSE_SUCCEED == response_type) {
        // read response
        struct pbc_rmessage* rmsg = pbc_rmessage_new(env, "StartContainerResponseProto", &slice);
        if (!rmsg) {
            opal_output(0, "deserialize StartContainerResponseProto from buffer failed.\n");
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
 * launch a single container
 */
static int query_container_state_internal(hadoop_rpc_proxy_t* proxy, 
    int container_id,
    container_state_t* state,
    int* retval,
    char** diag_msg) {

    char* request = NULL;
    int request_len;
    int rc;

    rc = generate_query_container_state_request(&request, &request_len, proxy, container_id);
    if (0 != rc) {
        opal_output(0, "generate query_container_state_request failed.\n");
        return -1;
    }

    // send request
    rc = send_rpc_request(proxy, request, request_len);
    if (0 != rc) {
        opal_output(0, "send query_container_state_request failed.\n");
        free(request);
        return -1;
    }

    // now we will not use it anymore
    free(request);
    struct pbc_slice slice;

    // read response
    response_type_t response_type;
    response_type = recv_rpc_response(proxy, (char**)(&(slice.buffer)), &(slice.len));
    if (RESPONSE_SUCCEED == response_type) {
        // read response
        struct pbc_rmessage* rmsg = pbc_rmessage_new(env, "GetContainerStatusResponseProto", &slice);
        if (!rmsg) {
            opal_output(0, "deserialize GetContainerStatusResponseProto from buffer failed.\n");
            free(slice.buffer);
            return -1;
        }

        // get container status
        struct pbc_rmessage* status_msg = pbc_rmessage_message(rmsg, "status", 0);
        if (!status_msg) {
            opal_output(0, "get ContainerStatusProto from response failed.\n");
            return -1;
        }

        // read state
        *state = pbc_rmessage_integer(status_msg, "state", 0, NULL);
        *retval = pbc_rmessage_integer(status_msg, "exit_status", 0, NULL);

        pbc_rmessage_delete(rmsg);
        free(slice.buffer);
        return 0;
    } else {
        process_bad_rpc_response(proxy, response_type);
        return -1;
    }
}

/*
 * generate query container state request
 */
static int generate_query_container_state_request(
    char** buffer,
    int* size,
    hadoop_rpc_proxy_t* proxy,
    int container_id) {

    int rc;
    struct pbc_wmessage* req = pbc_wmessage_new(env, "GetContainerStatusRequestProto");
    if (!req) {
        opal_output(0, "get GetContainerStatusRequestProto message failed.\n");
        return -1;
    }

    // set container_id
    struct pbc_wmessage* id_proto = pbc_wmessage_message(req, "container_id");
    if (!id_proto) {
        opal_output(0, "get ContainerIdProto from ContainerLaunchContextProto failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }
    rc = pbc_wmessage_integer(id_proto, "id", container_id, NULL);
    if (0 != rc) {
        opal_output(0, "pack container-id failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }
    rc = set_app_attempt_id(id_proto, "app_attempt_id", proxy);
    if (0 != rc) {
        opal_output(0, "pack app_attempt_id failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }
    rc = set_app_id(id_proto, "app_id", proxy);
    if (0 != rc) {
        opal_output(0, "pack app_id failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }

    struct pbc_slice slice;
    pbc_wmessage_buffer(req, &slice);

    /* try to create HadoopRpcRequestProto */
    rc = generate_hadoop_request((const char*)(slice.buffer),
        slice.len,
        CONTAINER_MANAGER_PROTOCOL_NAME,
        GET_CONTAINER_STATUS_METHOD_NAME,
        buffer,
        size);
    if (0 != rc) {
        opal_output(0, "create HadoopRpcRequestProto failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }

    pbc_wmessage_delete(req);
    return 0;
}

static int pack_env_to_launch_ctx(const char* env_key, struct pbc_wmessage* ctx) {
    int rc;
    char* env_val = getenv(env_key);
    if (!env_val) {
        opal_output(0, "no %s set in environment.\n", env_key);
        return 0;
    }
    struct pbc_wmessage* env_msg = pbc_wmessage_message(ctx, "environment");
    if (!env_msg) {
        opal_output(0, "get env message from context failed.\n");
        return -1;
    }
    // pack key
    rc = pbc_wmessage_string(env_msg, "key", env_key, 0);
    if (rc != 0) {
        opal_output(0, "set key to environment failed.\n");
        return -1;
    }
    // pack val
    rc = pbc_wmessage_string(env_msg, "value", env_val, 0);
    if (rc != 0) {
        opal_output(0, "set value to environment failed.\n");
        return -1;
    }
    return 0;
}

/**
 * generate launch container PB request
     message ContainerLaunchContextProto {
      optional ContainerIdProto container_id = 1;
      optional string user = 2;
      optional ResourceProto resource = 3;
      repeated StringLocalResourceMapProto localResources = 4;
      optional bytes container_tokens = 5;
      repeated StringBytesMapProto service_data = 6;
      repeated StringStringMapProto environment = 7;
      repeated string command = 8;
      repeated ApplicationACLMapProto application_ACLs = 9;
    }

    message StartContainerRequestProto {
      optional ContainerLaunchContextProto container_launch_context = 1;
    }
 */
static int generate_launch_container_request(
        char** buffer,
        int* size,
        hadoop_rpc_proxy_t* proxy,
        int container_id,
        containers_launch_context_t* launch_context) {
    int rc;
    struct pbc_wmessage* req = pbc_wmessage_new(env, "StartContainerRequestProto");
    if (!req) {
        opal_output(0, "get StartContainerRequestProto message failed.\n");
        return -1;
    }

    struct pbc_wmessage* ctx = pbc_wmessage_message(req, "container_launch_context");
    if (!ctx) {
        opal_output(0, "get container_launch_context from StartContainerRequestProto failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }

    // set container_id
    struct pbc_wmessage* id_proto = pbc_wmessage_message(ctx, "container_id");
    if (!id_proto) {
        opal_output(0, "get ContainerIdProto from ContainerLaunchContextProto failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }
    rc = pbc_wmessage_integer(id_proto, "id", container_id, NULL);
    if (0 != rc) {
        opal_output(0, "pack container-id failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }
    rc = set_app_attempt_id(id_proto, "app_attempt_id", proxy);
    if (0 != rc) {
        opal_output(0, "pack app_attempt_id failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }
    rc = set_app_id(id_proto, "app_id", proxy);
    if (0 != rc) {
        opal_output(0, "pack app_id failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }

    // pack user
    rc = pbc_wmessage_string(ctx, "user", getlogin(), 0);
    if (rc != 0) {
        opal_output(0, "pack user name failed.\n");
        return -1;
    }

    // pack resource
    struct pbc_wmessage* res_msg = pbc_wmessage_message(ctx, "resource");
    if (!res_msg) {
        opal_output(0, "get resource_proto from context failed.\n");
        return -1;
    }
    rc = pbc_wmessage_integer(res_msg, "memory", launch_context->resource.memory_per_slot, NULL);
    if (rc != 0) {
        pbc_wmessage_delete(req);
        opal_output(0, "pack memory to resource failed.\n");
        return -1;
    }
    // TODO, in 2.0.3, need pack cpu

    // pack localResources
    rc = set_local_resources(ctx, "localResources");
    if (rc != 0) {
        pbc_wmessage_delete(req);
        opal_output(0, "pack local resources failed.\n");
        return -1;
    }

    // pack env
    int offset = 0;
    if (launch_context->env) {
        while (launch_context->env[offset]) {
            struct pbc_wmessage* env_msg = pbc_wmessage_message(ctx, "environment");
            if (!env_msg) {
                pbc_wmessage_delete(req);
                opal_output(0, "get env message from context failed.\n");
                return -1;
            }

            char* key = get_env_key(launch_context->env[offset]);
            char* val = get_env_val(launch_context->env[offset]);
            if ((!key) || (!val)) {
                if (key) {
                    free(key);
                }
                if (val) {
                    free(val);
                }
                pbc_wmessage_delete(req);
                opal_output(0, "get env key or value failed, env=%s.\n", launch_context->env[offset]);
                return -1;
            }

            // pack key
            rc = pbc_wmessage_string(env_msg, "key", key, 0);
            free(key);
            if (rc != 0) {
                free(val);
                pbc_wmessage_delete(req);
                opal_output(0, "set key to environment failed.\n");
                return -1;
            }
            // pack val
            rc = pbc_wmessage_string(env_msg, "value", val, 0);
            if (rc != 0) {
                free(val);
                pbc_wmessage_delete(req);
                opal_output(0, "set value to environment failed.\n");
                return -1;
            }
            free(val);
            offset++;
        }
    }

    // pack $PATH, $LD_LIBRARY_PATH, $DYLD_LIBRARY_PATH, $CLASSPATH to env
    if (0 != (rc = pack_env_to_launch_ctx("PATH", ctx))) {
        pbc_wmessage_delete(req);
        return -1;
    }
    if (0 != (rc = pack_env_to_launch_ctx("LD_LIBRARY_PATH", ctx))) {
        pbc_wmessage_delete(req);
        return -1;
    }
    if (0 != (rc = pack_env_to_launch_ctx("DYLD_LIBRARY_PATH", ctx))) {
        pbc_wmessage_delete(req);
        return -1;
    }
    if (0 != (rc = pack_env_to_launch_ctx("CLASSPATH", ctx))) {
        pbc_wmessage_delete(req);
        return -1;
    }

    // pack command
    char* command = concat_argv_to_cmd(launch_context->argv);
    if (!command) {
        pbc_wmessage_delete(req);
        opal_output(0, "concat argv to command to command failed. argv[0]:%s.\n", launch_context->argv[0]);
        return -1;
    }
    rc = pbc_wmessage_string(ctx, "command", command, 0);
    free(command);
    if (rc != 0) {
        opal_output(0, "pack command to context failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }

    struct pbc_slice slice;
    pbc_wmessage_buffer(req, &slice);

    /* try to create HadoopRpcRequestProto */
    rc = generate_hadoop_request((const char*)(slice.buffer),
        slice.len,
        CONTAINER_MANAGER_PROTOCOL_NAME,
        START_CONTAINER_METHOD_NAME,
        buffer,
        size);
    if (0 != rc) {
        opal_output(0, "create HadoopRpcRequestProto failed.\n");
        pbc_wmessage_delete(req);
        return -1;
    }

    pbc_wmessage_delete(req);
    return 0;
}
