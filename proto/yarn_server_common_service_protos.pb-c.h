/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_yarn_5fserver_5fcommon_5fservice_5fprotos_2eproto__INCLUDED
#define PROTOBUF_C_yarn_5fserver_5fcommon_5fservice_5fprotos_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS

#include "yarn_protos.pb-c.h"
#include "yarn_server_common_protos.pb-c.h"

typedef struct _Hadoop__Yarn__RegisterNodeManagerRequestProto Hadoop__Yarn__RegisterNodeManagerRequestProto;
typedef struct _Hadoop__Yarn__RegisterNodeManagerResponseProto Hadoop__Yarn__RegisterNodeManagerResponseProto;
typedef struct _Hadoop__Yarn__NodeHeartbeatRequestProto Hadoop__Yarn__NodeHeartbeatRequestProto;
typedef struct _Hadoop__Yarn__NodeHeartbeatResponseProto Hadoop__Yarn__NodeHeartbeatResponseProto;


/* --- enums --- */


/* --- messages --- */

struct  _Hadoop__Yarn__RegisterNodeManagerRequestProto
{
  ProtobufCMessage base;
  Hadoop__Yarn__NodeIdProto *node_id;
  protobuf_c_boolean has_http_port;
  int32_t http_port;
  Hadoop__Yarn__ResourceProto *resource;
};
#define HADOOP__YARN__REGISTER_NODE_MANAGER_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__register_node_manager_request_proto__descriptor) \
    , NULL, 0,0, NULL }


struct  _Hadoop__Yarn__RegisterNodeManagerResponseProto
{
  ProtobufCMessage base;
  Hadoop__Yarn__MasterKeyProto *container_token_master_key;
  Hadoop__Yarn__MasterKeyProto *nm_token_master_key;
  protobuf_c_boolean has_nodeaction;
  Hadoop__Yarn__NodeActionProto nodeaction;
  protobuf_c_boolean has_rm_identifier;
  int64_t rm_identifier;
  char *diagnostics_message;
};
#define HADOOP__YARN__REGISTER_NODE_MANAGER_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__register_node_manager_response_proto__descriptor) \
    , NULL, NULL, 0,0, 0,0, NULL }


struct  _Hadoop__Yarn__NodeHeartbeatRequestProto
{
  ProtobufCMessage base;
  Hadoop__Yarn__NodeStatusProto *node_status;
  Hadoop__Yarn__MasterKeyProto *last_known_container_token_master_key;
  Hadoop__Yarn__MasterKeyProto *last_known_nm_token_master_key;
};
#define HADOOP__YARN__NODE_HEARTBEAT_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__node_heartbeat_request_proto__descriptor) \
    , NULL, NULL, NULL }


struct  _Hadoop__Yarn__NodeHeartbeatResponseProto
{
  ProtobufCMessage base;
  protobuf_c_boolean has_response_id;
  int32_t response_id;
  Hadoop__Yarn__MasterKeyProto *container_token_master_key;
  Hadoop__Yarn__MasterKeyProto *nm_token_master_key;
  protobuf_c_boolean has_nodeaction;
  Hadoop__Yarn__NodeActionProto nodeaction;
  size_t n_containers_to_cleanup;
  Hadoop__Yarn__ContainerIdProto **containers_to_cleanup;
  size_t n_applications_to_cleanup;
  Hadoop__Yarn__ApplicationIdProto **applications_to_cleanup;
  protobuf_c_boolean has_nextheartbeatinterval;
  int64_t nextheartbeatinterval;
  char *diagnostics_message;
};
#define HADOOP__YARN__NODE_HEARTBEAT_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__node_heartbeat_response_proto__descriptor) \
    , 0,0, NULL, NULL, 0,0, 0,NULL, 0,NULL, 0,0, NULL }


/* Hadoop__Yarn__RegisterNodeManagerRequestProto methods */
void   hadoop__yarn__register_node_manager_request_proto__init
                     (Hadoop__Yarn__RegisterNodeManagerRequestProto         *message);
size_t hadoop__yarn__register_node_manager_request_proto__get_packed_size
                     (const Hadoop__Yarn__RegisterNodeManagerRequestProto   *message);
size_t hadoop__yarn__register_node_manager_request_proto__pack
                     (const Hadoop__Yarn__RegisterNodeManagerRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__register_node_manager_request_proto__pack_to_buffer
                     (const Hadoop__Yarn__RegisterNodeManagerRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__RegisterNodeManagerRequestProto *
       hadoop__yarn__register_node_manager_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__register_node_manager_request_proto__free_unpacked
                     (Hadoop__Yarn__RegisterNodeManagerRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__RegisterNodeManagerResponseProto methods */
void   hadoop__yarn__register_node_manager_response_proto__init
                     (Hadoop__Yarn__RegisterNodeManagerResponseProto         *message);
size_t hadoop__yarn__register_node_manager_response_proto__get_packed_size
                     (const Hadoop__Yarn__RegisterNodeManagerResponseProto   *message);
size_t hadoop__yarn__register_node_manager_response_proto__pack
                     (const Hadoop__Yarn__RegisterNodeManagerResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__register_node_manager_response_proto__pack_to_buffer
                     (const Hadoop__Yarn__RegisterNodeManagerResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__RegisterNodeManagerResponseProto *
       hadoop__yarn__register_node_manager_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__register_node_manager_response_proto__free_unpacked
                     (Hadoop__Yarn__RegisterNodeManagerResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__NodeHeartbeatRequestProto methods */
void   hadoop__yarn__node_heartbeat_request_proto__init
                     (Hadoop__Yarn__NodeHeartbeatRequestProto         *message);
size_t hadoop__yarn__node_heartbeat_request_proto__get_packed_size
                     (const Hadoop__Yarn__NodeHeartbeatRequestProto   *message);
size_t hadoop__yarn__node_heartbeat_request_proto__pack
                     (const Hadoop__Yarn__NodeHeartbeatRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__node_heartbeat_request_proto__pack_to_buffer
                     (const Hadoop__Yarn__NodeHeartbeatRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__NodeHeartbeatRequestProto *
       hadoop__yarn__node_heartbeat_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__node_heartbeat_request_proto__free_unpacked
                     (Hadoop__Yarn__NodeHeartbeatRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__NodeHeartbeatResponseProto methods */
void   hadoop__yarn__node_heartbeat_response_proto__init
                     (Hadoop__Yarn__NodeHeartbeatResponseProto         *message);
size_t hadoop__yarn__node_heartbeat_response_proto__get_packed_size
                     (const Hadoop__Yarn__NodeHeartbeatResponseProto   *message);
size_t hadoop__yarn__node_heartbeat_response_proto__pack
                     (const Hadoop__Yarn__NodeHeartbeatResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__node_heartbeat_response_proto__pack_to_buffer
                     (const Hadoop__Yarn__NodeHeartbeatResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__NodeHeartbeatResponseProto *
       hadoop__yarn__node_heartbeat_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__node_heartbeat_response_proto__free_unpacked
                     (Hadoop__Yarn__NodeHeartbeatResponseProto *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Hadoop__Yarn__RegisterNodeManagerRequestProto_Closure)
                 (const Hadoop__Yarn__RegisterNodeManagerRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__RegisterNodeManagerResponseProto_Closure)
                 (const Hadoop__Yarn__RegisterNodeManagerResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__NodeHeartbeatRequestProto_Closure)
                 (const Hadoop__Yarn__NodeHeartbeatRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__NodeHeartbeatResponseProto_Closure)
                 (const Hadoop__Yarn__NodeHeartbeatResponseProto *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor hadoop__yarn__register_node_manager_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__register_node_manager_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__node_heartbeat_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__node_heartbeat_response_proto__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_yarn_5fserver_5fcommon_5fservice_5fprotos_2eproto__INCLUDED */
