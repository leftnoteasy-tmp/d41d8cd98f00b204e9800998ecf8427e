/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_HAServiceProtocol_2eproto__INCLUDED
#define PROTOBUF_C_HAServiceProtocol_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _Hadoop__Common__HAStateChangeRequestInfoProto Hadoop__Common__HAStateChangeRequestInfoProto;
typedef struct _Hadoop__Common__MonitorHealthRequestProto Hadoop__Common__MonitorHealthRequestProto;
typedef struct _Hadoop__Common__MonitorHealthResponseProto Hadoop__Common__MonitorHealthResponseProto;
typedef struct _Hadoop__Common__TransitionToActiveRequestProto Hadoop__Common__TransitionToActiveRequestProto;
typedef struct _Hadoop__Common__TransitionToActiveResponseProto Hadoop__Common__TransitionToActiveResponseProto;
typedef struct _Hadoop__Common__TransitionToStandbyRequestProto Hadoop__Common__TransitionToStandbyRequestProto;
typedef struct _Hadoop__Common__TransitionToStandbyResponseProto Hadoop__Common__TransitionToStandbyResponseProto;
typedef struct _Hadoop__Common__GetServiceStatusRequestProto Hadoop__Common__GetServiceStatusRequestProto;
typedef struct _Hadoop__Common__GetServiceStatusResponseProto Hadoop__Common__GetServiceStatusResponseProto;


/* --- enums --- */

typedef enum _Hadoop__Common__HAServiceStateProto {
  HADOOP__COMMON__HASERVICE_STATE_PROTO__INITIALIZING = 0,
  HADOOP__COMMON__HASERVICE_STATE_PROTO__ACTIVE = 1,
  HADOOP__COMMON__HASERVICE_STATE_PROTO__STANDBY = 2
} Hadoop__Common__HAServiceStateProto;
typedef enum _Hadoop__Common__HARequestSource {
  HADOOP__COMMON__HAREQUEST_SOURCE__REQUEST_BY_USER = 0,
  HADOOP__COMMON__HAREQUEST_SOURCE__REQUEST_BY_USER_FORCED = 1,
  HADOOP__COMMON__HAREQUEST_SOURCE__REQUEST_BY_ZKFC = 2
} Hadoop__Common__HARequestSource;

/* --- messages --- */

struct  _Hadoop__Common__HAStateChangeRequestInfoProto
{
  ProtobufCMessage base;
  Hadoop__Common__HARequestSource reqsource;
};
#define HADOOP__COMMON__HASTATE_CHANGE_REQUEST_INFO_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__hastate_change_request_info_proto__descriptor) \
    , 0 }


struct  _Hadoop__Common__MonitorHealthRequestProto
{
  ProtobufCMessage base;
};
#define HADOOP__COMMON__MONITOR_HEALTH_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__monitor_health_request_proto__descriptor) \
     }


struct  _Hadoop__Common__MonitorHealthResponseProto
{
  ProtobufCMessage base;
};
#define HADOOP__COMMON__MONITOR_HEALTH_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__monitor_health_response_proto__descriptor) \
     }


struct  _Hadoop__Common__TransitionToActiveRequestProto
{
  ProtobufCMessage base;
  Hadoop__Common__HAStateChangeRequestInfoProto *reqinfo;
};
#define HADOOP__COMMON__TRANSITION_TO_ACTIVE_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__transition_to_active_request_proto__descriptor) \
    , NULL }


struct  _Hadoop__Common__TransitionToActiveResponseProto
{
  ProtobufCMessage base;
};
#define HADOOP__COMMON__TRANSITION_TO_ACTIVE_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__transition_to_active_response_proto__descriptor) \
     }


struct  _Hadoop__Common__TransitionToStandbyRequestProto
{
  ProtobufCMessage base;
  Hadoop__Common__HAStateChangeRequestInfoProto *reqinfo;
};
#define HADOOP__COMMON__TRANSITION_TO_STANDBY_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__transition_to_standby_request_proto__descriptor) \
    , NULL }


struct  _Hadoop__Common__TransitionToStandbyResponseProto
{
  ProtobufCMessage base;
};
#define HADOOP__COMMON__TRANSITION_TO_STANDBY_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__transition_to_standby_response_proto__descriptor) \
     }


struct  _Hadoop__Common__GetServiceStatusRequestProto
{
  ProtobufCMessage base;
};
#define HADOOP__COMMON__GET_SERVICE_STATUS_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__get_service_status_request_proto__descriptor) \
     }


struct  _Hadoop__Common__GetServiceStatusResponseProto
{
  ProtobufCMessage base;
  Hadoop__Common__HAServiceStateProto state;
  protobuf_c_boolean has_readytobecomeactive;
  protobuf_c_boolean readytobecomeactive;
  char *notreadyreason;
};
#define HADOOP__COMMON__GET_SERVICE_STATUS_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__get_service_status_response_proto__descriptor) \
    , 0, 0,0, NULL }


/* Hadoop__Common__HAStateChangeRequestInfoProto methods */
void   hadoop__common__hastate_change_request_info_proto__init
                     (Hadoop__Common__HAStateChangeRequestInfoProto         *message);
size_t hadoop__common__hastate_change_request_info_proto__get_packed_size
                     (const Hadoop__Common__HAStateChangeRequestInfoProto   *message);
size_t hadoop__common__hastate_change_request_info_proto__pack
                     (const Hadoop__Common__HAStateChangeRequestInfoProto   *message,
                      uint8_t             *out);
size_t hadoop__common__hastate_change_request_info_proto__pack_to_buffer
                     (const Hadoop__Common__HAStateChangeRequestInfoProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__HAStateChangeRequestInfoProto *
       hadoop__common__hastate_change_request_info_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__hastate_change_request_info_proto__free_unpacked
                     (Hadoop__Common__HAStateChangeRequestInfoProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__MonitorHealthRequestProto methods */
void   hadoop__common__monitor_health_request_proto__init
                     (Hadoop__Common__MonitorHealthRequestProto         *message);
size_t hadoop__common__monitor_health_request_proto__get_packed_size
                     (const Hadoop__Common__MonitorHealthRequestProto   *message);
size_t hadoop__common__monitor_health_request_proto__pack
                     (const Hadoop__Common__MonitorHealthRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__monitor_health_request_proto__pack_to_buffer
                     (const Hadoop__Common__MonitorHealthRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__MonitorHealthRequestProto *
       hadoop__common__monitor_health_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__monitor_health_request_proto__free_unpacked
                     (Hadoop__Common__MonitorHealthRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__MonitorHealthResponseProto methods */
void   hadoop__common__monitor_health_response_proto__init
                     (Hadoop__Common__MonitorHealthResponseProto         *message);
size_t hadoop__common__monitor_health_response_proto__get_packed_size
                     (const Hadoop__Common__MonitorHealthResponseProto   *message);
size_t hadoop__common__monitor_health_response_proto__pack
                     (const Hadoop__Common__MonitorHealthResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__monitor_health_response_proto__pack_to_buffer
                     (const Hadoop__Common__MonitorHealthResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__MonitorHealthResponseProto *
       hadoop__common__monitor_health_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__monitor_health_response_proto__free_unpacked
                     (Hadoop__Common__MonitorHealthResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__TransitionToActiveRequestProto methods */
void   hadoop__common__transition_to_active_request_proto__init
                     (Hadoop__Common__TransitionToActiveRequestProto         *message);
size_t hadoop__common__transition_to_active_request_proto__get_packed_size
                     (const Hadoop__Common__TransitionToActiveRequestProto   *message);
size_t hadoop__common__transition_to_active_request_proto__pack
                     (const Hadoop__Common__TransitionToActiveRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__transition_to_active_request_proto__pack_to_buffer
                     (const Hadoop__Common__TransitionToActiveRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__TransitionToActiveRequestProto *
       hadoop__common__transition_to_active_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__transition_to_active_request_proto__free_unpacked
                     (Hadoop__Common__TransitionToActiveRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__TransitionToActiveResponseProto methods */
void   hadoop__common__transition_to_active_response_proto__init
                     (Hadoop__Common__TransitionToActiveResponseProto         *message);
size_t hadoop__common__transition_to_active_response_proto__get_packed_size
                     (const Hadoop__Common__TransitionToActiveResponseProto   *message);
size_t hadoop__common__transition_to_active_response_proto__pack
                     (const Hadoop__Common__TransitionToActiveResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__transition_to_active_response_proto__pack_to_buffer
                     (const Hadoop__Common__TransitionToActiveResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__TransitionToActiveResponseProto *
       hadoop__common__transition_to_active_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__transition_to_active_response_proto__free_unpacked
                     (Hadoop__Common__TransitionToActiveResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__TransitionToStandbyRequestProto methods */
void   hadoop__common__transition_to_standby_request_proto__init
                     (Hadoop__Common__TransitionToStandbyRequestProto         *message);
size_t hadoop__common__transition_to_standby_request_proto__get_packed_size
                     (const Hadoop__Common__TransitionToStandbyRequestProto   *message);
size_t hadoop__common__transition_to_standby_request_proto__pack
                     (const Hadoop__Common__TransitionToStandbyRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__transition_to_standby_request_proto__pack_to_buffer
                     (const Hadoop__Common__TransitionToStandbyRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__TransitionToStandbyRequestProto *
       hadoop__common__transition_to_standby_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__transition_to_standby_request_proto__free_unpacked
                     (Hadoop__Common__TransitionToStandbyRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__TransitionToStandbyResponseProto methods */
void   hadoop__common__transition_to_standby_response_proto__init
                     (Hadoop__Common__TransitionToStandbyResponseProto         *message);
size_t hadoop__common__transition_to_standby_response_proto__get_packed_size
                     (const Hadoop__Common__TransitionToStandbyResponseProto   *message);
size_t hadoop__common__transition_to_standby_response_proto__pack
                     (const Hadoop__Common__TransitionToStandbyResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__transition_to_standby_response_proto__pack_to_buffer
                     (const Hadoop__Common__TransitionToStandbyResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__TransitionToStandbyResponseProto *
       hadoop__common__transition_to_standby_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__transition_to_standby_response_proto__free_unpacked
                     (Hadoop__Common__TransitionToStandbyResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__GetServiceStatusRequestProto methods */
void   hadoop__common__get_service_status_request_proto__init
                     (Hadoop__Common__GetServiceStatusRequestProto         *message);
size_t hadoop__common__get_service_status_request_proto__get_packed_size
                     (const Hadoop__Common__GetServiceStatusRequestProto   *message);
size_t hadoop__common__get_service_status_request_proto__pack
                     (const Hadoop__Common__GetServiceStatusRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__get_service_status_request_proto__pack_to_buffer
                     (const Hadoop__Common__GetServiceStatusRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GetServiceStatusRequestProto *
       hadoop__common__get_service_status_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__get_service_status_request_proto__free_unpacked
                     (Hadoop__Common__GetServiceStatusRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__GetServiceStatusResponseProto methods */
void   hadoop__common__get_service_status_response_proto__init
                     (Hadoop__Common__GetServiceStatusResponseProto         *message);
size_t hadoop__common__get_service_status_response_proto__get_packed_size
                     (const Hadoop__Common__GetServiceStatusResponseProto   *message);
size_t hadoop__common__get_service_status_response_proto__pack
                     (const Hadoop__Common__GetServiceStatusResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__get_service_status_response_proto__pack_to_buffer
                     (const Hadoop__Common__GetServiceStatusResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GetServiceStatusResponseProto *
       hadoop__common__get_service_status_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__get_service_status_response_proto__free_unpacked
                     (Hadoop__Common__GetServiceStatusResponseProto *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Hadoop__Common__HAStateChangeRequestInfoProto_Closure)
                 (const Hadoop__Common__HAStateChangeRequestInfoProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__MonitorHealthRequestProto_Closure)
                 (const Hadoop__Common__MonitorHealthRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__MonitorHealthResponseProto_Closure)
                 (const Hadoop__Common__MonitorHealthResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__TransitionToActiveRequestProto_Closure)
                 (const Hadoop__Common__TransitionToActiveRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__TransitionToActiveResponseProto_Closure)
                 (const Hadoop__Common__TransitionToActiveResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__TransitionToStandbyRequestProto_Closure)
                 (const Hadoop__Common__TransitionToStandbyRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__TransitionToStandbyResponseProto_Closure)
                 (const Hadoop__Common__TransitionToStandbyResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__GetServiceStatusRequestProto_Closure)
                 (const Hadoop__Common__GetServiceStatusRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__GetServiceStatusResponseProto_Closure)
                 (const Hadoop__Common__GetServiceStatusResponseProto *message,
                  void *closure_data);

/* --- services --- */

typedef struct _Hadoop__Common__HAServiceProtocolService_Service Hadoop__Common__HAServiceProtocolService_Service;
struct _Hadoop__Common__HAServiceProtocolService_Service
{
  ProtobufCService base;
  void (*monitor_health)(Hadoop__Common__HAServiceProtocolService_Service *service,
                         const Hadoop__Common__MonitorHealthRequestProto *input,
                         Hadoop__Common__MonitorHealthResponseProto_Closure closure,
                         void *closure_data);
  void (*transition_to_active)(Hadoop__Common__HAServiceProtocolService_Service *service,
                               const Hadoop__Common__TransitionToActiveRequestProto *input,
                               Hadoop__Common__TransitionToActiveResponseProto_Closure closure,
                               void *closure_data);
  void (*transition_to_standby)(Hadoop__Common__HAServiceProtocolService_Service *service,
                                const Hadoop__Common__TransitionToStandbyRequestProto *input,
                                Hadoop__Common__TransitionToStandbyResponseProto_Closure closure,
                                void *closure_data);
  void (*get_service_status)(Hadoop__Common__HAServiceProtocolService_Service *service,
                             const Hadoop__Common__GetServiceStatusRequestProto *input,
                             Hadoop__Common__GetServiceStatusResponseProto_Closure closure,
                             void *closure_data);
};
typedef void (*Hadoop__Common__HAServiceProtocolService_ServiceDestroy)(Hadoop__Common__HAServiceProtocolService_Service *);
void hadoop__common__haservice_protocol_service__init (Hadoop__Common__HAServiceProtocolService_Service *service,
                                                       Hadoop__Common__HAServiceProtocolService_ServiceDestroy destroy);
#define HADOOP__COMMON__HASERVICE_PROTOCOL_SERVICE__BASE_INIT \
    { &hadoop__common__haservice_protocol_service__descriptor, protobuf_c_service_invoke_internal, NULL }
#define HADOOP__COMMON__HASERVICE_PROTOCOL_SERVICE__INIT(function_prefix__) \
    { HADOOP__COMMON__HASERVICE_PROTOCOL_SERVICE__BASE_INIT,\
      function_prefix__ ## monitor_health,\
      function_prefix__ ## transition_to_active,\
      function_prefix__ ## transition_to_standby,\
      function_prefix__ ## get_service_status  }
void hadoop__common__haservice_protocol_service__monitor_health(ProtobufCService *service,
                                                                const Hadoop__Common__MonitorHealthRequestProto *input,
                                                                Hadoop__Common__MonitorHealthResponseProto_Closure closure,
                                                                void *closure_data);
void hadoop__common__haservice_protocol_service__transition_to_active(ProtobufCService *service,
                                                                      const Hadoop__Common__TransitionToActiveRequestProto *input,
                                                                      Hadoop__Common__TransitionToActiveResponseProto_Closure closure,
                                                                      void *closure_data);
void hadoop__common__haservice_protocol_service__transition_to_standby(ProtobufCService *service,
                                                                       const Hadoop__Common__TransitionToStandbyRequestProto *input,
                                                                       Hadoop__Common__TransitionToStandbyResponseProto_Closure closure,
                                                                       void *closure_data);
void hadoop__common__haservice_protocol_service__get_service_status(ProtobufCService *service,
                                                                    const Hadoop__Common__GetServiceStatusRequestProto *input,
                                                                    Hadoop__Common__GetServiceStatusResponseProto_Closure closure,
                                                                    void *closure_data);

/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    hadoop__common__haservice_state_proto__descriptor;
extern const ProtobufCEnumDescriptor    hadoop__common__harequest_source__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__hastate_change_request_info_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__monitor_health_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__monitor_health_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__transition_to_active_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__transition_to_active_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__transition_to_standby_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__transition_to_standby_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__get_service_status_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__get_service_status_response_proto__descriptor;
extern const ProtobufCServiceDescriptor hadoop__common__haservice_protocol_service__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_HAServiceProtocol_2eproto__INCLUDED */
