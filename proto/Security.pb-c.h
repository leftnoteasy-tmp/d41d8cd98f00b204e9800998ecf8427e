/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_Security_2eproto__INCLUDED
#define PROTOBUF_C_Security_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _Hadoop__Common__TokenProto Hadoop__Common__TokenProto;
typedef struct _Hadoop__Common__GetDelegationTokenRequestProto Hadoop__Common__GetDelegationTokenRequestProto;
typedef struct _Hadoop__Common__GetDelegationTokenResponseProto Hadoop__Common__GetDelegationTokenResponseProto;
typedef struct _Hadoop__Common__RenewDelegationTokenRequestProto Hadoop__Common__RenewDelegationTokenRequestProto;
typedef struct _Hadoop__Common__RenewDelegationTokenResponseProto Hadoop__Common__RenewDelegationTokenResponseProto;
typedef struct _Hadoop__Common__CancelDelegationTokenRequestProto Hadoop__Common__CancelDelegationTokenRequestProto;
typedef struct _Hadoop__Common__CancelDelegationTokenResponseProto Hadoop__Common__CancelDelegationTokenResponseProto;


/* --- enums --- */


/* --- messages --- */

struct  _Hadoop__Common__TokenProto
{
  ProtobufCMessage base;
  ProtobufCBinaryData identifier;
  ProtobufCBinaryData password;
  char *kind;
  char *service;
};
#define HADOOP__COMMON__TOKEN_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__token_proto__descriptor) \
    , {0,NULL}, {0,NULL}, NULL, NULL }


struct  _Hadoop__Common__GetDelegationTokenRequestProto
{
  ProtobufCMessage base;
  char *renewer;
};
#define HADOOP__COMMON__GET_DELEGATION_TOKEN_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__get_delegation_token_request_proto__descriptor) \
    , NULL }


struct  _Hadoop__Common__GetDelegationTokenResponseProto
{
  ProtobufCMessage base;
  Hadoop__Common__TokenProto *token;
};
#define HADOOP__COMMON__GET_DELEGATION_TOKEN_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__get_delegation_token_response_proto__descriptor) \
    , NULL }


struct  _Hadoop__Common__RenewDelegationTokenRequestProto
{
  ProtobufCMessage base;
  Hadoop__Common__TokenProto *token;
};
#define HADOOP__COMMON__RENEW_DELEGATION_TOKEN_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__renew_delegation_token_request_proto__descriptor) \
    , NULL }


struct  _Hadoop__Common__RenewDelegationTokenResponseProto
{
  ProtobufCMessage base;
  uint64_t newexpirytime;
};
#define HADOOP__COMMON__RENEW_DELEGATION_TOKEN_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__renew_delegation_token_response_proto__descriptor) \
    , 0 }


struct  _Hadoop__Common__CancelDelegationTokenRequestProto
{
  ProtobufCMessage base;
  Hadoop__Common__TokenProto *token;
};
#define HADOOP__COMMON__CANCEL_DELEGATION_TOKEN_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__cancel_delegation_token_request_proto__descriptor) \
    , NULL }


struct  _Hadoop__Common__CancelDelegationTokenResponseProto
{
  ProtobufCMessage base;
};
#define HADOOP__COMMON__CANCEL_DELEGATION_TOKEN_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__cancel_delegation_token_response_proto__descriptor) \
     }


/* Hadoop__Common__TokenProto methods */
void   hadoop__common__token_proto__init
                     (Hadoop__Common__TokenProto         *message);
size_t hadoop__common__token_proto__get_packed_size
                     (const Hadoop__Common__TokenProto   *message);
size_t hadoop__common__token_proto__pack
                     (const Hadoop__Common__TokenProto   *message,
                      uint8_t             *out);
size_t hadoop__common__token_proto__pack_to_buffer
                     (const Hadoop__Common__TokenProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__TokenProto *
       hadoop__common__token_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__token_proto__free_unpacked
                     (Hadoop__Common__TokenProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__GetDelegationTokenRequestProto methods */
void   hadoop__common__get_delegation_token_request_proto__init
                     (Hadoop__Common__GetDelegationTokenRequestProto         *message);
size_t hadoop__common__get_delegation_token_request_proto__get_packed_size
                     (const Hadoop__Common__GetDelegationTokenRequestProto   *message);
size_t hadoop__common__get_delegation_token_request_proto__pack
                     (const Hadoop__Common__GetDelegationTokenRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__get_delegation_token_request_proto__pack_to_buffer
                     (const Hadoop__Common__GetDelegationTokenRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GetDelegationTokenRequestProto *
       hadoop__common__get_delegation_token_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__get_delegation_token_request_proto__free_unpacked
                     (Hadoop__Common__GetDelegationTokenRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__GetDelegationTokenResponseProto methods */
void   hadoop__common__get_delegation_token_response_proto__init
                     (Hadoop__Common__GetDelegationTokenResponseProto         *message);
size_t hadoop__common__get_delegation_token_response_proto__get_packed_size
                     (const Hadoop__Common__GetDelegationTokenResponseProto   *message);
size_t hadoop__common__get_delegation_token_response_proto__pack
                     (const Hadoop__Common__GetDelegationTokenResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__get_delegation_token_response_proto__pack_to_buffer
                     (const Hadoop__Common__GetDelegationTokenResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GetDelegationTokenResponseProto *
       hadoop__common__get_delegation_token_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__get_delegation_token_response_proto__free_unpacked
                     (Hadoop__Common__GetDelegationTokenResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__RenewDelegationTokenRequestProto methods */
void   hadoop__common__renew_delegation_token_request_proto__init
                     (Hadoop__Common__RenewDelegationTokenRequestProto         *message);
size_t hadoop__common__renew_delegation_token_request_proto__get_packed_size
                     (const Hadoop__Common__RenewDelegationTokenRequestProto   *message);
size_t hadoop__common__renew_delegation_token_request_proto__pack
                     (const Hadoop__Common__RenewDelegationTokenRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__renew_delegation_token_request_proto__pack_to_buffer
                     (const Hadoop__Common__RenewDelegationTokenRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__RenewDelegationTokenRequestProto *
       hadoop__common__renew_delegation_token_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__renew_delegation_token_request_proto__free_unpacked
                     (Hadoop__Common__RenewDelegationTokenRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__RenewDelegationTokenResponseProto methods */
void   hadoop__common__renew_delegation_token_response_proto__init
                     (Hadoop__Common__RenewDelegationTokenResponseProto         *message);
size_t hadoop__common__renew_delegation_token_response_proto__get_packed_size
                     (const Hadoop__Common__RenewDelegationTokenResponseProto   *message);
size_t hadoop__common__renew_delegation_token_response_proto__pack
                     (const Hadoop__Common__RenewDelegationTokenResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__renew_delegation_token_response_proto__pack_to_buffer
                     (const Hadoop__Common__RenewDelegationTokenResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__RenewDelegationTokenResponseProto *
       hadoop__common__renew_delegation_token_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__renew_delegation_token_response_proto__free_unpacked
                     (Hadoop__Common__RenewDelegationTokenResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__CancelDelegationTokenRequestProto methods */
void   hadoop__common__cancel_delegation_token_request_proto__init
                     (Hadoop__Common__CancelDelegationTokenRequestProto         *message);
size_t hadoop__common__cancel_delegation_token_request_proto__get_packed_size
                     (const Hadoop__Common__CancelDelegationTokenRequestProto   *message);
size_t hadoop__common__cancel_delegation_token_request_proto__pack
                     (const Hadoop__Common__CancelDelegationTokenRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__cancel_delegation_token_request_proto__pack_to_buffer
                     (const Hadoop__Common__CancelDelegationTokenRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__CancelDelegationTokenRequestProto *
       hadoop__common__cancel_delegation_token_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__cancel_delegation_token_request_proto__free_unpacked
                     (Hadoop__Common__CancelDelegationTokenRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__CancelDelegationTokenResponseProto methods */
void   hadoop__common__cancel_delegation_token_response_proto__init
                     (Hadoop__Common__CancelDelegationTokenResponseProto         *message);
size_t hadoop__common__cancel_delegation_token_response_proto__get_packed_size
                     (const Hadoop__Common__CancelDelegationTokenResponseProto   *message);
size_t hadoop__common__cancel_delegation_token_response_proto__pack
                     (const Hadoop__Common__CancelDelegationTokenResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__cancel_delegation_token_response_proto__pack_to_buffer
                     (const Hadoop__Common__CancelDelegationTokenResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__CancelDelegationTokenResponseProto *
       hadoop__common__cancel_delegation_token_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__cancel_delegation_token_response_proto__free_unpacked
                     (Hadoop__Common__CancelDelegationTokenResponseProto *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Hadoop__Common__TokenProto_Closure)
                 (const Hadoop__Common__TokenProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__GetDelegationTokenRequestProto_Closure)
                 (const Hadoop__Common__GetDelegationTokenRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__GetDelegationTokenResponseProto_Closure)
                 (const Hadoop__Common__GetDelegationTokenResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__RenewDelegationTokenRequestProto_Closure)
                 (const Hadoop__Common__RenewDelegationTokenRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__RenewDelegationTokenResponseProto_Closure)
                 (const Hadoop__Common__RenewDelegationTokenResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__CancelDelegationTokenRequestProto_Closure)
                 (const Hadoop__Common__CancelDelegationTokenRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__CancelDelegationTokenResponseProto_Closure)
                 (const Hadoop__Common__CancelDelegationTokenResponseProto *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor hadoop__common__token_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__get_delegation_token_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__get_delegation_token_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__renew_delegation_token_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__renew_delegation_token_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__cancel_delegation_token_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__cancel_delegation_token_response_proto__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_Security_2eproto__INCLUDED */
