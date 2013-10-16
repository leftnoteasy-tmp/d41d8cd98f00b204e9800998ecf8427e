#ifndef _HD_CLIENT_HADOOP_RPC_H
#define _HD_CLIENT_HADOOP_RPC_H

#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#include "opal/util/output.h"

extern struct pbc_env* env;
extern bool is_env_initialize;
extern const char* hadoop_version;

/**
 * type of PB server
 */
typedef enum { 
    NM, // Node Mgr
    RM, // Resource Mgr
    NN, // NameNode, not used now
    DN  // DataNode, not used now
} hadoop_server_type_t;

/**
 * type of PB client
 */
typedef enum {
    CLIENT, // Client 
    AM      // App Master
} hadoop_client_type_t;

/**
 * allocated resource define of AM requested from RM
 */
typedef struct {
    int container_id;
    char* host;
    int port;
} allocated_container_t;

/*
 * enum for container state
 */
typedef enum {
    /** New container */
    CONTAINER_NEW = 1, 

    /** Running container */
    CONTAINER_RUNNING = 2, 

    /** Completed container */
    CONTAINER_COMPLETE = 3
} container_state_t;

/*
 * type for container status
 */
typedef struct {
    container_state_t state;
    int container_id;
    int exit_status;
    char* diagnostics_msg;
} container_status_t;

/*
 * completed containers
 */
typedef struct {
    container_status_t** containers;
    int num_containers;
} containers_status_array_t;

/**
 * resource define for a single slot
 */
typedef struct {
    int memory_per_slot;
    int cpu_per_slot;
    int slot_num;
    char* host;
} yarn_resource_t;

/**
 * containerid array to be released
 */
typedef struct {
    int *containerid_array;
    int num_containers;
} release_containerid_array_t;

/**
 * allocate resource context in AM request RM resources
 */
typedef struct {
    /* number of resources */
    int resource_num;
    yarn_resource_t* resources; // array of yarn_resource_t
    release_containerid_array_t release_containers;
} allocate_resource_context_t;

/**
 * allocated response include list of allocated containers
 */
typedef struct {
    allocated_container_t** containers;
    int num_containers;
    containers_status_array_t* completed_containers;
} allocate_resource_response_t;

/**
 * struct define of PB proxy client
 */
typedef struct {
    int caller_id;                     /* caller-id, assume user shouldn't access this */
    hadoop_client_type_t client_type;  /* client type */
    hadoop_server_type_t server_type;  /* server type */
    int socket_id;                     /* socket-id, assume user shouldn't access this */
    const char* protocol_name;         /* name of protocol, assume user shouldn't access this */
    int app_id;                        /* application-id */
    int app_attempt_id;                /* application-attempt-id */
    int64_t cluster_timestamp;         /* time stamp of the cluster */
    pthread_mutex_t lock;              /* lock object */
} hadoop_rpc_proxy_t;

/**
 * submit application context of client 
 */
typedef struct {
} submit_application_context_t;

/**
 * container launch define for launch containers
 */
typedef struct {
    yarn_resource_t resource;
    /* Standard environ-style array, including a final NULL pointer */
    char** env;
    /* Standard argv-style array, including a final NULL pointer, need
     * include argv[0] as app name */
    char** argv
} containers_launch_context_t;

/**
 * enum define of AM status when notify AM finished
 */
typedef enum {
    /** Undefined state when either the application has not yet finished */
    APP_UNDEFINED = 0,

    /** Application which finished successfully. */
    APP_SUCCEEDED = 1,

    /** Application which failed. */
    APP_FAILED = 2,

    /** Application which was terminated by a user or admin. */
    APP_KILLED = 3
} final_am_status_t;

/**
 * get rpc proxy for user specified client/server type
 * return null when failed
 */ 
hadoop_rpc_proxy_t* new_hadoop_rpc_proxy(
    const char* host,
    int port,
    hadoop_client_type_t client_type, 
    hadoop_server_type_t server_type);  /* pass NULL we will use latest YARN version we support */

/**
 * submit application to YARN-RM from client
 * return 0 if succeed, otherwise, it's failed
 */
int submit_application(
    hadoop_rpc_proxy_t* proxy, 
    submit_application_context_t* context);

/**
 * register app master, like register to RM, init proxy-app-id, etc.
 * return 0 if succeed, otherwise, it's failed
 */
int register_app_master(hadoop_rpc_proxy_t* proxy);

/**
 * get completed status, will return containers_status_array_t if succeed
 * otherwise, will return NULL
 */
containers_status_array_t* get_completed_containers(hadoop_rpc_proxy_t* proxy);

/**
 * tell RM this app master is finished, 
 * if no diagnostics_msg, set NULL
 * return 0 if succeed
 */
int finish_app_master(hadoop_rpc_proxy_t* proxy, 
    final_am_status_t status, 
    const char* diagnostics_msg);

/**
 * submit resource request to YARN-RM, and get response.
 * please free resouces of return value and context
 * return NULL if failed, otherwise, it's succeed
 *
 * if max_wait_time(in ms) <= 0, it will try to allocate 
 * resource forever, otherwise, it will failed of this 
 * allocation after max_wait_time exceeded.
 */
allocate_resource_response_t* allocate_resource(hadoop_rpc_proxy_t* proxy,
   allocate_resource_context_t* context, int max_wait_time);



/**
 * submit resource release request to YARN-RM
 */
int release_resource(hadoop_rpc_proxy_t* proxy,
        allocate_resource_context_t* context);

/**
 * launch <launch_context> in specified container
 * return 0 if launch succeed
 * any other value if launch failed.
 */
int launch_containers(
   containers_launch_context_t* launch_context,
   allocated_container_t* container);

/**
 * init protobuf env, the pb_dir should contains compiled pb_file
 * return 0 if succeed, otherwise, it's failed
 */
int init_pb_env(const char* pb_dir, const char* hadoop_version);

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
    char** diag_msg);

/**
 * destory pb environment 
 */
void destory_pb_env();

/**
 * destory allocate_resource_response_t
 */
void destory_allocate_resource_response(allocate_resource_response_t* response);

/*
 * destory container_status_array_t
 */
void destory_container_status_array(containers_status_array_t* array);

/**
 * destory proxy
 */
void destory_hadoop_rpc_proxy(hadoop_rpc_proxy_t** pproxy);

#endif
