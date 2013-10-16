/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_ProtocolInfo_2eproto__INCLUDED
#define PROTOBUF_C_ProtocolInfo_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _Hadoop__Common__GetProtocolVersionsRequestProto Hadoop__Common__GetProtocolVersionsRequestProto;
typedef struct _Hadoop__Common__ProtocolVersionProto Hadoop__Common__ProtocolVersionProto;
typedef struct _Hadoop__Common__GetProtocolVersionsResponseProto Hadoop__Common__GetProtocolVersionsResponseProto;
typedef struct _Hadoop__Common__GetProtocolSignatureRequestProto Hadoop__Common__GetProtocolSignatureRequestProto;
typedef struct _Hadoop__Common__GetProtocolSignatureResponseProto Hadoop__Common__GetProtocolSignatureResponseProto;
typedef struct _Hadoop__Common__ProtocolSignatureProto Hadoop__Common__ProtocolSignatureProto;


/* --- enums --- */


/* --- messages --- */

struct  _Hadoop__Common__GetProtocolVersionsRequestProto
{
  ProtobufCMessage base;
  char *protocol;
};
#define HADOOP__COMMON__GET_PROTOCOL_VERSIONS_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__get_protocol_versions_request_proto__descriptor) \
    , NULL }


struct  _Hadoop__Common__ProtocolVersionProto
{
  ProtobufCMessage base;
  char *rpckind;
  size_t n_versions;
  uint64_t *versions;
};
#define HADOOP__COMMON__PROTOCOL_VERSION_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__protocol_version_proto__descriptor) \
    , NULL, 0,NULL }


struct  _Hadoop__Common__GetProtocolVersionsResponseProto
{
  ProtobufCMessage base;
  size_t n_protocolversions;
  Hadoop__Common__ProtocolVersionProto **protocolversions;
};
#define HADOOP__COMMON__GET_PROTOCOL_VERSIONS_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__get_protocol_versions_response_proto__descriptor) \
    , 0,NULL }


struct  _Hadoop__Common__GetProtocolSignatureRequestProto
{
  ProtobufCMessage base;
  char *protocol;
  char *rpckind;
};
#define HADOOP__COMMON__GET_PROTOCOL_SIGNATURE_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__get_protocol_signature_request_proto__descriptor) \
    , NULL, NULL }


struct  _Hadoop__Common__GetProtocolSignatureResponseProto
{
  ProtobufCMessage base;
  size_t n_protocolsignature;
  Hadoop__Common__ProtocolSignatureProto **protocolsignature;
};
#define HADOOP__COMMON__GET_PROTOCOL_SIGNATURE_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__get_protocol_signature_response_proto__descriptor) \
    , 0,NULL }


struct  _Hadoop__Common__ProtocolSignatureProto
{
  ProtobufCMessage base;
  uint64_t version;
  size_t n_methods;
  uint32_t *methods;
};
#define HADOOP__COMMON__PROTOCOL_SIGNATURE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__protocol_signature_proto__descriptor) \
    , 0, 0,NULL }


/* Hadoop__Common__GetProtocolVersionsRequestProto methods */
void   hadoop__common__get_protocol_versions_request_proto__init
                     (Hadoop__Common__GetProtocolVersionsRequestProto         *message);
size_t hadoop__common__get_protocol_versions_request_proto__get_packed_size
                     (const Hadoop__Common__GetProtocolVersionsRequestProto   *message);
size_t hadoop__common__get_protocol_versions_request_proto__pack
                     (const Hadoop__Common__GetProtocolVersionsRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__get_protocol_versions_request_proto__pack_to_buffer
                     (const Hadoop__Common__GetProtocolVersionsRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GetProtocolVersionsRequestProto *
       hadoop__common__get_protocol_versions_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__get_protocol_versions_request_proto__free_unpacked
                     (Hadoop__Common__GetProtocolVersionsRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__ProtocolVersionProto methods */
void   hadoop__common__protocol_version_proto__init
                     (Hadoop__Common__ProtocolVersionProto         *message);
size_t hadoop__common__protocol_version_proto__get_packed_size
                     (const Hadoop__Common__ProtocolVersionProto   *message);
size_t hadoop__common__protocol_version_proto__pack
                     (const Hadoop__Common__ProtocolVersionProto   *message,
                      uint8_t             *out);
size_t hadoop__common__protocol_version_proto__pack_to_buffer
                     (const Hadoop__Common__ProtocolVersionProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__ProtocolVersionProto *
       hadoop__common__protocol_version_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__protocol_version_proto__free_unpacked
                     (Hadoop__Common__ProtocolVersionProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__GetProtocolVersionsResponseProto methods */
void   hadoop__common__get_protocol_versions_response_proto__init
                     (Hadoop__Common__GetProtocolVersionsResponseProto         *message);
size_t hadoop__common__get_protocol_versions_response_proto__get_packed_size
                     (const Hadoop__Common__GetProtocolVersionsResponseProto   *message);
size_t hadoop__common__get_protocol_versions_response_proto__pack
                     (const Hadoop__Common__GetProtocolVersionsResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__get_protocol_versions_response_proto__pack_to_buffer
                     (const Hadoop__Common__GetProtocolVersionsResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GetProtocolVersionsResponseProto *
       hadoop__common__get_protocol_versions_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__get_protocol_versions_response_proto__free_unpacked
                     (Hadoop__Common__GetProtocolVersionsResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__GetProtocolSignatureRequestProto methods */
void   hadoop__common__get_protocol_signature_request_proto__init
                     (Hadoop__Common__GetProtocolSignatureRequestProto         *message);
size_t hadoop__common__get_protocol_signature_request_proto__get_packed_size
                     (const Hadoop__Common__GetProtocolSignatureRequestProto   *message);
size_t hadoop__common__get_protocol_signature_request_proto__pack
                     (const Hadoop__Common__GetProtocolSignatureRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__get_protocol_signature_request_proto__pack_to_buffer
                     (const Hadoop__Common__GetProtocolSignatureRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GetProtocolSignatureRequestProto *
       hadoop__common__get_protocol_signature_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__get_protocol_signature_request_proto__free_unpacked
                     (Hadoop__Common__GetProtocolSignatureRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__GetProtocolSignatureResponseProto methods */
void   hadoop__common__get_protocol_signature_response_proto__init
                     (Hadoop__Common__GetProtocolSignatureResponseProto         *message);
size_t hadoop__common__get_protocol_signature_response_proto__get_packed_size
                     (const Hadoop__Common__GetProtocolSignatureResponseProto   *message);
size_t hadoop__common__get_protocol_signature_response_proto__pack
                     (const Hadoop__Common__GetProtocolSignatureResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__get_protocol_signature_response_proto__pack_to_buffer
                     (const Hadoop__Common__GetProtocolSignatureResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GetProtocolSignatureResponseProto *
       hadoop__common__get_protocol_signature_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__get_protocol_signature_response_proto__free_unpacked
                     (Hadoop__Common__GetProtocolSignatureResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__ProtocolSignatureProto methods */
void   hadoop__common__protocol_signature_proto__init
                     (Hadoop__Common__ProtocolSignatureProto         *message);
size_t hadoop__common__protocol_signature_proto__get_packed_size
                     (const Hadoop__Common__ProtocolSignatureProto   *message);
size_t hadoop__common__protocol_signature_proto__pack
                     (const Hadoop__Common__ProtocolSignatureProto   *message,
                      uint8_t             *out);
size_t hadoop__common__protocol_signature_proto__pack_to_buffer
                     (const Hadoop__Common__ProtocolSignatureProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__ProtocolSignatureProto *
       hadoop__common__protocol_signature_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__protocol_signature_proto__free_unpacked
                     (Hadoop__Common__ProtocolSignatureProto *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Hadoop__Common__GetProtocolVersionsRequestProto_Closure)
                 (const Hadoop__Common__GetProtocolVersionsRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__ProtocolVersionProto_Closure)
                 (const Hadoop__Common__ProtocolVersionProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__GetProtocolVersionsResponseProto_Closure)
                 (const Hadoop__Common__GetProtocolVersionsResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__GetProtocolSignatureRequestProto_Closure)
                 (const Hadoop__Common__GetProtocolSignatureRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__GetProtocolSignatureResponseProto_Closure)
                 (const Hadoop__Common__GetProtocolSignatureResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__ProtocolSignatureProto_Closure)
                 (const Hadoop__Common__ProtocolSignatureProto *message,
                  void *closure_data);

/* --- services --- */

typedef struct _Hadoop__Common__ProtocolInfoService_Service Hadoop__Common__ProtocolInfoService_Service;
struct _Hadoop__Common__ProtocolInfoService_Service
{
  ProtobufCService base;
  void (*get_protocol_versions)(Hadoop__Common__ProtocolInfoService_Service *service,
                                const Hadoop__Common__GetProtocolVersionsRequestProto *input,
                                Hadoop__Common__GetProtocolVersionsResponseProto_Closure closure,
                                void *closure_data);
  void (*get_protocol_signature)(Hadoop__Common__ProtocolInfoService_Service *service,
                                 const Hadoop__Common__GetProtocolSignatureRequestProto *input,
                                 Hadoop__Common__GetProtocolSignatureResponseProto_Closure closure,
                                 void *closure_data);
};
typedef void (*Hadoop__Common__ProtocolInfoService_ServiceDestroy)(Hadoop__Common__ProtocolInfoService_Service *);
void hadoop__common__protocol_info_service__init (Hadoop__Common__ProtocolInfoService_Service *service,
                                                  Hadoop__Common__ProtocolInfoService_ServiceDestroy destroy);
#define HADOOP__COMMON__PROTOCOL_INFO_SERVICE__BASE_INIT \
    { &hadoop__common__protocol_info_service__descriptor, protobuf_c_service_invoke_internal, NULL }
#define HADOOP__COMMON__PROTOCOL_INFO_SERVICE__INIT(function_prefix__) \
    { HADOOP__COMMON__PROTOCOL_INFO_SERVICE__BASE_INIT,\
      function_prefix__ ## get_protocol_versions,\
      function_prefix__ ## get_protocol_signature  }
void hadoop__common__protocol_info_service__get_protocol_versions(ProtobufCService *service,
                                                                  const Hadoop__Common__GetProtocolVersionsRequestProto *input,
                                                                  Hadoop__Common__GetProtocolVersionsResponseProto_Closure closure,
                                                                  void *closure_data);
void hadoop__common__protocol_info_service__get_protocol_signature(ProtobufCService *service,
                                                                   const Hadoop__Common__GetProtocolSignatureRequestProto *input,
                                                                   Hadoop__Common__GetProtocolSignatureResponseProto_Closure closure,
                                                                   void *closure_data);

/* --- descriptors --- */

extern const ProtobufCMessageDescriptor hadoop__common__get_protocol_versions_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__protocol_version_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__get_protocol_versions_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__get_protocol_signature_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__get_protocol_signature_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__protocol_signature_proto__descriptor;
extern const ProtobufCServiceDescriptor hadoop__common__protocol_info_service__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_ProtocolInfo_2eproto__INCLUDED */
