/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_applicationclient_5fprotocol_2eproto__INCLUDED
#define PROTOBUF_C_applicationclient_5fprotocol_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS

#include "Security.pb-c.h"
#include "yarn_service_protos.pb-c.h"



/* --- enums --- */


/* --- messages --- */

/* --- per-message closures --- */


/* --- services --- */

typedef struct _ApplicationClientProtocolService_Service ApplicationClientProtocolService_Service;
struct _ApplicationClientProtocolService_Service
{
  ProtobufCService base;
  void (*get_new_application)(ApplicationClientProtocolService_Service *service,
                              const GetNewApplicationRequestProto *input,
                              GetNewApplicationResponseProto_Closure closure,
                              void *closure_data);
  void (*get_application_report)(ApplicationClientProtocolService_Service *service,
                                 const GetApplicationReportRequestProto *input,
                                 GetApplicationReportResponseProto_Closure closure,
                                 void *closure_data);
  void (*submit_application)(ApplicationClientProtocolService_Service *service,
                             const SubmitApplicationRequestProto *input,
                             SubmitApplicationResponseProto_Closure closure,
                             void *closure_data);
  void (*force_kill_application)(ApplicationClientProtocolService_Service *service,
                                 const KillApplicationRequestProto *input,
                                 KillApplicationResponseProto_Closure closure,
                                 void *closure_data);
  void (*get_cluster_metrics)(ApplicationClientProtocolService_Service *service,
                              const GetClusterMetricsRequestProto *input,
                              GetClusterMetricsResponseProto_Closure closure,
                              void *closure_data);
  void (*get_applications)(ApplicationClientProtocolService_Service *service,
                           const GetApplicationsRequestProto *input,
                           GetApplicationsResponseProto_Closure closure,
                           void *closure_data);
  void (*get_cluster_nodes)(ApplicationClientProtocolService_Service *service,
                            const GetClusterNodesRequestProto *input,
                            GetClusterNodesResponseProto_Closure closure,
                            void *closure_data);
  void (*get_queue_info)(ApplicationClientProtocolService_Service *service,
                         const GetQueueInfoRequestProto *input,
                         GetQueueInfoResponseProto_Closure closure,
                         void *closure_data);
  void (*get_queue_user_acls)(ApplicationClientProtocolService_Service *service,
                              const GetQueueUserAclsInfoRequestProto *input,
                              GetQueueUserAclsInfoResponseProto_Closure closure,
                              void *closure_data);
  void (*get_delegation_token)(ApplicationClientProtocolService_Service *service,
                               const Hadoop__Common__GetDelegationTokenRequestProto *input,
                               Hadoop__Common__GetDelegationTokenResponseProto_Closure closure,
                               void *closure_data);
  void (*renew_delegation_token)(ApplicationClientProtocolService_Service *service,
                                 const Hadoop__Common__RenewDelegationTokenRequestProto *input,
                                 Hadoop__Common__RenewDelegationTokenResponseProto_Closure closure,
                                 void *closure_data);
  void (*cancel_delegation_token)(ApplicationClientProtocolService_Service *service,
                                  const Hadoop__Common__CancelDelegationTokenRequestProto *input,
                                  Hadoop__Common__CancelDelegationTokenResponseProto_Closure closure,
                                  void *closure_data);
};
typedef void (*ApplicationClientProtocolService_ServiceDestroy)(ApplicationClientProtocolService_Service *);
void application_client_protocol_service__init (ApplicationClientProtocolService_Service *service,
                                                ApplicationClientProtocolService_ServiceDestroy destroy);
#define APPLICATION_CLIENT_PROTOCOL_SERVICE__BASE_INIT \
    { &application_client_protocol_service__descriptor, protobuf_c_service_invoke_internal, NULL }
#define APPLICATION_CLIENT_PROTOCOL_SERVICE__INIT(function_prefix__) \
    { APPLICATION_CLIENT_PROTOCOL_SERVICE__BASE_INIT,\
      function_prefix__ ## get_new_application,\
      function_prefix__ ## get_application_report,\
      function_prefix__ ## submit_application,\
      function_prefix__ ## force_kill_application,\
      function_prefix__ ## get_cluster_metrics,\
      function_prefix__ ## get_applications,\
      function_prefix__ ## get_cluster_nodes,\
      function_prefix__ ## get_queue_info,\
      function_prefix__ ## get_queue_user_acls,\
      function_prefix__ ## get_delegation_token,\
      function_prefix__ ## renew_delegation_token,\
      function_prefix__ ## cancel_delegation_token  }
void application_client_protocol_service__get_new_application(ProtobufCService *service,
                                                              const GetNewApplicationRequestProto *input,
                                                              GetNewApplicationResponseProto_Closure closure,
                                                              void *closure_data);
void application_client_protocol_service__get_application_report(ProtobufCService *service,
                                                                 const GetApplicationReportRequestProto *input,
                                                                 GetApplicationReportResponseProto_Closure closure,
                                                                 void *closure_data);
void application_client_protocol_service__submit_application(ProtobufCService *service,
                                                             const SubmitApplicationRequestProto *input,
                                                             SubmitApplicationResponseProto_Closure closure,
                                                             void *closure_data);
void application_client_protocol_service__force_kill_application(ProtobufCService *service,
                                                                 const KillApplicationRequestProto *input,
                                                                 KillApplicationResponseProto_Closure closure,
                                                                 void *closure_data);
void application_client_protocol_service__get_cluster_metrics(ProtobufCService *service,
                                                              const GetClusterMetricsRequestProto *input,
                                                              GetClusterMetricsResponseProto_Closure closure,
                                                              void *closure_data);
void application_client_protocol_service__get_applications(ProtobufCService *service,
                                                           const GetApplicationsRequestProto *input,
                                                           GetApplicationsResponseProto_Closure closure,
                                                           void *closure_data);
void application_client_protocol_service__get_cluster_nodes(ProtobufCService *service,
                                                            const GetClusterNodesRequestProto *input,
                                                            GetClusterNodesResponseProto_Closure closure,
                                                            void *closure_data);
void application_client_protocol_service__get_queue_info(ProtobufCService *service,
                                                         const GetQueueInfoRequestProto *input,
                                                         GetQueueInfoResponseProto_Closure closure,
                                                         void *closure_data);
void application_client_protocol_service__get_queue_user_acls(ProtobufCService *service,
                                                              const GetQueueUserAclsInfoRequestProto *input,
                                                              GetQueueUserAclsInfoResponseProto_Closure closure,
                                                              void *closure_data);
void application_client_protocol_service__get_delegation_token(ProtobufCService *service,
                                                               const Hadoop__Common__GetDelegationTokenRequestProto *input,
                                                               Hadoop__Common__GetDelegationTokenResponseProto_Closure closure,
                                                               void *closure_data);
void application_client_protocol_service__renew_delegation_token(ProtobufCService *service,
                                                                 const Hadoop__Common__RenewDelegationTokenRequestProto *input,
                                                                 Hadoop__Common__RenewDelegationTokenResponseProto_Closure closure,
                                                                 void *closure_data);
void application_client_protocol_service__cancel_delegation_token(ProtobufCService *service,
                                                                  const Hadoop__Common__CancelDelegationTokenRequestProto *input,
                                                                  Hadoop__Common__CancelDelegationTokenResponseProto_Closure closure,
                                                                  void *closure_data);

/* --- descriptors --- */

extern const ProtobufCServiceDescriptor application_client_protocol_service__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_applicationclient_5fprotocol_2eproto__INCLUDED */
