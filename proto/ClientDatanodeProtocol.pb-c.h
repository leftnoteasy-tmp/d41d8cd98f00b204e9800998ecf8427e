/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_ClientDatanodeProtocol_2eproto__INCLUDED
#define PROTOBUF_C_ClientDatanodeProtocol_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS

#include "Security.pb-c.h"
#include "hdfs.pb-c.h"

typedef struct _Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto;
typedef struct _Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto;
typedef struct _Hadoop__Hdfs__RefreshNamenodesRequestProto Hadoop__Hdfs__RefreshNamenodesRequestProto;
typedef struct _Hadoop__Hdfs__RefreshNamenodesResponseProto Hadoop__Hdfs__RefreshNamenodesResponseProto;
typedef struct _Hadoop__Hdfs__DeleteBlockPoolRequestProto Hadoop__Hdfs__DeleteBlockPoolRequestProto;
typedef struct _Hadoop__Hdfs__DeleteBlockPoolResponseProto Hadoop__Hdfs__DeleteBlockPoolResponseProto;
typedef struct _Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto;
typedef struct _Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto;
typedef struct _Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto;
typedef struct _Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto;


/* --- enums --- */


/* --- messages --- */

struct  _Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto
{
  ProtobufCMessage base;
  Hadoop__Hdfs__ExtendedBlockProto *block;
};
#define HADOOP__HDFS__GET_REPLICA_VISIBLE_LENGTH_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__get_replica_visible_length_request_proto__descriptor) \
    , NULL }


struct  _Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto
{
  ProtobufCMessage base;
  uint64_t length;
};
#define HADOOP__HDFS__GET_REPLICA_VISIBLE_LENGTH_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__get_replica_visible_length_response_proto__descriptor) \
    , 0 }


struct  _Hadoop__Hdfs__RefreshNamenodesRequestProto
{
  ProtobufCMessage base;
};
#define HADOOP__HDFS__REFRESH_NAMENODES_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__refresh_namenodes_request_proto__descriptor) \
     }


struct  _Hadoop__Hdfs__RefreshNamenodesResponseProto
{
  ProtobufCMessage base;
};
#define HADOOP__HDFS__REFRESH_NAMENODES_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__refresh_namenodes_response_proto__descriptor) \
     }


struct  _Hadoop__Hdfs__DeleteBlockPoolRequestProto
{
  ProtobufCMessage base;
  char *blockpool;
  protobuf_c_boolean force;
};
#define HADOOP__HDFS__DELETE_BLOCK_POOL_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__delete_block_pool_request_proto__descriptor) \
    , NULL, 0 }


struct  _Hadoop__Hdfs__DeleteBlockPoolResponseProto
{
  ProtobufCMessage base;
};
#define HADOOP__HDFS__DELETE_BLOCK_POOL_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__delete_block_pool_response_proto__descriptor) \
     }


struct  _Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto
{
  ProtobufCMessage base;
  Hadoop__Hdfs__ExtendedBlockProto *block;
  Hadoop__Common__TokenProto *token;
};
#define HADOOP__HDFS__GET_BLOCK_LOCAL_PATH_INFO_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__get_block_local_path_info_request_proto__descriptor) \
    , NULL, NULL }


struct  _Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto
{
  ProtobufCMessage base;
  Hadoop__Hdfs__ExtendedBlockProto *block;
  char *localpath;
  char *localmetapath;
};
#define HADOOP__HDFS__GET_BLOCK_LOCAL_PATH_INFO_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__get_block_local_path_info_response_proto__descriptor) \
    , NULL, NULL, NULL }


struct  _Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto
{
  ProtobufCMessage base;
  size_t n_blocks;
  Hadoop__Hdfs__ExtendedBlockProto **blocks;
  size_t n_tokens;
  Hadoop__Common__TokenProto **tokens;
};
#define HADOOP__HDFS__GET_HDFS_BLOCK_LOCATIONS_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__get_hdfs_block_locations_request_proto__descriptor) \
    , 0,NULL, 0,NULL }


struct  _Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto
{
  ProtobufCMessage base;
  size_t n_volumeids;
  ProtobufCBinaryData *volumeids;
  size_t n_volumeindexes;
  uint32_t *volumeindexes;
};
#define HADOOP__HDFS__GET_HDFS_BLOCK_LOCATIONS_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__get_hdfs_block_locations_response_proto__descriptor) \
    , 0,NULL, 0,NULL }


/* Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto methods */
void   hadoop__hdfs__get_replica_visible_length_request_proto__init
                     (Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto         *message);
size_t hadoop__hdfs__get_replica_visible_length_request_proto__get_packed_size
                     (const Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto   *message);
size_t hadoop__hdfs__get_replica_visible_length_request_proto__pack
                     (const Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__get_replica_visible_length_request_proto__pack_to_buffer
                     (const Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto *
       hadoop__hdfs__get_replica_visible_length_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__get_replica_visible_length_request_proto__free_unpacked
                     (Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto methods */
void   hadoop__hdfs__get_replica_visible_length_response_proto__init
                     (Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto         *message);
size_t hadoop__hdfs__get_replica_visible_length_response_proto__get_packed_size
                     (const Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto   *message);
size_t hadoop__hdfs__get_replica_visible_length_response_proto__pack
                     (const Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__get_replica_visible_length_response_proto__pack_to_buffer
                     (const Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto *
       hadoop__hdfs__get_replica_visible_length_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__get_replica_visible_length_response_proto__free_unpacked
                     (Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Hdfs__RefreshNamenodesRequestProto methods */
void   hadoop__hdfs__refresh_namenodes_request_proto__init
                     (Hadoop__Hdfs__RefreshNamenodesRequestProto         *message);
size_t hadoop__hdfs__refresh_namenodes_request_proto__get_packed_size
                     (const Hadoop__Hdfs__RefreshNamenodesRequestProto   *message);
size_t hadoop__hdfs__refresh_namenodes_request_proto__pack
                     (const Hadoop__Hdfs__RefreshNamenodesRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__refresh_namenodes_request_proto__pack_to_buffer
                     (const Hadoop__Hdfs__RefreshNamenodesRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__RefreshNamenodesRequestProto *
       hadoop__hdfs__refresh_namenodes_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__refresh_namenodes_request_proto__free_unpacked
                     (Hadoop__Hdfs__RefreshNamenodesRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Hdfs__RefreshNamenodesResponseProto methods */
void   hadoop__hdfs__refresh_namenodes_response_proto__init
                     (Hadoop__Hdfs__RefreshNamenodesResponseProto         *message);
size_t hadoop__hdfs__refresh_namenodes_response_proto__get_packed_size
                     (const Hadoop__Hdfs__RefreshNamenodesResponseProto   *message);
size_t hadoop__hdfs__refresh_namenodes_response_proto__pack
                     (const Hadoop__Hdfs__RefreshNamenodesResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__refresh_namenodes_response_proto__pack_to_buffer
                     (const Hadoop__Hdfs__RefreshNamenodesResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__RefreshNamenodesResponseProto *
       hadoop__hdfs__refresh_namenodes_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__refresh_namenodes_response_proto__free_unpacked
                     (Hadoop__Hdfs__RefreshNamenodesResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Hdfs__DeleteBlockPoolRequestProto methods */
void   hadoop__hdfs__delete_block_pool_request_proto__init
                     (Hadoop__Hdfs__DeleteBlockPoolRequestProto         *message);
size_t hadoop__hdfs__delete_block_pool_request_proto__get_packed_size
                     (const Hadoop__Hdfs__DeleteBlockPoolRequestProto   *message);
size_t hadoop__hdfs__delete_block_pool_request_proto__pack
                     (const Hadoop__Hdfs__DeleteBlockPoolRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__delete_block_pool_request_proto__pack_to_buffer
                     (const Hadoop__Hdfs__DeleteBlockPoolRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__DeleteBlockPoolRequestProto *
       hadoop__hdfs__delete_block_pool_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__delete_block_pool_request_proto__free_unpacked
                     (Hadoop__Hdfs__DeleteBlockPoolRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Hdfs__DeleteBlockPoolResponseProto methods */
void   hadoop__hdfs__delete_block_pool_response_proto__init
                     (Hadoop__Hdfs__DeleteBlockPoolResponseProto         *message);
size_t hadoop__hdfs__delete_block_pool_response_proto__get_packed_size
                     (const Hadoop__Hdfs__DeleteBlockPoolResponseProto   *message);
size_t hadoop__hdfs__delete_block_pool_response_proto__pack
                     (const Hadoop__Hdfs__DeleteBlockPoolResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__delete_block_pool_response_proto__pack_to_buffer
                     (const Hadoop__Hdfs__DeleteBlockPoolResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__DeleteBlockPoolResponseProto *
       hadoop__hdfs__delete_block_pool_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__delete_block_pool_response_proto__free_unpacked
                     (Hadoop__Hdfs__DeleteBlockPoolResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto methods */
void   hadoop__hdfs__get_block_local_path_info_request_proto__init
                     (Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto         *message);
size_t hadoop__hdfs__get_block_local_path_info_request_proto__get_packed_size
                     (const Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto   *message);
size_t hadoop__hdfs__get_block_local_path_info_request_proto__pack
                     (const Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__get_block_local_path_info_request_proto__pack_to_buffer
                     (const Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto *
       hadoop__hdfs__get_block_local_path_info_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__get_block_local_path_info_request_proto__free_unpacked
                     (Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto methods */
void   hadoop__hdfs__get_block_local_path_info_response_proto__init
                     (Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto         *message);
size_t hadoop__hdfs__get_block_local_path_info_response_proto__get_packed_size
                     (const Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto   *message);
size_t hadoop__hdfs__get_block_local_path_info_response_proto__pack
                     (const Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__get_block_local_path_info_response_proto__pack_to_buffer
                     (const Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto *
       hadoop__hdfs__get_block_local_path_info_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__get_block_local_path_info_response_proto__free_unpacked
                     (Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto methods */
void   hadoop__hdfs__get_hdfs_block_locations_request_proto__init
                     (Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto         *message);
size_t hadoop__hdfs__get_hdfs_block_locations_request_proto__get_packed_size
                     (const Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto   *message);
size_t hadoop__hdfs__get_hdfs_block_locations_request_proto__pack
                     (const Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__get_hdfs_block_locations_request_proto__pack_to_buffer
                     (const Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto *
       hadoop__hdfs__get_hdfs_block_locations_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__get_hdfs_block_locations_request_proto__free_unpacked
                     (Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto methods */
void   hadoop__hdfs__get_hdfs_block_locations_response_proto__init
                     (Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto         *message);
size_t hadoop__hdfs__get_hdfs_block_locations_response_proto__get_packed_size
                     (const Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto   *message);
size_t hadoop__hdfs__get_hdfs_block_locations_response_proto__pack
                     (const Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__get_hdfs_block_locations_response_proto__pack_to_buffer
                     (const Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto *
       hadoop__hdfs__get_hdfs_block_locations_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__get_hdfs_block_locations_response_proto__free_unpacked
                     (Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto_Closure)
                 (const Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto_Closure)
                 (const Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Hdfs__RefreshNamenodesRequestProto_Closure)
                 (const Hadoop__Hdfs__RefreshNamenodesRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Hdfs__RefreshNamenodesResponseProto_Closure)
                 (const Hadoop__Hdfs__RefreshNamenodesResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Hdfs__DeleteBlockPoolRequestProto_Closure)
                 (const Hadoop__Hdfs__DeleteBlockPoolRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Hdfs__DeleteBlockPoolResponseProto_Closure)
                 (const Hadoop__Hdfs__DeleteBlockPoolResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto_Closure)
                 (const Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto_Closure)
                 (const Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto_Closure)
                 (const Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto_Closure)
                 (const Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto *message,
                  void *closure_data);

/* --- services --- */

typedef struct _Hadoop__Hdfs__ClientDatanodeProtocolService_Service Hadoop__Hdfs__ClientDatanodeProtocolService_Service;
struct _Hadoop__Hdfs__ClientDatanodeProtocolService_Service
{
  ProtobufCService base;
  void (*get_replica_visible_length)(Hadoop__Hdfs__ClientDatanodeProtocolService_Service *service,
                                     const Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto *input,
                                     Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto_Closure closure,
                                     void *closure_data);
  void (*refresh_namenodes)(Hadoop__Hdfs__ClientDatanodeProtocolService_Service *service,
                            const Hadoop__Hdfs__RefreshNamenodesRequestProto *input,
                            Hadoop__Hdfs__RefreshNamenodesResponseProto_Closure closure,
                            void *closure_data);
  void (*delete_block_pool)(Hadoop__Hdfs__ClientDatanodeProtocolService_Service *service,
                            const Hadoop__Hdfs__DeleteBlockPoolRequestProto *input,
                            Hadoop__Hdfs__DeleteBlockPoolResponseProto_Closure closure,
                            void *closure_data);
  void (*get_block_local_path_info)(Hadoop__Hdfs__ClientDatanodeProtocolService_Service *service,
                                    const Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto *input,
                                    Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto_Closure closure,
                                    void *closure_data);
  void (*get_hdfs_block_locations)(Hadoop__Hdfs__ClientDatanodeProtocolService_Service *service,
                                   const Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto *input,
                                   Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto_Closure closure,
                                   void *closure_data);
};
typedef void (*Hadoop__Hdfs__ClientDatanodeProtocolService_ServiceDestroy)(Hadoop__Hdfs__ClientDatanodeProtocolService_Service *);
void hadoop__hdfs__client_datanode_protocol_service__init (Hadoop__Hdfs__ClientDatanodeProtocolService_Service *service,
                                                           Hadoop__Hdfs__ClientDatanodeProtocolService_ServiceDestroy destroy);
#define HADOOP__HDFS__CLIENT_DATANODE_PROTOCOL_SERVICE__BASE_INIT \
    { &hadoop__hdfs__client_datanode_protocol_service__descriptor, protobuf_c_service_invoke_internal, NULL }
#define HADOOP__HDFS__CLIENT_DATANODE_PROTOCOL_SERVICE__INIT(function_prefix__) \
    { HADOOP__HDFS__CLIENT_DATANODE_PROTOCOL_SERVICE__BASE_INIT,\
      function_prefix__ ## get_replica_visible_length,\
      function_prefix__ ## refresh_namenodes,\
      function_prefix__ ## delete_block_pool,\
      function_prefix__ ## get_block_local_path_info,\
      function_prefix__ ## get_hdfs_block_locations  }
void hadoop__hdfs__client_datanode_protocol_service__get_replica_visible_length(ProtobufCService *service,
                                                                                const Hadoop__Hdfs__GetReplicaVisibleLengthRequestProto *input,
                                                                                Hadoop__Hdfs__GetReplicaVisibleLengthResponseProto_Closure closure,
                                                                                void *closure_data);
void hadoop__hdfs__client_datanode_protocol_service__refresh_namenodes(ProtobufCService *service,
                                                                       const Hadoop__Hdfs__RefreshNamenodesRequestProto *input,
                                                                       Hadoop__Hdfs__RefreshNamenodesResponseProto_Closure closure,
                                                                       void *closure_data);
void hadoop__hdfs__client_datanode_protocol_service__delete_block_pool(ProtobufCService *service,
                                                                       const Hadoop__Hdfs__DeleteBlockPoolRequestProto *input,
                                                                       Hadoop__Hdfs__DeleteBlockPoolResponseProto_Closure closure,
                                                                       void *closure_data);
void hadoop__hdfs__client_datanode_protocol_service__get_block_local_path_info(ProtobufCService *service,
                                                                               const Hadoop__Hdfs__GetBlockLocalPathInfoRequestProto *input,
                                                                               Hadoop__Hdfs__GetBlockLocalPathInfoResponseProto_Closure closure,
                                                                               void *closure_data);
void hadoop__hdfs__client_datanode_protocol_service__get_hdfs_block_locations(ProtobufCService *service,
                                                                              const Hadoop__Hdfs__GetHdfsBlockLocationsRequestProto *input,
                                                                              Hadoop__Hdfs__GetHdfsBlockLocationsResponseProto_Closure closure,
                                                                              void *closure_data);

/* --- descriptors --- */

extern const ProtobufCMessageDescriptor hadoop__hdfs__get_replica_visible_length_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__hdfs__get_replica_visible_length_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__hdfs__refresh_namenodes_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__hdfs__refresh_namenodes_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__hdfs__delete_block_pool_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__hdfs__delete_block_pool_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__hdfs__get_block_local_path_info_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__hdfs__get_block_local_path_info_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__hdfs__get_hdfs_block_locations_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__hdfs__get_hdfs_block_locations_response_proto__descriptor;
extern const ProtobufCServiceDescriptor hadoop__hdfs__client_datanode_protocol_service__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_ClientDatanodeProtocol_2eproto__INCLUDED */
