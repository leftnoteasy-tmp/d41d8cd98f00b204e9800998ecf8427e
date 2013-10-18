#include "yarn.h"
#include "net_utils.h"
#include "str_utils.h"
#include "log_utils.h"
#include "hadoop_rpc_constants.h"
#include "hadoop_rpc_utils.h"

// PB definitions
#include "RpcHeader.pb-c.h"
#include "IpcConnectionContext.pb-c.h"
#include "ProtobufRpcEngine.pb-c.h"

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
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/* connect_to_server, return 0 if succeed */
int connect_to_server(int socket_id, const char* host, int port) {
    //define socket variables
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //init port / socket / server
    server = gethostbyname(host);
    if (server == NULL)
    {
        yarn_log_error("ERROR, no such host.\n");
        return -1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
                server->h_length);
                serv_addr.sin_port = htons(port);
                 
    //connect via socket
    if (connect(socket_id, &serv_addr, sizeof(serv_addr)) < 0)
    {
        yarn_log_error("ERROR connecting.\n");
        return -1;
    }

    return 0;
}

/*
Spec for UserInformationProto is specified in ProtoUtil#makeIpcConnectionContext

message UserInformationProto {
  optional string effectiveUser = 1;
  optional string realUser = 2;
}

The connection context is sent as part of the connection establishment.
It establishes the context for ALL Rpc calls within the connection.

message IpcConnectionContextProto {
  // UserInfo beyond what is determined as part of security handshake
  // at connection time (kerberos, tokens etc).
  optional UserInformationProto userInfo = 2;

  // Protocol name for next rpc layer.
  // The client created a proxy with this protocol name
  optional string protocol = 3;
}
*/
static char* generate_ipc_connection_context(hadoop_rpc_proxy_t* proxy, int* len) {
    Hadoop__Common__IpcConnectionContextProto msg = HADOOP__COMMON__IPC_CONNECTION_CONTEXT_PROTO__INIT;
    Hadoop__Common__UserInformationProto ugi = HADOOP__COMMON__USER_INFORMATION_PROTO__INIT;
    ugi.effectiveuser = getlogin();
    msg.userinfo = &ugi;
    msg.protocol = proxy->protocol_name;
    return generate_delimited_message((const ProtobufCMessage*)&msg, len);
}

/* write connection header to socket */
int write_connection_header(hadoop_rpc_proxy_t* proxy) {
    int rc;

    if (!proxy) {
        yarn_log_error("proxy cannot be null.\n");
        return -1;
    }

    /**
     * Write the connection header - this is sent when connection is established
     * +----------------------------------+
     * |  "hrpc" 4 bytes                  |      
     * +----------------------------------+
     * |  Version (1 bytes)               | (This should be 9 for 2.2.0)
     * +----------------------------------+
     * |  Service cls (1 byte)            | (0 for default)
     * +----------------------------------+
     * |  AuthProtocol (1 byte)           | (0 for None, -33 for security)
     * +----------------------------------+
     */
    rc = write_all(proxy->socket_id, "hrpc", 4);
    if (rc != 0) {
        yarn_log_error("write hrpc failed.\n");
        return -1;
    }

    // write Version
    char v = 9;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        yarn_log_error("write version failed.\n");
        return -1;
    }

    // write service class (0)
    v = 0;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        yarn_log_error("write auth method failed.\n");
        return -1;
    }

    // write AutoProtocol (0)
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        yarn_log_error("write serialization type failed.\n");
        return -1;
    }

    // write RpcRequestMessageWrapper
    // generate RpcRequestHeaderProto
    int header_len;
    char* header_buffer = generate_request_header(proxy, true, &header_len);

    // generate IpcConnectionContext
    int ipc_ctx_len;
    char* ipc_ctx_buffer = generate_ipc_connection_context(proxy, &ipc_ctx_len);

    // write em' to socket
    write_endian_swap_int(proxy->socket_id, header_len + ipc_ctx_len);
    rc = write_all(proxy->socket_id, header_buffer, header_len);
    if (rc != 0) {
        yarn_log_error("write rpc header failed.");
        free(header_buffer);
        free(ipc_ctx_buffer);
        return -1;
    }
    rc = write_all(proxy->socket_id, ipc_ctx_buffer, ipc_ctx_len);
    if (rc != 0) {
        yarn_log_error("write ipc connection context failed.");
        free(header_buffer);
        free(ipc_ctx_buffer);
        return -1;
    }

    free(header_buffer);
    free(ipc_ctx_buffer);

    return 0;
}

static char* generate_protobuf_header(hadoop_rpc_proxy_t* proxy, const char* method, int* len) {
    int header_len;
    char* header_buffer = generate_request_header(proxy, true, &header_len);

    Hadoop__Common__RequestHeaderProto header = HADOOP__COMMON__REQUEST_HEADER_PROTO__INIT;
    header.methodname = method;
    header.declaringclassprotocolname = proxy->protocol_name;
    header.clientprotocolversion = 1L;

    return generate_delimited_message((const ProtobufCMessage*)&header, len);
}

/* send the whole rpc payload to socket, will add header for it */
int send_rpc_request(hadoop_rpc_proxy_t* proxy, 
    const char* method, 
    const char* msg,
    int msg_len) {

    // the standard header
    int common_header_len;
    char* common_header_msg = generate_request_header(proxy, false, &common_header_len);

    // proto specified header
    int pb_header_len;
    char* pb_header_msg = generate_protobuf_header(proxy, method, &pb_header_len);

    // total length of this RPC request
    int total_len = common_header_len + pb_header_len + msg_len;
    write_endian_swap_int(proxy->socket_id, total_len);

    // write messages one by one
    int rc = write_all(proxy->socket_id, common_header_msg, common_header_len);
    if (rc != 0) {
        yarn_log_error("write RPC request header failed");
        return -1;
    }
    rc = write_all(proxy->socket_id, pb_header_msg, pb_header_len);
    if (rc != 0) {
        yarn_log_error("write request header failed");
        return -1;
    }
    rc = write_all(proxy->socket_id, msg, msg_len);
    if (rc != 0) {
        yarn_log_error("write actual msg failed");
        return -1;
    }
    return 0;
}

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
    int request_len) {
    const MAX_VINT_SIZE = 8;

    char header_len_buffer[MAX_VINT_SIZE];
    char request_len_buffer[MAX_VINT_SIZE];
    int rc;

    int header_vint_len = write_raw_varint32(&(header_len_buffer[0]), header_len);
    int request_vint_len = write_raw_varint32(&(request_len_buffer[0]), request_len);

    /* write total length */
    int total_len = int_endian_swap(header_vint_len + header_len + request_vint_len + request_len);
    rc = write_all(socket_id, (char*)(&total_len), 4);
    if (0 != rc) {
        yarn_log_error("write total length failed.\n");
        return -1;
    }

    /* write of header vint */
    rc = write_all(socket_id, header_len_buffer, header_vint_len);
    if (0 != rc) {
        yarn_log_error("write header vint failed.\n");
        return -1;
    }

    /* write header */
    rc = write_all(socket_id, header, header_len);
    if (0 != rc) {
        yarn_log_error("write header buffer failed.\n");
        return -1;
    }

    /* write of request vint */
    rc = write_all(socket_id, request_len_buffer, request_vint_len);
    if (0 != rc) {
        yarn_log_error("write request vint failed.\n");
        return -1;
    }

    /* write header */
    rc = write_all(socket_id, request, request_len);
    if (0 != rc) {
        yarn_log_error("write request buffer failed.\n");
        return -1;
    }

    return 0;
}

/* genereate delimited message (with vint length in buffer) */
char* generate_delimited_message(const ProtobufCMessage *message, int* length_out) {
    int msg_len = protobuf_c_message_get_packed_size(message);
    int vint_len = get_raw_varint32_len(msg_len);
    char* buffer = (char*)malloc(vint_len + msg_len);
    protobuf_c_message_pack(message, buffer + vint_len);
    write_raw_varint32(buffer, msg_len);
    *length_out = msg_len + vint_len;
    return buffer;
}

/* generate header for request 
enum RpcKindProto {
  RPC_BUILTIN          = 0;  // Used for built in calls by tests
  RPC_WRITABLE         = 1;  // Use WritableRpcEngine
  RPC_PROTOCOL_BUFFER  = 2;  // Use ProtobufRpcEngine
}
   
message RpcRequestHeaderProto { // the header for the RpcRequest
  enum OperationProto {
    RPC_FINAL_PACKET        = 0; // The final RPC Packet
    RPC_CONTINUATION_PACKET = 1; // not implemented yet 
    RPC_CLOSE_CONNECTION     = 2; // close the rpc connection
  }

  optional RpcKindProto rpcKind = 1;
  optional OperationProto rpcOp = 2;
  required sint32 callId = 3; // a sequence number that is sent back in response
  required bytes clientId = 4; // Globally unique client ID
  // clientId + callId uniquely identifies a request
  // retry count, 1 means this is the first retry
  optional sint32 retryCount = 5 [default = -1];
}
*/
char* generate_request_header(hadoop_rpc_proxy_t* proxy, bool first, int* size) {
    Hadoop__Common__RpcRequestHeaderProto header = HADOOP__COMMON__RPC_REQUEST_HEADER_PROTO__INIT;

    // set has fields
    header.has_rpckind = true;
    header.has_rpcop = true;
    header.has_retrycount = true;

    header.rpckind = 2;

    header.rpcop = 0;
    if (first) {
        header.callid = -3;
        header.retrycount = -1;
    } else {
        header.callid = proxy->caller_id++;
        header.retrycount = 0;
    }
    header.clientid.len = proxy->uuid_len;
    header.clientid.data = proxy->uuid;
    char* msg_buffer = generate_delimited_message((const ProtobufCMessage*)&header, size);
    return msg_buffer;
}


/* read header of response,
 * it will return actual response message if succeed
 * it will return NULL if failed/error, and print error messages
 */ 
char* recv_rpc_response(hadoop_rpc_proxy_t* proxy, int* response_msg_len) {
    int response_total_len;
    int rc;

    // read length
    rc = read_all(proxy->socket_id, &response_total_len, sizeof(int));
    if (0 != rc) {
        yarn_log_error("failed to read total length of response");
        return NULL;
    }

    // read vlen of response header
    int vint_len;
    int response_header_len;
    rc = read_raw_varint32(proxy->socket_id, &vint_len, &response_header_len);
    if (0 != rc) {
        yarn_log_error("failed to read response header length");
        return NULL;
    }

    // parse response header
    char header_buffer[response_header_len];
    rc = read_all(proxy->socket_id, header_buffer, response_header_len);
    Hadoop__Common__RpcResponseHeaderProto* response_header = 
        hadoop__common__rpc_response_header_proto__unpack(NULL, response_header_len, header_buffer);
    if (!response_header) {
        yarn_log_error("failed to parse rpc response header");
        return NULL;
    }

    // check values of response header and print error messages if needed
    if (HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_STATUS_PROTO__SUCCESS == response_header->status) {
        // clear response header
        hadoop__common__rpc_response_header_proto__free_unpacked(response_header, NULL);

        // do succeed response
        // continue read buffer, get actual response message
        rc = read_raw_varint32(proxy->socket_id, &vint_len, response_msg_len);
        if (0 != rc) {
            yarn_log_error("failed to read response message length");
            return NULL;
        }
        char* buffer = (char*)malloc(*response_msg_len);
        rc = read_all(proxy->socket_id, buffer, *response_msg_len);
        if (0 != rc) {
            yarn_log_error("failed to read response message");
            free(buffer);
            return NULL;
        }
        return buffer;
    } else {
        yarn_log_error("error received in rpc communication:");
        // do failed response
        if (response_header->exceptionclassname) {
            yarn_log_error("exception class name:%s", response_header->exceptionclassname);
        }
        if (response_header->errormsg) {
            yarn_log_error("exception message:%s", response_header->errormsg);
        }
        if (response_header->has_errordetail) {
            // TODO, make the error code readable
            yarn_log_error("detailed error code is %d", response_header->errordetail);
        }
        hadoop__common__rpc_response_header_proto__free_unpacked(response_header, NULL);
        return NULL;
    }
}
