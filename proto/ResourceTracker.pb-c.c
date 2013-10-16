/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "ResourceTracker.pb-c.h"
static const ProtobufCMethodDescriptor resource_tracker_service__method_descriptors[2] =
{
  { "registerNodeManager", &register_node_manager_request_proto__descriptor, &register_node_manager_response_proto__descriptor },
  { "nodeHeartbeat", &node_heartbeat_request_proto__descriptor, &node_heartbeat_response_proto__descriptor },
};
const unsigned resource_tracker_service__method_indices_by_name[] = {
  1,        /* nodeHeartbeat */
  0         /* registerNodeManager */
};
const ProtobufCServiceDescriptor resource_tracker_service__descriptor =
{
  PROTOBUF_C_SERVICE_DESCRIPTOR_MAGIC,
  "ResourceTrackerService",
  "registerNodeManager",
  "ResourceTrackerService",
  "",
  2,
  resource_tracker_service__method_descriptors,
  resource_tracker_service__method_indices_by_name
};
void resource_tracker_service__register_node_manager(ProtobufCService *service,
                                                     const RegisterNodeManagerRequestProto *input,
                                                     RegisterNodeManagerResponseProto_Closure closure,
                                                     void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &resource_tracker_service__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void resource_tracker_service__node_heartbeat(ProtobufCService *service,
                                              const NodeHeartbeatRequestProto *input,
                                              NodeHeartbeatResponseProto_Closure closure,
                                              void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &resource_tracker_service__descriptor);
  service->invoke(service, 1, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void resource_tracker_service__init (ResourceTrackerService_Service *service,
                                     ResourceTrackerService_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &resource_tracker_service__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}
