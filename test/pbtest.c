#include "RpcHeader.pb-c.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // make a header
    Hadoop__Common__RpcRequestHeaderProto header = HADOOP__COMMON__RPC_REQUEST_HEADER_PROTO__INIT;
    header.rpckind = 2;
    header.has_rpckind = 1;
    header.rpcop = 0;
    header.callid = -3;
    header.has_retrycount = 1;
    header.retrycount = -3;

    header.clientid.len = 0;
    header.clientid.data = NULL;

    // serialize it
    size_t msg_len = hadoop__common__rpc_request_header_proto__get_packed_size(&header);
    char* buffer = malloc(msg_len);
    hadoop__common__rpc_request_header_proto__pack(&header, buffer);

    // de-serialize it
    Hadoop__Common__RpcRequestHeaderProto* msg = hadoop__common__rpc_request_header_proto__unpack(NULL, msg_len, buffer);
    
    printf("has rpckind:%d\n", msg->has_rpckind);
    printf("rpckind:%d\n", msg->rpckind);
    printf("has retrycount:%d\n", msg->has_retrycount);
    printf("retrycount:%d\n", msg->retrycount);

    int i;
    for (i = 0; i < msg_len; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}