#include "hadoop_rpc.h"
#include "net_utils.h"
#include "pbc_utils.h"
#include "str_utils.h"
#include "hadoop_rpc_constants.h"
#include "hadoop_rpc_utils.h"

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
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct {
    char* key;
    struct pbc_slice slice;
    struct pbc_rmessage* rmsg;
} local_resource_pb_t;

static local_resource_pb_t** local_resource_pb_array;
static local_resource_pb_num = -1;

/* check if initialized pb-env and print error msg */
bool check_init_and_print() {
    if (!is_env_initialize){
        opal_output(0, "initialize pb_env before use this function.\n");
        return false;
    }
    return true;
}

/* connect_to_server, return 0 if succeed */
int connect_to_server(int socket_id, const char* host, int port) {
    //define socket variables
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //init port / socket / server
    server = gethostbyname(host);
    if (server == NULL)
    {
        opal_output(0, "ERROR, no such host.\n");
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
        opal_output(0, "ERROR connecting.\n");
        return -1;
    }

    return 0;
}

/* write connection header to socket */
int write_connection_header(hadoop_rpc_proxy_t* proxy) {
    int rc;
    struct pbc_slice slice;

    if (!proxy) {
        opal_output(0, "proxy cannot be null.\n");
        return -1;
    }

    /**
     * Write the connection header - this is sent when connection is established
     * +----------------------------------+
     * |  "hrpc" 4 bytes                  |      
     * +----------------------------------+
     * |  Version (1 bytes)               | (This should be 7 for 2.0.x)
     * +----------------------------------+
     * |  Authmethod (1 byte)             | (80->SIMPLE), (81->GSSAPI), (82-DIGEST)
     * +----------------------------------+
     * |  IpcSerializationType (1 byte)   | (should be 0)
     * +----------------------------------+
     */
    rc = write_all(proxy->socket_id, "hrpc", 4);
    if (rc != 0) {
        opal_output(0, "write hrpc failed.\n");
        return -1;
    }

    // process different hd version
    char v;
    if (strcmp(hadoop_version, APACHE_HADOOP_202_VER) == 0) {
        v = 7;
    } else {
        v = 8;
    }
    
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        opal_output(0, "write version failed.\n");
        return -1;
    }

    v = 80;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        opal_output(0, "write auth method failed.\n");
        return -1;
    }

    v = 0;
    rc = write_all(proxy->socket_id, &v, 1);
    if (rc != 0) {
        opal_output(0, "write serialization type failed.\n");
        return -1;
    }

    /* write IpcConectionContextProto to socket */
    struct pbc_wmessage* ipc_proto;
    if (strcmp(hadoop_version, APACHE_HADOOP_202_VER) == 0) {
        ipc_proto = pbc_wmessage_new(env, "IpcConnectionContextProto");
    } else {
        ipc_proto = pbc_wmessage_new(env, "hadoop.common.IpcConnectionContextProto");
    }
    if (!ipc_proto) {
        opal_output(0, "current env not contains hadoop.common.IpcConnectionContextProto, plz check.\n");
        return -1;
    }

    pbc_wmessage_string(ipc_proto, "protocol", proxy->protocol_name, 0);
    pbc_wmessage_buffer(ipc_proto, &slice);

    /* write length of IpcConnectionContextProto */
    int len = int_endian_swap(slice.len);
    rc = write_all(proxy->socket_id, (char*)(&len), 4);
    if (rc != 0) {
        opal_output(0, "write length of ipc connection context failed.\n");
        pbc_wmessage_delete(ipc_proto);
        return -1;
    }

    /* write content of pack context */
    rc = write_all(proxy->socket_id, (char*)(slice.buffer), slice.len);
    if (rc != 0) {
        opal_output(0, "write IpcConectionContextProto failed.\n");
        pbc_wmessage_delete(ipc_proto);
        free(slice.buffer);
        return -1;
    }

    pbc_wmessage_delete(ipc_proto);

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
        opal_output(0, "write total length failed.\n");
        return -1;
    }

    /* write of header vint */
    rc = write_all(socket_id, header_len_buffer, header_vint_len);
    if (0 != rc) {
        opal_output(0, "write header vint failed.\n");
        return -1;
    }

    /* write header */
    rc = write_all(socket_id, header, header_len);
    if (0 != rc) {
        opal_output(0, "write header buffer failed.\n");
        return -1;
    }

    /* write of request vint */
    rc = write_all(socket_id, request_len_buffer, request_vint_len);
    if (0 != rc) {
        opal_output(0, "write request vint failed.\n");
        return -1;
    }

    /* write header */
    rc = write_all(socket_id, request, request_len);
    if (0 != rc) {
        opal_output(0, "write request buffer failed.\n");
        return -1;
    }

    return 0;
}

static int init_local_resources() {
    int rc, len, i;

    // start initialize local_resources
    int file = open(DEFAULT_LOCALRESOURCE_SERIALIZED_FILENAME,  O_RDONLY);
    if (file < 0) {
        opal_output(0, "open DEFAULT_LOCALRESOURCE_SERIALIZED_FILENAME failed.\n");
        return -1;
    }

    // read from file
    rc = read(file, &local_resource_pb_num, sizeof(int));
    if (rc != sizeof(int)) {
        opal_output(0, "error when reading local_resource_pb_num.\n");
        return -1;
    }
    local_resource_pb_num = int_endian_swap(local_resource_pb_num);

    if (0 >= local_resource_pb_num) {
        opal_output(0, "local_resource_pb_num <= 0, please check.\n");
        return -1;
    }

    // init local_resource_pb_array
    local_resource_pb_array = (local_resource_pb_t**)malloc(sizeof(local_resource_pb_t*) * local_resource_pb_num);
    if (!local_resource_pb_array) {
        opal_output(0, "error when allocate local_resource_pb_array.\n");
        return -1;
    }

    for (i = 0; i < local_resource_pb_num; i++) {
        // malloc this local_resource_pb_array
        local_resource_pb_array[i] = (local_resource_pb_t*)malloc(sizeof(local_resource_pb_t));
        if (!local_resource_pb_array[i]) {
            opal_output(0, "allocate local_resource_pb_array[%d] failed.\n", i);
            return -1;
        }
        local_resource_pb_t* cur_res = local_resource_pb_array[i]; // for convenience

        // read key in
        rc = read(file, &len, sizeof(int));
        if (rc != sizeof(int)) {
            opal_output(0, "error when reading length of key.\n");
            return -1;
        }
        len = int_endian_swap(len);
        cur_res->key = (char*)malloc(len + 1);
        if (!cur_res->key) {
            opal_output(0, "error when allocate cur_res->key.\n");
            return -1;
        }
        rc = read(file, cur_res->key, len);
        if (rc != len) {
            opal_output(0, "error when reading content of key.\n");
            return -1;
        }
        cur_res->key[len] = '\0';

        // read slice in
        rc = read(file, &(cur_res->slice.len), sizeof(int));
        if (rc != sizeof(int)) {
            opal_output(0, "error when reading slice len.\n");
            return -1;
        }
        cur_res->slice.len = int_endian_swap(cur_res->slice.len);
        cur_res->slice.buffer = malloc(cur_res->slice.len);
        if (!cur_res->slice.buffer) {
            opal_output(0, "error when allocate content of slice.\n");
            return -1;
        }
        rc = read(file, cur_res->slice.buffer, cur_res->slice.len);
        if (rc != cur_res->slice.len) {
            opal_output(0, "error when reading slice content.\n");
            return -1;
        }

        // re-create rmessage
        cur_res->rmsg = pbc_rmessage_new(env, "LocalResourceProto", &cur_res->slice);
        if (!cur_res->rmsg) {
            opal_output(0, "error when read rmessage from slice.\n");
            return -1;
        }
    }

    // finish reading
    close(file);
    return 0;
}

/**
 * set local resources to msg, return 0 if succeed
 */
int set_local_resources(struct pbc_wmessage* msg, const char* key) {
    int rc, len, i;

    // instanity check
    if ((!msg) || (!key)) {
        opal_output(0, "set_local_resources: msg/key is null.\n");
        return -1;
    }

    // check if initialized
    if (local_resource_pb_num < 0) {
        rc = init_local_resources();
        if (rc != 0) {
            opal_output(0, "init_local_resources failed.\n");
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
            opal_output(0, "set_local_resources get wmsg from msg failed.\n");
            return -1;
        }

        // serialize key
        rc = pbc_wmessage_string(wmsg, "key", local_resource_pb_array[i]->key, 0);
        if (0 != rc) {
            opal_output(0, "serialize key to wmsg failed.\n");
            return -1;
        }

        // get LocalResourceProto
        struct pbc_wmessage* wvalue = pbc_wmessage_message(wmsg, "value");
        if (!wvalue) {
            opal_output(0, "failed to get walue from wmsg.\n");
            return -1;
        }

        // read and set size
        uint64_t size;
        size = pbc_rmessage_int64(rvalue, "size", 0);
        uint32_t ulo = size & 0xFFFFFFFF;
        uint32_t uhi = size >> 32;
        rc = pbc_wmessage_integer(wvalue, "size", ulo, uhi);
        if (0 != rc) {
            opal_output(0, "failed to set size in wvalue.\n");
            return -1;
        }

        // read and set timestamp
        uint64_t timestamp;
        timestamp = pbc_rmessage_int64(rvalue, "timestamp", 0);
        ulo = timestamp & 0xFFFFFFFF;
        uhi = timestamp >> 32;
        rc = pbc_wmessage_integer(wvalue, "timestamp", ulo, uhi);
        if (0 != rc) {
            opal_output(0, "failed to set timestamp in wvalue.\n");
            return -1;
        }

        // read and set type
        int type = pbc_rmessage_integer(rvalue, "type", 0, NULL);
        rc = pbc_wmessage_integer(wvalue, "type", type, NULL);
        if (0 != rc) {
            opal_output(0, "failed to set type in wvalue");
            return -1;
        }

        // read and set visibility
        int visibility = pbc_rmessage_integer(rvalue, "visibility", 0, NULL);
        rc = pbc_wmessage_integer(wvalue, "visibility", visibility, NULL);
        if (0 != rc) {
            opal_output(0, "failed to set visibility in wvalue");
            return -1;
        }

        // read and set url
        struct pbc_rmessage* rurl = pbc_rmessage_message(rvalue, "resource", 0);
        struct pbc_wmessage* wurl = pbc_wmessage_message(wvalue, "resource");
        if ((!rurl) || (!wurl)) {
            opal_output(0, "failed to get rurl or wurl.\n");
            return -1;
        }

        char* scheme = pbc_rmessage_string(rurl, "scheme", 0, NULL);
        char* host = pbc_rmessage_string(rurl, "host", 0, NULL);
        char* file = pbc_rmessage_string(rurl, "file", 0, NULL);
        int port = pbc_rmessage_integer(rurl, "port", 0, NULL);

        if (!file) {
            opal_output(0, "failed to read file from rurl.\n");
            return -1;
        }

        if (scheme) {
            rc = pbc_wmessage_string(wurl, "scheme", scheme, NULL);
            if (rc != 0) {
                opal_output(0, "failed to ser scheme to wurl.\n");
                return -1;
            }
        }

        if (host) {
            rc = pbc_wmessage_string(wurl, "host", host, NULL);
            if (rc != 0) {
                opal_output(0, "failed to ser host to wurl.\n");
                return -1;
            }
        }

        rc = pbc_wmessage_string(wurl, "file", file, NULL);
        if (rc != 0) {
            opal_output(0, "failed to ser file to wurl.\n");
            return -1;
        }

        rc = pbc_wmessage_integer(wurl, "port", port, NULL);
        if (rc != 0) {
            opal_output(0, "failed to ser port to wurl.\n");
            return -1;
        }
    }
    return 0;
}

/**
 *  set app_id in PB
    message ApplicationIdProto {
        optional int32 id = 1;
        optional int64 cluster_timestamp = 2;
    }
 */
int set_app_id(struct pbc_wmessage* m,
        const char* key,
        hadoop_rpc_proxy_t* proxy) {
    int rc;
    struct pbc_wmessage* app_id_msg = pbc_wmessage_message(m, key);
    if (!app_id_msg) {
        opal_output(0, "get app_id_msg, failed.\n");
        return -1;
    }

    rc = pbc_wmessage_integer(app_id_msg, "id", proxy->app_id, 0);
    if (rc != 0) {
        opal_output(0, "pack app_id failed.\n");
        return -1;
    }

    int64_t ts = proxy->cluster_timestamp;
    uint32_t ulo = ts & 0xFFFFFFFF;
    uint32_t uhi = ts >> 32;
    rc = pbc_wmessage_integer(app_id_msg, "cluster_timestamp", ulo, uhi);
    if (rc != 0) {
        opal_output(0, "pack cluster timestamp failed.\n");
        return -1;
    }

    return 0;
}

/**
 *  message ApplicationAttemptIdProto {
 *   optional ApplicationIdProto application_id = 1;
 *   optional int32 attemptId = 2;
 *  }
 */
int set_app_attempt_id(struct pbc_wmessage *m,
        const char *key,
        hadoop_rpc_proxy_t* proxy) {
    int rc;
    struct pbc_wmessage* app_attempt_id_msg = pbc_wmessage_message(m, key);
    if (!app_attempt_id_msg) {
        opal_output(0, "get app_attempt_id_msg failed.\n");
        return -1;
    }

    // pack attempt_id
    rc = pbc_wmessage_integer(app_attempt_id_msg, "attemptId", proxy->app_attempt_id, 0);
    if (rc != 0) {
        opal_output(0, "pack attempt_id failed.\n");
        return -1;
    }

    struct pbc_wmessage* app_id_msg = pbc_wmessage_message(app_attempt_id_msg, "application_id");
    if (!app_id_msg) {
        opal_output(0, "get app_id_msg, failed.\n");
        return -1;
    }

    rc = pbc_wmessage_integer(app_id_msg, "id", proxy->app_id, 0);
    if (rc != 0) {
        opal_output(0, "pack app_id failed.\n");
        return -1;
    }

    int64_t ts = proxy->cluster_timestamp;
    uint32_t ulo = ts & 0xFFFFFFFF;
    uint32_t uhi = ts >> 32;
    rc = pbc_wmessage_integer(app_id_msg, "cluster_timestamp", ulo, uhi);
    if (rc != 0) {
        opal_output(0, "pack cluster timestamp failed.\n");
        return -1;
    }

    return 0;
}

/* generate header for request :
    enum RpcKindProto {
      RPC_BUILTIN          = 0;  // Used for built in calls by tests
      RPC_WRITABLE         = 1;  // Use WritableRpcEngine 
      RPC_PROTOCOL_BUFFER  = 2;  // Use ProtobufRpcEngine
    }
     
    enum RpcPayloadOperationProto {
      RPC_FINAL_PAYLOAD        = 0; // The final payload
      RPC_CONTINUATION_PAYLOAD = 1; // not implemented yet
      RPC_CLOSE_CONNECTION     = 2; // close the rpc connection
    }
        
    message RpcPayloadHeaderProto { // the header for the RpcRequest
      optional RpcKindProto rpcKind = 1;
      optional RpcPayloadOperationProto rpcOp = 2;
      required uint32 callId = 3; // each rpc has a callId that is also used in response
    }
*/
int generate_request_header(char** p_buffer, int* size, int caller_id) {
    struct pbc_wmessage* header;
    if (strcmp(hadoop_version, APACHE_HADOOP_202_VER) == 0) {
        header = pbc_wmessage_new(env, "RpcPayloadHeaderProto");
    } else {
        header = pbc_wmessage_new(env, "hadoop.common.RpcPayloadHeaderProto");
    }

    if (!header) {
        opal_output(0, "current env not contains RpcPayloadHeaderProto, plz check.");
        return -1;
    }

    struct pbc_slice slice;

    pbc_wmessage_integer(header, "rpcKind", 2, 0);
    pbc_wmessage_integer(header, "rpcOp", 0, 0);
    pbc_wmessage_integer(header, "callId", caller_id, 0);

    pbc_wmessage_buffer(header, &slice);
    *p_buffer = (char*)malloc(slice.len);
    memcpy(*p_buffer, slice.buffer, slice.len);
    *size = slice.len;

    pbc_wmessage_delete(header);
    return 0;
}

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
    char** pbuffer, 
    int* size) {
    
    struct pbc_wmessage* rmsg;
    if (strcmp(hadoop_version, APACHE_HADOOP_202_VER) == 0) {
        rmsg = pbc_wmessage_new(env, "HadoopRpcRequestProto"); 
    } else {
        rmsg = pbc_wmessage_new(env, "hadoop.common.HadoopRpcRequestProto");
    }

    if (!rmsg) {
        opal_output(0, "current env not contains hadoop.common.HadoopRpcRequestProto, plz check.\n");
        return -1;
    }
    struct pbc_slice slice;

    pbc_wmessage_string(rmsg, "methodName", method, 0);
    pbc_wmessage_string(rmsg, "request", request, request_len);
    pbc_wmessage_string(rmsg, "declaringClassProtocolName", protocol, 0);
    pbc_wmessage_integer(rmsg, "clientProtocolVersion", 1, 0);

    pbc_wmessage_buffer(rmsg, &slice);
    *pbuffer = (char*)malloc(slice.len);
    memcpy(*pbuffer, slice.buffer, slice.len);
    *size = slice.len;
    pbc_wmessage_delete(rmsg);

    return 0;
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

    int read_count;
    int rc;
    struct pbc_slice slice;
    
    /* read length of header */
    rc = read_raw_varint32(proxy->socket_id, &read_count, &(slice.len));
    if ((rc != 0) || (slice.len <= 0)) {
        opal_output(0, "read response header length failed.\n");
        return RESPONSE_OTHER_ERROR;
    }

    slice.buffer = malloc(slice.len);
    if (!(slice.buffer)) {
        opal_output(0, "Out of memory when alloc.\n");
        return RESPONSE_OTHER_ERROR;
    }

    /* read header buffer from socket */
    rc = read_all(proxy->socket_id, (char*)(slice.buffer), slice.len);
    if (rc != 0) {
        opal_output(0, "read head buffer from socket failed.\n");
        free(slice.buffer);
        return RESPONSE_OTHER_ERROR;
    }

    /* de-serialize header from buffer */
    struct pbc_rmessage* m;
    if (strcmp(hadoop_version, APACHE_HADOOP_202_VER) == 0) {
        m = pbc_rmessage_new(env, "RpcResponseHeaderProto", &slice);
    } else {
        m = pbc_rmessage_new(env, "hadoop.common.RpcResponseHeaderProto", &slice);
    }
    if (!m) {
        opal_output(0, "Error : %s, \n", pbc_error(env));
        free(slice.buffer);
        return RESPONSE_OTHER_ERROR;
    }

    /* get type of response */
    int response_status = pbc_rmessage_integer(m, "status", 0, NULL);
    int response_caller_id = pbc_rmessage_integer(m, "callId", 0, NULL);
    int response_server_ipc_version = pbc_rmessage_integer(m, "serverIpcVersionNum", 0, NULL);

    /* now we can delete the header message now */
    pbc_rmessage_delete(m);
    free(slice.buffer);

    /* check caller-id if equals to previous id in proxy, if not, something wrong */
    if (response_caller_id != proxy->caller_id - 1) {
        opal_output(0, "caller-id not match, %d:%d.\n", response_caller_id, proxy->caller_id - 1);
        return RESPONSE_OTHER_ERROR;
    }

    /* check type */
    if (response_status == 0) {
        // SUCCESS, read response buffer out and return
        int response_size;
        read(proxy->socket_id, &response_size, 4);
        // transfer it to c-syle
        response_size = int_endian_swap(response_size);
        if (response_size < 0) {
            opal_output(0, "something wrong in reading size of response payload length.\n");
            return RESPONSE_OTHER_ERROR;
        }
        // check if response_size == 0, if so, maybe it's an empty response
        // like FinishApplicationMasterResponseProto
        if (0 == response_size) {
            *response = (char*)malloc(0);
            *size = response_size;
            return RESPONSE_SUCCEED;
        }
        // create response buffer and read them out
        *response = (char*)malloc(response_size);
        
        if (!(*response)) {
            opal_output(0, "out of memory when read response.\n");
            return RESPONSE_OTHER_ERROR;
        }
        rc = read_all(proxy->socket_id, *response, response_size);
        if (rc != 0) {
            opal_output(0, "error in read response payload content.\n");
            free(*response);
            return RESPONSE_OTHER_ERROR;
        }
        // set read length of response payload
        *size = response_size;
        return RESPONSE_SUCCEED;
    } else if (response_status == 1) {
        return RESPONSE_ERROR;
    } else {
        opal_output(0, "FATAL error of response, version not match, server version is:%d\n",
            response_server_ipc_version);
        return RESPONSE_FATAL;
    }
}

/* send the whole rpc payload to socket, will add header for it */
int send_rpc_request(hadoop_rpc_proxy_t* proxy, char* request_payload, int request_payload_len) {
    int rc;

    char* header = NULL;
    char* request = NULL;
    int header_len;
    int request_len;

    // generate header for hadoop_request
    rc = generate_request_header(&header, &header_len, proxy->caller_id);
    if (0 != rc) {
        opal_output(0, "generate request header failed.\n");
        return -1;
    }

    // now, write header and request to socket
    rc = write_request(proxy->socket_id, header, header_len, request_payload, request_payload_len);
    if (0 != rc) {
        opal_output(0, "write request payload to socket failed.\n");
        free(header);
        return -1;
    }
    free(header);

    // increase caller_id, wait for response
    proxy->caller_id++;

    return 0;
}

/* read error, return 0 if SUCCEED, and put error msg to params */
int read_exception(hadoop_rpc_proxy_t* proxy, 
    char** exception_class, 
    char** exception_stack) {
    int len;
    int rc;

    /* read exception_class */
    rc = read_all(proxy->socket_id, &len, 4);
    if (0 != rc) {
        opal_output(0, "read length of exception failed.\n");
        return -1;
    }
    len = int_endian_swap(len);
    *exception_class = (char*)malloc(len + 1);
    if (!(*exception_class)) {
        opal_output(0, "OOM when allocate exception class.\n");
        return -1;
    }
    rc = read_all(proxy->socket_id, *exception_class, len);
    if (0 != rc) {
        opal_output(0, "read exception class string failed.\n");
        free(*exception_class);
        return -1;
    }
    (*exception_class)[len] = '\0';

    /* read exception_stack */
    rc = read_all(proxy->socket_id, &len, 4);
    if (0 != rc) {
        opal_output(0, "read length of exception failed.\n");
        return -1;
    }
    len = int_endian_swap(len);
    *exception_stack = (char*)malloc(len + 1);
    if (!(*exception_stack)) {
        opal_output(0, "OOM when allocate exception stack.\n");
        return -1;
    }
    rc = read_all(proxy->socket_id, *exception_stack, len);
    if (0 != rc) {
        opal_output(0, "read exception class string failed.\n");
        free(*exception_stack);
        return -1;
    }
    (*exception_stack)[len] = '\0';

    // SUCCEED
    return 0;
}

void process_bad_rpc_response(hadoop_rpc_proxy_t* proxy, response_type_t type) {
    int rc;
    if (RESPONSE_ERROR == type) {
        char* exception_class = NULL;
        char* exception_stack = NULL;
        rc = read_exception(proxy, &exception_class, &exception_stack);
        if (0 != rc) {
            opal_output(0, "read error of response failed.\n");
            return;
        }
        opal_output(0, "error of response, class:%s\nstack_trace:%s\n.", exception_class, exception_stack);
        return;
    } else {
        opal_output(0, "some other error caused failed.\n");
        return;
    }
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
            opal_output(0, "app id is not defined, please check.\n");
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
            opal_output(0, "cluster time stamp is not defined, please check.\n");
            return -1;
        }
    }

    return 0;
}
