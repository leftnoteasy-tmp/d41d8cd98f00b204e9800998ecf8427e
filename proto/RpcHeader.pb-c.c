/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "RpcHeader.pb-c.h"
void   hadoop__common__rpc_request_header_proto__init
                     (Hadoop__Common__RpcRequestHeaderProto         *message)
{
  static Hadoop__Common__RpcRequestHeaderProto init_value = HADOOP__COMMON__RPC_REQUEST_HEADER_PROTO__INIT;
  *message = init_value;
}
size_t hadoop__common__rpc_request_header_proto__get_packed_size
                     (const Hadoop__Common__RpcRequestHeaderProto *message)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_request_header_proto__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t hadoop__common__rpc_request_header_proto__pack
                     (const Hadoop__Common__RpcRequestHeaderProto *message,
                      uint8_t       *out)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_request_header_proto__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t hadoop__common__rpc_request_header_proto__pack_to_buffer
                     (const Hadoop__Common__RpcRequestHeaderProto *message,
                      ProtobufCBuffer *buffer)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_request_header_proto__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Hadoop__Common__RpcRequestHeaderProto *
       hadoop__common__rpc_request_header_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Hadoop__Common__RpcRequestHeaderProto *)
     protobuf_c_message_unpack (&hadoop__common__rpc_request_header_proto__descriptor,
                                allocator, len, data);
}
void   hadoop__common__rpc_request_header_proto__free_unpacked
                     (Hadoop__Common__RpcRequestHeaderProto *message,
                      ProtobufCAllocator *allocator)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_request_header_proto__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   hadoop__common__rpc_response_header_proto__init
                     (Hadoop__Common__RpcResponseHeaderProto         *message)
{
  static Hadoop__Common__RpcResponseHeaderProto init_value = HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__INIT;
  *message = init_value;
}
size_t hadoop__common__rpc_response_header_proto__get_packed_size
                     (const Hadoop__Common__RpcResponseHeaderProto *message)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_response_header_proto__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t hadoop__common__rpc_response_header_proto__pack
                     (const Hadoop__Common__RpcResponseHeaderProto *message,
                      uint8_t       *out)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_response_header_proto__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t hadoop__common__rpc_response_header_proto__pack_to_buffer
                     (const Hadoop__Common__RpcResponseHeaderProto *message,
                      ProtobufCBuffer *buffer)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_response_header_proto__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Hadoop__Common__RpcResponseHeaderProto *
       hadoop__common__rpc_response_header_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Hadoop__Common__RpcResponseHeaderProto *)
     protobuf_c_message_unpack (&hadoop__common__rpc_response_header_proto__descriptor,
                                allocator, len, data);
}
void   hadoop__common__rpc_response_header_proto__free_unpacked
                     (Hadoop__Common__RpcResponseHeaderProto *message,
                      ProtobufCAllocator *allocator)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_response_header_proto__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   hadoop__common__rpc_sasl_proto__sasl_auth__init
                     (Hadoop__Common__RpcSaslProto__SaslAuth         *message)
{
  static Hadoop__Common__RpcSaslProto__SaslAuth init_value = HADOOP__COMMON__RPC_SASL_PROTO__SASL_AUTH__INIT;
  *message = init_value;
}
void   hadoop__common__rpc_sasl_proto__init
                     (Hadoop__Common__RpcSaslProto         *message)
{
  static Hadoop__Common__RpcSaslProto init_value = HADOOP__COMMON__RPC_SASL_PROTO__INIT;
  *message = init_value;
}
size_t hadoop__common__rpc_sasl_proto__get_packed_size
                     (const Hadoop__Common__RpcSaslProto *message)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_sasl_proto__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t hadoop__common__rpc_sasl_proto__pack
                     (const Hadoop__Common__RpcSaslProto *message,
                      uint8_t       *out)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_sasl_proto__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t hadoop__common__rpc_sasl_proto__pack_to_buffer
                     (const Hadoop__Common__RpcSaslProto *message,
                      ProtobufCBuffer *buffer)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_sasl_proto__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Hadoop__Common__RpcSaslProto *
       hadoop__common__rpc_sasl_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Hadoop__Common__RpcSaslProto *)
     protobuf_c_message_unpack (&hadoop__common__rpc_sasl_proto__descriptor,
                                allocator, len, data);
}
void   hadoop__common__rpc_sasl_proto__free_unpacked
                     (Hadoop__Common__RpcSaslProto *message,
                      ProtobufCAllocator *allocator)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &hadoop__common__rpc_sasl_proto__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
const ProtobufCEnumValue hadoop__common__rpc_request_header_proto__operation_proto__enum_values_by_number[3] =
{
  { "RPC_FINAL_PACKET", "HADOOP__COMMON__RPC_REQUEST_HEADER_PROTO__OPERATION_PROTO__RPC_FINAL_PACKET", 0 },
  { "RPC_CONTINUATION_PACKET", "HADOOP__COMMON__RPC_REQUEST_HEADER_PROTO__OPERATION_PROTO__RPC_CONTINUATION_PACKET", 1 },
  { "RPC_CLOSE_CONNECTION", "HADOOP__COMMON__RPC_REQUEST_HEADER_PROTO__OPERATION_PROTO__RPC_CLOSE_CONNECTION", 2 },
};
static const ProtobufCIntRange hadoop__common__rpc_request_header_proto__operation_proto__value_ranges[] = {
{0, 0},{0, 3}
};
const ProtobufCEnumValueIndex hadoop__common__rpc_request_header_proto__operation_proto__enum_values_by_name[3] =
{
  { "RPC_CLOSE_CONNECTION", 2 },
  { "RPC_CONTINUATION_PACKET", 1 },
  { "RPC_FINAL_PACKET", 0 },
};
const ProtobufCEnumDescriptor hadoop__common__rpc_request_header_proto__operation_proto__descriptor =
{
  PROTOBUF_C_ENUM_DESCRIPTOR_MAGIC,
  "hadoop.common.RpcRequestHeaderProto.OperationProto",
  "OperationProto",
  "Hadoop__Common__RpcRequestHeaderProto__OperationProto",
  "hadoop.common",
  3,
  hadoop__common__rpc_request_header_proto__operation_proto__enum_values_by_number,
  3,
  hadoop__common__rpc_request_header_proto__operation_proto__enum_values_by_name,
  1,
  hadoop__common__rpc_request_header_proto__operation_proto__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const int32_t hadoop__common__rpc_request_header_proto__retry_count__default_value = -1;
static const ProtobufCFieldDescriptor hadoop__common__rpc_request_header_proto__field_descriptors[5] =
{
  {
    "rpcKind",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_ENUM,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcRequestHeaderProto, has_rpckind),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcRequestHeaderProto, rpckind),
    &hadoop__common__rpc_kind_proto__descriptor,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "rpcOp",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_ENUM,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcRequestHeaderProto, has_rpcop),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcRequestHeaderProto, rpcop),
    &hadoop__common__rpc_request_header_proto__operation_proto__descriptor,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "callId",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_SINT32,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcRequestHeaderProto, callid),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "clientId",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcRequestHeaderProto, clientid),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "retryCount",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_SINT32,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcRequestHeaderProto, has_retrycount),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcRequestHeaderProto, retrycount),
    NULL,
    &hadoop__common__rpc_request_header_proto__retry_count__default_value,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned hadoop__common__rpc_request_header_proto__field_indices_by_name[] = {
  2,   /* field[2] = callId */
  3,   /* field[3] = clientId */
  4,   /* field[4] = retryCount */
  0,   /* field[0] = rpcKind */
  1,   /* field[1] = rpcOp */
};
static const ProtobufCIntRange hadoop__common__rpc_request_header_proto__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor hadoop__common__rpc_request_header_proto__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "hadoop.common.RpcRequestHeaderProto",
  "RpcRequestHeaderProto",
  "Hadoop__Common__RpcRequestHeaderProto",
  "hadoop.common",
  sizeof(Hadoop__Common__RpcRequestHeaderProto),
  5,
  hadoop__common__rpc_request_header_proto__field_descriptors,
  hadoop__common__rpc_request_header_proto__field_indices_by_name,
  1,  hadoop__common__rpc_request_header_proto__number_ranges,
  (ProtobufCMessageInit) hadoop__common__rpc_request_header_proto__init,
  NULL,NULL,NULL    /* reserved[123] */
};
const ProtobufCEnumValue hadoop__common__rpc_response_header_proto__rpc_status_proto__enum_values_by_number[3] =
{
  { "SUCCESS", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_STATUS_PROTO__SUCCESS", 0 },
  { "ERROR", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_STATUS_PROTO__ERROR", 1 },
  { "FATAL", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_STATUS_PROTO__FATAL", 2 },
};
static const ProtobufCIntRange hadoop__common__rpc_response_header_proto__rpc_status_proto__value_ranges[] = {
{0, 0},{0, 3}
};
const ProtobufCEnumValueIndex hadoop__common__rpc_response_header_proto__rpc_status_proto__enum_values_by_name[3] =
{
  { "ERROR", 1 },
  { "FATAL", 2 },
  { "SUCCESS", 0 },
};
const ProtobufCEnumDescriptor hadoop__common__rpc_response_header_proto__rpc_status_proto__descriptor =
{
  PROTOBUF_C_ENUM_DESCRIPTOR_MAGIC,
  "hadoop.common.RpcResponseHeaderProto.RpcStatusProto",
  "RpcStatusProto",
  "Hadoop__Common__RpcResponseHeaderProto__RpcStatusProto",
  "hadoop.common",
  3,
  hadoop__common__rpc_response_header_proto__rpc_status_proto__enum_values_by_number,
  3,
  hadoop__common__rpc_response_header_proto__rpc_status_proto__enum_values_by_name,
  1,
  hadoop__common__rpc_response_header_proto__rpc_status_proto__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
const ProtobufCEnumValue hadoop__common__rpc_response_header_proto__rpc_error_code_proto__enum_values_by_number[12] =
{
  { "ERROR_APPLICATION", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__ERROR_APPLICATION", 1 },
  { "ERROR_NO_SUCH_METHOD", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__ERROR_NO_SUCH_METHOD", 2 },
  { "ERROR_NO_SUCH_PROTOCOL", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__ERROR_NO_SUCH_PROTOCOL", 3 },
  { "ERROR_RPC_SERVER", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__ERROR_RPC_SERVER", 4 },
  { "ERROR_SERIALIZING_RESPONSE", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__ERROR_SERIALIZING_RESPONSE", 5 },
  { "ERROR_RPC_VERSION_MISMATCH", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__ERROR_RPC_VERSION_MISMATCH", 6 },
  { "FATAL_UNKNOWN", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__FATAL_UNKNOWN", 10 },
  { "FATAL_UNSUPPORTED_SERIALIZATION", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__FATAL_UNSUPPORTED_SERIALIZATION", 11 },
  { "FATAL_INVALID_RPC_HEADER", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__FATAL_INVALID_RPC_HEADER", 12 },
  { "FATAL_DESERIALIZING_REQUEST", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__FATAL_DESERIALIZING_REQUEST", 13 },
  { "FATAL_VERSION_MISMATCH", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__FATAL_VERSION_MISMATCH", 14 },
  { "FATAL_UNAUTHORIZED", "HADOOP__COMMON__RPC_RESPONSE_HEADER_PROTO__RPC_ERROR_CODE_PROTO__FATAL_UNAUTHORIZED", 15 },
};
static const ProtobufCIntRange hadoop__common__rpc_response_header_proto__rpc_error_code_proto__value_ranges[] = {
{1, 0},{10, 6},{0, 12}
};
const ProtobufCEnumValueIndex hadoop__common__rpc_response_header_proto__rpc_error_code_proto__enum_values_by_name[12] =
{
  { "ERROR_APPLICATION", 0 },
  { "ERROR_NO_SUCH_METHOD", 1 },
  { "ERROR_NO_SUCH_PROTOCOL", 2 },
  { "ERROR_RPC_SERVER", 3 },
  { "ERROR_RPC_VERSION_MISMATCH", 5 },
  { "ERROR_SERIALIZING_RESPONSE", 4 },
  { "FATAL_DESERIALIZING_REQUEST", 9 },
  { "FATAL_INVALID_RPC_HEADER", 8 },
  { "FATAL_UNAUTHORIZED", 11 },
  { "FATAL_UNKNOWN", 6 },
  { "FATAL_UNSUPPORTED_SERIALIZATION", 7 },
  { "FATAL_VERSION_MISMATCH", 10 },
};
const ProtobufCEnumDescriptor hadoop__common__rpc_response_header_proto__rpc_error_code_proto__descriptor =
{
  PROTOBUF_C_ENUM_DESCRIPTOR_MAGIC,
  "hadoop.common.RpcResponseHeaderProto.RpcErrorCodeProto",
  "RpcErrorCodeProto",
  "Hadoop__Common__RpcResponseHeaderProto__RpcErrorCodeProto",
  "hadoop.common",
  12,
  hadoop__common__rpc_response_header_proto__rpc_error_code_proto__enum_values_by_number,
  12,
  hadoop__common__rpc_response_header_proto__rpc_error_code_proto__enum_values_by_name,
  2,
  hadoop__common__rpc_response_header_proto__rpc_error_code_proto__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const int32_t hadoop__common__rpc_response_header_proto__retry_count__default_value = -1;
static const ProtobufCFieldDescriptor hadoop__common__rpc_response_header_proto__field_descriptors[8] =
{
  {
    "callId",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, callid),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "status",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, status),
    &hadoop__common__rpc_response_header_proto__rpc_status_proto__descriptor,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "serverIpcVersionNum",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, has_serveripcversionnum),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, serveripcversionnum),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "exceptionClassName",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, exceptionclassname),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "errorMsg",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, errormsg),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "errorDetail",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_ENUM,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, has_errordetail),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, errordetail),
    &hadoop__common__rpc_response_header_proto__rpc_error_code_proto__descriptor,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "clientId",
    7,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, has_clientid),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, clientid),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "retryCount",
    8,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_SINT32,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, has_retrycount),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcResponseHeaderProto, retrycount),
    NULL,
    &hadoop__common__rpc_response_header_proto__retry_count__default_value,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned hadoop__common__rpc_response_header_proto__field_indices_by_name[] = {
  0,   /* field[0] = callId */
  6,   /* field[6] = clientId */
  5,   /* field[5] = errorDetail */
  4,   /* field[4] = errorMsg */
  3,   /* field[3] = exceptionClassName */
  7,   /* field[7] = retryCount */
  2,   /* field[2] = serverIpcVersionNum */
  1,   /* field[1] = status */
};
static const ProtobufCIntRange hadoop__common__rpc_response_header_proto__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 8 }
};
const ProtobufCMessageDescriptor hadoop__common__rpc_response_header_proto__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "hadoop.common.RpcResponseHeaderProto",
  "RpcResponseHeaderProto",
  "Hadoop__Common__RpcResponseHeaderProto",
  "hadoop.common",
  sizeof(Hadoop__Common__RpcResponseHeaderProto),
  8,
  hadoop__common__rpc_response_header_proto__field_descriptors,
  hadoop__common__rpc_response_header_proto__field_indices_by_name,
  1,  hadoop__common__rpc_response_header_proto__number_ranges,
  (ProtobufCMessageInit) hadoop__common__rpc_response_header_proto__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor hadoop__common__rpc_sasl_proto__sasl_auth__field_descriptors[5] =
{
  {
    "method",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto__SaslAuth, method),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "mechanism",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto__SaslAuth, mechanism),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "protocol",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto__SaslAuth, protocol),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "serverId",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto__SaslAuth, serverid),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "challenge",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto__SaslAuth, has_challenge),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto__SaslAuth, challenge),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned hadoop__common__rpc_sasl_proto__sasl_auth__field_indices_by_name[] = {
  4,   /* field[4] = challenge */
  1,   /* field[1] = mechanism */
  0,   /* field[0] = method */
  2,   /* field[2] = protocol */
  3,   /* field[3] = serverId */
};
static const ProtobufCIntRange hadoop__common__rpc_sasl_proto__sasl_auth__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor hadoop__common__rpc_sasl_proto__sasl_auth__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "hadoop.common.RpcSaslProto.SaslAuth",
  "SaslAuth",
  "Hadoop__Common__RpcSaslProto__SaslAuth",
  "hadoop.common",
  sizeof(Hadoop__Common__RpcSaslProto__SaslAuth),
  5,
  hadoop__common__rpc_sasl_proto__sasl_auth__field_descriptors,
  hadoop__common__rpc_sasl_proto__sasl_auth__field_indices_by_name,
  1,  hadoop__common__rpc_sasl_proto__sasl_auth__number_ranges,
  (ProtobufCMessageInit) hadoop__common__rpc_sasl_proto__sasl_auth__init,
  NULL,NULL,NULL    /* reserved[123] */
};
const ProtobufCEnumValue hadoop__common__rpc_sasl_proto__sasl_state__enum_values_by_number[6] =
{
  { "SUCCESS", "HADOOP__COMMON__RPC_SASL_PROTO__SASL_STATE__SUCCESS", 0 },
  { "NEGOTIATE", "HADOOP__COMMON__RPC_SASL_PROTO__SASL_STATE__NEGOTIATE", 1 },
  { "INITIATE", "HADOOP__COMMON__RPC_SASL_PROTO__SASL_STATE__INITIATE", 2 },
  { "CHALLENGE", "HADOOP__COMMON__RPC_SASL_PROTO__SASL_STATE__CHALLENGE", 3 },
  { "RESPONSE", "HADOOP__COMMON__RPC_SASL_PROTO__SASL_STATE__RESPONSE", 4 },
  { "WRAP", "HADOOP__COMMON__RPC_SASL_PROTO__SASL_STATE__WRAP", 5 },
};
static const ProtobufCIntRange hadoop__common__rpc_sasl_proto__sasl_state__value_ranges[] = {
{0, 0},{0, 6}
};
const ProtobufCEnumValueIndex hadoop__common__rpc_sasl_proto__sasl_state__enum_values_by_name[6] =
{
  { "CHALLENGE", 3 },
  { "INITIATE", 2 },
  { "NEGOTIATE", 1 },
  { "RESPONSE", 4 },
  { "SUCCESS", 0 },
  { "WRAP", 5 },
};
const ProtobufCEnumDescriptor hadoop__common__rpc_sasl_proto__sasl_state__descriptor =
{
  PROTOBUF_C_ENUM_DESCRIPTOR_MAGIC,
  "hadoop.common.RpcSaslProto.SaslState",
  "SaslState",
  "Hadoop__Common__RpcSaslProto__SaslState",
  "hadoop.common",
  6,
  hadoop__common__rpc_sasl_proto__sasl_state__enum_values_by_number,
  6,
  hadoop__common__rpc_sasl_proto__sasl_state__enum_values_by_name,
  1,
  hadoop__common__rpc_sasl_proto__sasl_state__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor hadoop__common__rpc_sasl_proto__field_descriptors[4] =
{
  {
    "version",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto, has_version),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto, version),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "state",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto, state),
    &hadoop__common__rpc_sasl_proto__sasl_state__descriptor,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "token",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto, has_token),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto, token),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "auths",
    4,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto, n_auths),
    PROTOBUF_C_OFFSETOF(Hadoop__Common__RpcSaslProto, auths),
    &hadoop__common__rpc_sasl_proto__sasl_auth__descriptor,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned hadoop__common__rpc_sasl_proto__field_indices_by_name[] = {
  3,   /* field[3] = auths */
  1,   /* field[1] = state */
  2,   /* field[2] = token */
  0,   /* field[0] = version */
};
static const ProtobufCIntRange hadoop__common__rpc_sasl_proto__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor hadoop__common__rpc_sasl_proto__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "hadoop.common.RpcSaslProto",
  "RpcSaslProto",
  "Hadoop__Common__RpcSaslProto",
  "hadoop.common",
  sizeof(Hadoop__Common__RpcSaslProto),
  4,
  hadoop__common__rpc_sasl_proto__field_descriptors,
  hadoop__common__rpc_sasl_proto__field_indices_by_name,
  1,  hadoop__common__rpc_sasl_proto__number_ranges,
  (ProtobufCMessageInit) hadoop__common__rpc_sasl_proto__init,
  NULL,NULL,NULL    /* reserved[123] */
};
const ProtobufCEnumValue hadoop__common__rpc_kind_proto__enum_values_by_number[3] =
{
  { "RPC_BUILTIN", "HADOOP__COMMON__RPC_KIND_PROTO__RPC_BUILTIN", 0 },
  { "RPC_WRITABLE", "HADOOP__COMMON__RPC_KIND_PROTO__RPC_WRITABLE", 1 },
  { "RPC_PROTOCOL_BUFFER", "HADOOP__COMMON__RPC_KIND_PROTO__RPC_PROTOCOL_BUFFER", 2 },
};
static const ProtobufCIntRange hadoop__common__rpc_kind_proto__value_ranges[] = {
{0, 0},{0, 3}
};
const ProtobufCEnumValueIndex hadoop__common__rpc_kind_proto__enum_values_by_name[3] =
{
  { "RPC_BUILTIN", 0 },
  { "RPC_PROTOCOL_BUFFER", 2 },
  { "RPC_WRITABLE", 1 },
};
const ProtobufCEnumDescriptor hadoop__common__rpc_kind_proto__descriptor =
{
  PROTOBUF_C_ENUM_DESCRIPTOR_MAGIC,
  "hadoop.common.RpcKindProto",
  "RpcKindProto",
  "Hadoop__Common__RpcKindProto",
  "hadoop.common",
  3,
  hadoop__common__rpc_kind_proto__enum_values_by_number,
  3,
  hadoop__common__rpc_kind_proto__enum_values_by_name,
  1,
  hadoop__common__rpc_kind_proto__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
