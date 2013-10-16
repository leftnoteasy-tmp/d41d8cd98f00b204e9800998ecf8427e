#ifndef _HD_CLIENT_AM_RM_PROTOCOL_IMPL_H
#define _HD_CLIENT_AM_RM_PROTOCOL_IMPL_H

#include "orte/mca/common/yarnpbc/hdclient/hadoop_rpc.h"

/**
 * implementation of register app master
 */
int register_app_master_impl(hadoop_rpc_proxy_t* proxy);

/**
 * notify RM app master finished.
 * if no diagnostics_msg, set NULL
 * return 0 if succeed
 */
int finish_app_master_impl(hadoop_rpc_proxy_t* proxy, 
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
allocate_resource_response_t* allocate_resource_impl(
    hadoop_rpc_proxy_t* proxy,
    allocate_resource_context_t* context,
    int max_wait_time);


/**
 * release containers via allocate_resource_once
 */
allocate_resource_response_t* release_resource_impl(hadoop_rpc_proxy_t* proxy,
        allocate_resource_context_t* context);

/**
 * get completed status, will return containers_status_array_t if succeed
 * otherwise, will return NULL
 */
containers_status_array_t* get_completed_containers_impl(hadoop_rpc_proxy_t* proxy);

#endif
