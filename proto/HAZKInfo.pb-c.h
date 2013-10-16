/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_HAZKInfo_2eproto__INCLUDED
#define PROTOBUF_C_HAZKInfo_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _Hadoop__Hdfs__ActiveNodeInfo Hadoop__Hdfs__ActiveNodeInfo;


/* --- enums --- */


/* --- messages --- */

struct  _Hadoop__Hdfs__ActiveNodeInfo
{
  ProtobufCMessage base;
  char *nameserviceid;
  char *namenodeid;
  char *hostname;
  int32_t port;
  int32_t zkfcport;
};
#define HADOOP__HDFS__ACTIVE_NODE_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__hdfs__active_node_info__descriptor) \
    , NULL, NULL, NULL, 0, 0 }


/* Hadoop__Hdfs__ActiveNodeInfo methods */
void   hadoop__hdfs__active_node_info__init
                     (Hadoop__Hdfs__ActiveNodeInfo         *message);
size_t hadoop__hdfs__active_node_info__get_packed_size
                     (const Hadoop__Hdfs__ActiveNodeInfo   *message);
size_t hadoop__hdfs__active_node_info__pack
                     (const Hadoop__Hdfs__ActiveNodeInfo   *message,
                      uint8_t             *out);
size_t hadoop__hdfs__active_node_info__pack_to_buffer
                     (const Hadoop__Hdfs__ActiveNodeInfo   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Hdfs__ActiveNodeInfo *
       hadoop__hdfs__active_node_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__hdfs__active_node_info__free_unpacked
                     (Hadoop__Hdfs__ActiveNodeInfo *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Hadoop__Hdfs__ActiveNodeInfo_Closure)
                 (const Hadoop__Hdfs__ActiveNodeInfo *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor hadoop__hdfs__active_node_info__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_HAZKInfo_2eproto__INCLUDED */