#include "client_rm_protocol_impl.h"
#include "hadoop_rpc_utils.h"
#include "yarn.h"
#include "net_utils.h"
#include "str_utils.h"
#include "log_utils.h"
#include "hadoop_rpc_constants.h"

#include "yarn_service_protos.pb-c.h"

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

/* static methods*/
static int generate_new_app_request(char** buffer, int* size);

/* global methods */
int get_new_application_impl(hadoop_rpc_proxy_t* proxy) {
    int rc;
    if (-1 != proxy->app_id) {
        yarn_log_error("there's already a app, id=%d, will exit", proxy->app_id);
        return -1;
    }

    char* request = NULL;
    int request_len;

    /*****************************************************
     * first, we will submit CreateNewApplicationRequest *
     *****************************************************/

    // generate new_application_request
    rc = generate_new_app_request(&request, &request_len);
    if (0 != rc) {
        yarn_log_error("generate new app request failed.");
        return -1;
    }

    // send request
    rc = send_rpc_request(proxy, "getNewApplication", request, request_len);
    if (0 != rc) {
        yarn_log_error("send new_application_request failed.");
        free(request);
        return -1;
    }

    // now we will not use it anymore
    free(request);

    // read response
    int response_msg_len;
    char* response = recv_rpc_response(proxy, &response_msg_len);
    if (!response) {
        return -1;
    }

    /* problem here , cannot read varint from socket after read response out */
    /* need add a read varint32 from buffer method */

    // read response len
    int msg_len;
    int v_len;
    rc = read_raw_varint32(proxy->socket_id, &v_len, &msg_len);
    if (0 != rc) {
        yarn_log_error("read vint of response message failed in get_new_application_impl");
        free(response);
        return -1;
    }

    // unpack response
    Hadoop__Yarn__GetNewApplicationResponseProto* response_msg = 
        hadoop__yarn__get_new_application_response_proto__unpack(NULL, response_msg_len - v_len, response + v_len);
    if (!response_msg) {
        yarn_log_error("failed to unpack response message of get_new_application_impl");
        free(response);
        return -1;
    }
    free(response);

    return 0;

    // get attempt_id from response and set it to proxy
    // TODO
}

/* ClientRMProtocol.getNewApplication */
static int generate_new_app_request(char** buffer, int* size) {
    Hadoop__Yarn__GetNewApplicationRequestProto request = HADOOP__YARN__GET_NEW_APPLICATION_REQUEST_PROTO__INIT;
    *buffer = generate_delimited_message((const ProtobufCMessage*)&request, size);
    return 0;
}
