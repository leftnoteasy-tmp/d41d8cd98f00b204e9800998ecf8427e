/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "LocalizationProtocol.pb-c.h"
static const ProtobufCMethodDescriptor localization_protocol_service__method_descriptors[1] =
{
  { "heartbeat", &localizer_status_proto__descriptor, &localizer_heartbeat_response_proto__descriptor },
};
const unsigned localization_protocol_service__method_indices_by_name[] = {
  0         /* heartbeat */
};
const ProtobufCServiceDescriptor localization_protocol_service__descriptor =
{
  PROTOBUF_C_SERVICE_DESCRIPTOR_MAGIC,
  "LocalizationProtocolService",
  "heartbeat",
  "LocalizationProtocolService",
  "",
  1,
  localization_protocol_service__method_descriptors,
  localization_protocol_service__method_indices_by_name
};
void localization_protocol_service__heartbeat(ProtobufCService *service,
                                              const LocalizerStatusProto *input,
                                              LocalizerHeartbeatResponseProto_Closure closure,
                                              void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &localization_protocol_service__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void localization_protocol_service__init (LocalizationProtocolService_Service *service,
                                          LocalizationProtocolService_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &localization_protocol_service__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}
