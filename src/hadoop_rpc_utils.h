#ifndef _HD_CLIENT_HADOOP_RPC_UTILS_H_
#define _HD_CLIENT_HADOOP_RPC_UTILS_H_

#include "yarn.h"
#include <google/protobuf-c/protobuf-c.h>
#include <stdbool.h>

/* type of RPC PB response */
typedef enum {
    RESPONSE_SUCCEED,
    RESPONSE_ERROR,
    RESPONSE_FATAL,
    RESPONSE_OTHER_ERROR
} response_type_t;

/* check if initialized pb-env and print error msg */
bool check_init_and_print();

/* connect_to_server, return 0 if succeed */
int connect_to_server(int socket_id, const char* host, int port);

/* write connection header to socket */
int write_connection_header(hadoop_rpc_proxy_t* proxy);

/* generate header for request */
char* generate_request_header(hadoop_rpc_proxy_t* proxy, bool first, int* size);

/* genereate delimited message (with vint length in buffer) */
char* generate_delimited_message(const ProtobufCMessage *message, int* length_out);

/**
 *  message ApplicationAttemptIdProto {
 *   optional ApplicationIdProto application_id = 1;
 *   optional int32 attemptId = 2;
 *  }
 */
int set_app_attempt_id(ProtobufCMessage *msg,
        const char *key,
        hadoop_rpc_proxy_t* proxy);

/**
 *  set app_id in PB
 */
int set_app_id(ProtobufCMessage *m,
        const char *key,
        hadoop_rpc_proxy_t* proxy);

/**
 * set local resources to msg, return 0 if succeed
 */
int set_local_resources(ProtobufCMessage* msg, const char* key);

/* 
message HadoopRpcRequestProto {
  required string methodName = 1; 
  optional bytes request = 2;
  required string declaringClassProtocolName = 3;
  required uint64 clientProtocolVersion = 4;
}
 
 * An example,
 * methodName: "getAllApplications"
 * request: GetAllApplicationRequest.getBytes()
 * declaringClassProtocolName: "org.apache.hadoop.yarn.api.ClientRMProtocolPB"
 * clientProtocolVersion: 1
*/
int generate_hadoop_request(const char* request,
    int request_len,
    const char* protocol, 
    const char* method,
    char** buffer, 
    int* size);

/* try to write request to socket
 * -----------------------------------------------
 * | length of length(header) + length(request)  |
 * | header = raw_varint_int(header) + header    |
 * | request = raw_varint_int(request) + request |
 * -----------------------------------------------
 */
int write_request(
    int socket_id, 
    const char* header, 
    int header_len, 
    const char* request, 
    int request_len);

/**
 * init app_id and cluster_timestamp from envars, 
 * will return 0: if proxy->app_id not defined (-1) and successfully 
                 get from env or it's already set
               other value: other-wise.
 */
int init_app_id_from_env(hadoop_rpc_proxy_t* proxy);

/* read header of response,
 * it will return actual response message if succeed
 * it will return NULL if failed/error, and print error messages
 */ 
char* recv_rpc_response(hadoop_rpc_proxy_t* proxy, int* response_msg_len);

/* read error, return 0 if SUCCEED, and put error msg to params */
int read_exception(hadoop_rpc_proxy_t* proxy, 
    char** exception_class, 
    char** exception_stack);

/* send the whole rpc payload to socket, will add header for it */
int send_rpc_request(hadoop_rpc_proxy_t* proxy, 
    const char* method, 
    const char* msg,
    int msg_len);

void process_bad_rpc_response(hadoop_rpc_proxy_t* proxy, response_type_t type);


#endif //_HD_CLIENT_HADOOP_RPC_UTILS_H_
