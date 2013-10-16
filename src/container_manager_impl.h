#ifndef _HD_CLIENT_CONTAINER_MANAGER_H
#define _HD_CLIENT_CONTAINER_MANAGER_H

#include "orte/mca/common/yarnpbc/hdclient/hadoop_rpc.h"

/**
 * launch <launch_context> in specified container
 * return 0 if launch succeed
 * any other value if launch failed.
 */
int launch_containers_impl(
   containers_launch_context_t* launch_context,
   allocated_container_t* container);

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
    char** diag_msg);

#endif