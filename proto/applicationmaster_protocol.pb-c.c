/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "applicationmaster_protocol.pb-c.h"
static const ProtobufCMethodDescriptor hadoop__yarn__application_master_protocol_service__method_descriptors[3] =
{
  { "registerApplicationMaster", &hadoop__yarn__register_application_master_request_proto__descriptor, &hadoop__yarn__register_application_master_response_proto__descriptor },
  { "finishApplicationMaster", &hadoop__yarn__finish_application_master_request_proto__descriptor, &hadoop__yarn__finish_application_master_response_proto__descriptor },
  { "allocate", &hadoop__yarn__allocate_request_proto__descriptor, &hadoop__yarn__allocate_response_proto__descriptor },
};
const unsigned hadoop__yarn__application_master_protocol_service__method_indices_by_name[] = {
  2,        /* allocate */
  1,        /* finishApplicationMaster */
  0         /* registerApplicationMaster */
};
const ProtobufCServiceDescriptor hadoop__yarn__application_master_protocol_service__descriptor =
{
  PROTOBUF_C_SERVICE_DESCRIPTOR_MAGIC,
  "hadoop.yarn.ApplicationMasterProtocolService",
  "registerApplicationMaster",
  "Hadoop__Yarn__ApplicationMasterProtocolService",
  "hadoop.yarn",
  3,
  hadoop__yarn__application_master_protocol_service__method_descriptors,
  hadoop__yarn__application_master_protocol_service__method_indices_by_name
};
void hadoop__yarn__application_master_protocol_service__register_application_master(ProtobufCService *service,
                                                                                    const Hadoop__Yarn__RegisterApplicationMasterRequestProto *input,
                                                                                    Hadoop__Yarn__RegisterApplicationMasterResponseProto_Closure closure,
                                                                                    void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &hadoop__yarn__application_master_protocol_service__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void hadoop__yarn__application_master_protocol_service__finish_application_master(ProtobufCService *service,
                                                                                  const Hadoop__Yarn__FinishApplicationMasterRequestProto *input,
                                                                                  Hadoop__Yarn__FinishApplicationMasterResponseProto_Closure closure,
                                                                                  void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &hadoop__yarn__application_master_protocol_service__descriptor);
  service->invoke(service, 1, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void hadoop__yarn__application_master_protocol_service__allocate(ProtobufCService *service,
                                                                 const Hadoop__Yarn__AllocateRequestProto *input,
                                                                 Hadoop__Yarn__AllocateResponseProto_Closure closure,
                                                                 void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &hadoop__yarn__application_master_protocol_service__descriptor);
  service->invoke(service, 2, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void hadoop__yarn__application_master_protocol_service__init (Hadoop__Yarn__ApplicationMasterProtocolService_Service *service,
                                                              Hadoop__Yarn__ApplicationMasterProtocolService_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &hadoop__yarn__application_master_protocol_service__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}
