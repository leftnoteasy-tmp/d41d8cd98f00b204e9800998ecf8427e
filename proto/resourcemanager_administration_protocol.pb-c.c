/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "resourcemanager_administration_protocol.pb-c.h"
static const ProtobufCMethodDescriptor resource_manager_administration_protocol_service__method_descriptors[7] =
{
  { "refreshQueues", &refresh_queues_request_proto__descriptor, &refresh_queues_response_proto__descriptor },
  { "refreshNodes", &refresh_nodes_request_proto__descriptor, &refresh_nodes_response_proto__descriptor },
  { "refreshSuperUserGroupsConfiguration", &refresh_super_user_groups_configuration_request_proto__descriptor, &refresh_super_user_groups_configuration_response_proto__descriptor },
  { "refreshUserToGroupsMappings", &refresh_user_to_groups_mappings_request_proto__descriptor, &refresh_user_to_groups_mappings_response_proto__descriptor },
  { "refreshAdminAcls", &refresh_admin_acls_request_proto__descriptor, &refresh_admin_acls_response_proto__descriptor },
  { "refreshServiceAcls", &refresh_service_acls_request_proto__descriptor, &refresh_service_acls_response_proto__descriptor },
  { "getGroupsForUser", &get_groups_for_user_request_proto__descriptor, &get_groups_for_user_response_proto__descriptor },
};
const unsigned resource_manager_administration_protocol_service__method_indices_by_name[] = {
  6,        /* getGroupsForUser */
  4,        /* refreshAdminAcls */
  1,        /* refreshNodes */
  0,        /* refreshQueues */
  5,        /* refreshServiceAcls */
  2,        /* refreshSuperUserGroupsConfiguration */
  3         /* refreshUserToGroupsMappings */
};
const ProtobufCServiceDescriptor resource_manager_administration_protocol_service__descriptor =
{
  PROTOBUF_C_SERVICE_DESCRIPTOR_MAGIC,
  "ResourceManagerAdministrationProtocolService",
  "refreshUserToGroupsMappings",
  "ResourceManagerAdministrationProtocolService",
  "",
  7,
  resource_manager_administration_protocol_service__method_descriptors,
  resource_manager_administration_protocol_service__method_indices_by_name
};
void resource_manager_administration_protocol_service__refresh_queues(ProtobufCService *service,
                                                                      const RefreshQueuesRequestProto *input,
                                                                      RefreshQueuesResponseProto_Closure closure,
                                                                      void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &resource_manager_administration_protocol_service__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void resource_manager_administration_protocol_service__refresh_nodes(ProtobufCService *service,
                                                                     const RefreshNodesRequestProto *input,
                                                                     RefreshNodesResponseProto_Closure closure,
                                                                     void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &resource_manager_administration_protocol_service__descriptor);
  service->invoke(service, 1, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void resource_manager_administration_protocol_service__refresh_super_user_groups_configuration(ProtobufCService *service,
                                                                                               const RefreshSuperUserGroupsConfigurationRequestProto *input,
                                                                                               RefreshSuperUserGroupsConfigurationResponseProto_Closure closure,
                                                                                               void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &resource_manager_administration_protocol_service__descriptor);
  service->invoke(service, 2, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void resource_manager_administration_protocol_service__refresh_user_to_groups_mappings(ProtobufCService *service,
                                                                                       const RefreshUserToGroupsMappingsRequestProto *input,
                                                                                       RefreshUserToGroupsMappingsResponseProto_Closure closure,
                                                                                       void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &resource_manager_administration_protocol_service__descriptor);
  service->invoke(service, 3, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void resource_manager_administration_protocol_service__refresh_admin_acls(ProtobufCService *service,
                                                                          const RefreshAdminAclsRequestProto *input,
                                                                          RefreshAdminAclsResponseProto_Closure closure,
                                                                          void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &resource_manager_administration_protocol_service__descriptor);
  service->invoke(service, 4, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void resource_manager_administration_protocol_service__refresh_service_acls(ProtobufCService *service,
                                                                            const RefreshServiceAclsRequestProto *input,
                                                                            RefreshServiceAclsResponseProto_Closure closure,
                                                                            void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &resource_manager_administration_protocol_service__descriptor);
  service->invoke(service, 5, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void resource_manager_administration_protocol_service__get_groups_for_user(ProtobufCService *service,
                                                                           const GetGroupsForUserRequestProto *input,
                                                                           GetGroupsForUserResponseProto_Closure closure,
                                                                           void *closure_data)
{
  PROTOBUF_C_ASSERT (service->descriptor == &resource_manager_administration_protocol_service__descriptor);
  service->invoke(service, 6, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void resource_manager_administration_protocol_service__init (ResourceManagerAdministrationProtocolService_Service *service,
                                                             ResourceManagerAdministrationProtocolService_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &resource_manager_administration_protocol_service__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}