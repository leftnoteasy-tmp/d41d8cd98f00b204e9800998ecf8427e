#include "yarn.h"
#include "net_utils.h"
#include "str_utils.h"
#include "log_utils.h"
#include "hadoop_rpc_constants.h"
#include "hadoop_rpc_utils.h"

// PB definitions
#include "RpcHeader.pb-c.h"
#include "IpcConnectionContext.pb-c.h"

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
        return -1;
    }
    rc = write_all(proxy->socket_id, ipc_ctx_buffer, ipc_ctx_len);
    if (rc != 0) {
        yarn_log_error("write ipc connection context failed.");
        return -1;
    }

    return 0;
}

static char* generate_protobuf_header(hadoop_rpc_proxy_t* proxy, const char* method, int* len) {
    int header_len;
    char* header_buffer = generate_request_header(proxy, true, &header_len);

    Hadoop__Common__RequestHeaderProto header = HADOOP__COMMON__REQUEST_HEADER_PROTO__INIT;
    header.methodname = method;
    header.declaringclassprotocolname = proxy->protocol_name;
    header.clientprotocolversion = 1L;

    return generate_delimited_message((const ProtobufCMessage*)&msg, len);
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

/**
 * set local resources to msg, return 0 if succeed
 */
/*
int set_local_resources(struct pbc_wmessage* msg, const char* key) {
    int rc, len, i;

    // instanity check
    if ((!msg) || (!key)) {
        yarn_log_error("set_local_resources: msg/key is null.\n");
        return -1;
    }

    // check if initialized
    if (local_resource_pb_num < 0) {
        rc = init_local_resources();
        if (rc != 0) {
            yarn_log_error("init_local_resources failed.\n");
            return -1;
        }
    }


    // loop local_resource and copy it to msg
    for (i = 0; i < local_resource_pb_num; i++) {

        // for convenience
        struct pbc_rmessage* rvalue = local_resource_pb_array[i]->rmsg;

        // get a new wmsg for write
        struct pbc_wmessage* wmsg = pbc_wmessage_message(msg, key);
        if (!wmsg) {
            yarn_log_error("set_local_resources get wmsg from msg failed.\n");
            return -1;
        }

        // serialize key
        rc = pbc_wmessage_string(wmsg, "key", local_resource_pb_array[i]->key, 0);
        if (0 != rc) {
            yarn_log_error("serialize key to wmsg failed.\n");
            return -1;
        }

        // get LocalResourceProto
        struct pbc_wmessage* wvalue = pbc_wmessage_message(wmsg, "value");
        if (!wvalue) {
            yarn_log_error("failed to get walue from wmsg.\n");
            return -1;
        }

        // read and set size
        uint64_t size;
        size = pbc_rmessage_int64(rvalue, "size", 0);
        uint32_t ulo = size & 0xFFFFFFFF;
        uint32_t uhi = size >> 32;
        rc = pbc_wmessage_integer(wvalue, "size", ulo, uhi);
        if (0 != rc) {
            yarn_log_error("failed to set size in wvalue.\n");
            return -1;
        }

        // read and set timestamp
        uint64_t timestamp;
        timestamp = pbc_rmessage_int64(rvalue, "timestamp", 0);
        ulo = timestamp & 0xFFFFFFFF;
        uhi = timestamp >> 32;
        rc = pbc_wmessage_integer(wvalue, "timestamp", ulo, uhi);
        if (0 != rc) {
            yarn_log_error("failed to set timestamp in wvalue.\n");
            return -1;
        }

        // read and set type
        int type = pbc_rmessage_integer(rvalue, "type", 0, NULL);
        rc = pbc_wmessage_integer(wvalue, "type", type, NULL);
        if (0 != rc) {
            yarn_log_error("failed to set type in wvalue");
            return -1;
        }

        // read and set visibility
        int visibility = pbc_rmessage_integer(rvalue, "visibility", 0, NULL);
        rc = pbc_wmessage_integer(wvalue, "visibility", visibility, NULL);
        if (0 != rc) {
            yarn_log_error("failed to set visibility in wvalue");
            return -1;
        }

        // read and set url
        struct pbc_rmessage* rurl = pbc_rmessage_message(rvalue, "resource", 0);
        struct pbc_wmessage* wurl = pbc_wmessage_message(wvalue, "resource");
        if ((!rurl) || (!wurl)) {
            yarn_log_error("failed to get rurl or wurl.\n");
            return -1;
        }

        char* scheme = pbc_rmessage_string(rurl, "scheme", 0, NULL);
        char* host = pbc_rmessage_string(rurl, "host", 0, NULL);
        char* file = pbc_rmessage_string(rurl, "file", 0, NULL);
        int port = pbc_rmessage_integer(rurl, "port", 0, NULL);

        if (!file) {
            yarn_log_error("failed to read file from rurl.\n");
            return -1;
        }

        if (scheme) {
            rc = pbc_wmessage_string(wurl, "scheme", scheme, NULL);
            if (rc != 0) {
                yarn_log_error("failed to ser scheme to wurl.\n");
                return -1;
            }
        }

        if (host) {
            rc = pbc_wmessage_string(wurl, "host", host, NULL);
            if (rc != 0) {
                yarn_log_error("failed to ser host to wurl.\n");
                return -1;
            }
        }

        rc = pbc_wmessage_string(wurl, "file", file, NULL);
        if (rc != 0) {
            yarn_log_error("failed to ser file to wurl.\n");
            return -1;
        }

        rc = pbc_wmessage_integer(wurl, "port", port, NULL);
        if (rc != 0) {
            yarn_log_error("failed to ser port to wurl.\n");
            return -1;
        }
    }
    return 0;
}
*/

/**
 *  set app_id in PB
    message ApplicationIdProto {
        optional int32 id = 1;
        optional int64 cluster_timestamp = 2;
    }
 */
/*
int set_app_id(struct pbc_wmessage* m,
        const char* key,
        hadoop_rpc_proxy_t* proxy) {
    int rc;
    struct pbc_wmessage* app_id_msg = pbc_wmessage_message(m, key);
    if (!app_id_msg) {
        yarn_log_error("get app_id_msg, failed.\n");
        return -1;
    }

    rc = pbc_wmessage_integer(app_id_msg, "id", proxy->app_id, 0);
    if (rc != 0) {
        yarn_log_error("pack app_id failed.\n");
        return -1;
    }

    int64_t ts = proxy->cluster_timestamp;
    uint32_t ulo = ts & 0xFFFFFFFF;
    uint32_t uhi = ts >> 32;
    rc = pbc_wmessage_integer(app_id_msg, "cluster_timestamp", ulo, uhi);
    if (rc != 0) {
        yarn_log_error("pack cluster timestamp failed.\n");
        return -1;
    }

    return 0;
}
*/

/**
 *  message ApplicationAttemptIdProto {
 *   optional ApplicationIdProto application_id = 1;
 *   optional int32 attemptId = 2;
 *  }
 */
 /*
int set_app_attempt_id(struct pbc_wmessage *m,
        const char *key,
        hadoop_rpc_proxy_t* proxy) {
    int rc;
    struct pbc_wmessage* app_attempt_id_msg = pbc_wmessage_message(m, key);
    if (!app_attempt_id_msg) {
        yarn_log_error("get app_attempt_id_msg failed.\n");
        return -1;
    }

    // pack attempt_id
    rc = pbc_wmessage_integer(app_attempt_id_msg, "attemptId", proxy->app_attempt_id, 0);
    if (rc != 0) {
        yarn_log_error("pack attempt_id failed.\n");
        return -1;
    }

    struct pbc_wmessage* app_id_msg = pbc_wmessage_message(app_attempt_id_msg, "application_id");
    if (!app_id_msg) {
        yarn_log_error("get app_id_msg, failed.\n");
        return -1;
    }

    rc = pbc_wmessage_integer(app_id_msg, "id", proxy->app_id, 0);
    if (rc != 0) {
        yarn_log_error("pack app_id failed.\n");
        return -1;
    }

    int64_t ts = proxy->cluster_timestamp;
    uint32_t ulo = ts & 0xFFFFFFFF;
    uint32_t uhi = ts >> 32;
    rc = pbc_wmessage_integer(app_id_msg, "cluster_timestamp", ulo, uhi);
    if (rc != 0) {
        yarn_log_error("pack cluster timestamp failed.\n");
        return -1;
    }

    return 0;
}
*/

/* genereate delimited message (with vint length in buffer) */
char* generate_delimited_message(const ProtobufCMessage *message, int* length_out) {
    int msg_len = protobuf_c_message_get_packed_size(message);
    int vint_len = get_raw_varint32_len(msg_len);
    char* buffer = (char*)malloc(vint_len + msg_len);
    protobuf_c_message_pack(message, buffer + vint_len);
    write_raw_varint32(buffer, msg_len);
    *length_out = msg_len + vint_len;

    //debug
    int i;
    for (i = 0; i < msg_len; i++) {
        printf("%d ", buffer[i + vint_len]);
    }
    printf("\n");
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


/* read header of response, it will first read a varint32 of header size, 
 * then following is header
 * if SUCCEED, (return RESPONSE_SUCCEED), it will also read response buffer and size
 * if ERROR, (return RESPONSE_ERROR), then you can call read_exception(...) to get 
 *    what happended
 * if FATAL, (return RESPONSE_FATAL), then you can call read_fatal to get version of
 *    server side
 */ 
response_type_t recv_rpc_response(hadoop_rpc_proxy_t* proxy,
    char** response, int* size) {
    // add return
}

/**
 * init app_id and cluster_timestamp from envars, 
 * will return 0: if proxy->app_id not defined (-1) and successfully 
                 get from env or it's already set
               other value: other-wise.
 */
int init_app_id_from_env(hadoop_rpc_proxy_t* proxy) {
    if (proxy->app_id == -1) {
        /* if app_id not defined, try to see if is it defined in envar */
        char* val = getenv(APP_ID_ENV_KEY);
        if (NULL != val) {
            int app_id = atoi(val);
            proxy->app_id = app_id;
        } else {
            yarn_log_error("app id is not defined, please check.\n");
            return -1;
        }
    }

    if (proxy->cluster_timestamp == -1) {
        /* if app_id not defined, try to see if is it defined in envar */
        char* val = getenv(CLUSTER_TIMESTAMP_ENV_KEY);
        if (NULL != val) {
            long ts = atol(val);
            proxy->cluster_timestamp = ts;
        } else {
            yarn_log_error("cluster time stamp is not defined, please check.\n");
            return -1;
        }
    }

    return 0;
}
