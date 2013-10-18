#include "yarn.h"

#include <stdlib.h>

int main(int argc, char** argv) {
   hadoop_rpc_proxy_t* proxy = new_hadoop_rpc_proxy(argv[1], atoi(argv[2]), CLIENT, RM);
   int rc = get_new_application(proxy);
   if (rc != 0) {
       yarn_log_error("get_new_application failed");
   }
}
