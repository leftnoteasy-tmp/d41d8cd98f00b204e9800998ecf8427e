/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "LocalizationProtocol.pb-c.h"
static const ProtobufCMethodDescriptor hadoop__yarn__localization_protocol_service__method_descriptors[1] =
{
  { "heartbeat", &hadoop__yarn__localizer_status_proto__descriptor, &hadoop__yarn__localizer_heartbeat_response_proto__descriptor },
};
const unsigned hadoop__yarn__localization_protocol_service__method_indices_by_name[] = {
  0         /* heartbeat */
};
const ProtobufCServiceDescriptor hadoop__yarn__localization_protocol_service__descriptor =
{
  PROTOBUF_C_SERVICE_DESCRIPTOR_MAGIC,
  "hadoop.yarn.LocalizationProtocolService",
  "heartbeat",
  "Hadoop__Yarn__LocalizationProtocolService",
  "hadoop.yarn",
  1,
  hadoop__yarn__localization_protocol_service__method_descriptors,
  hadoop__yarn__localization_protocol_service__method_indices_by_name
};
void hadoop__yarn__localization_protocol_service__heartbeat(ProtobufCService *service,
                                                            const Hadoop__Yarn__LocalizerStatusProto *input,
                                                            Hadoop__Yarn__LocalizerHeartbeatResponseProto_Closure closure,
                                                            void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &hadoop__yarn__localization_protocol_service__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void hadoop__yarn__localization_protocol_service__init (Hadoop__Yarn__LocalizationProtocolService_Service *service,
                                                        Hadoop__Yarn__LocalizationProtocolService_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &hadoop__yarn__localization_protocol_service__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}
