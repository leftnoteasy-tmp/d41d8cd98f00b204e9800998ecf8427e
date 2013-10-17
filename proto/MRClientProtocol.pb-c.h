/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_MRClientProtocol_2eproto__INCLUDED
#define PROTOBUF_C_MRClientProtocol_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS

#include "Security.pb-c.h"
#include "mr_service_protos.pb-c.h"



/* --- enums --- */


/* --- messages --- */

/* --- per-message closures --- */


/* --- services --- */

typedef struct _Hadoop__Mapreduce__MRClientProtocolService_Service Hadoop__Mapreduce__MRClientProtocolService_Service;
struct _Hadoop__Mapreduce__MRClientProtocolService_Service
{
  ProtobufCService base;
  void (*get_job_report)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                         const Hadoop__Mapreduce__GetJobReportRequestProto *input,
                         Hadoop__Mapreduce__GetJobReportResponseProto_Closure closure,
                         void *closure_data);
  void (*get_task_report)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                          const Hadoop__Mapreduce__GetTaskReportRequestProto *input,
                          Hadoop__Mapreduce__GetTaskReportResponseProto_Closure closure,
                          void *closure_data);
  void (*get_task_attempt_report)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                                  const Hadoop__Mapreduce__GetTaskAttemptReportRequestProto *input,
                                  Hadoop__Mapreduce__GetTaskAttemptReportResponseProto_Closure closure,
                                  void *closure_data);
  void (*get_counters)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                       const Hadoop__Mapreduce__GetCountersRequestProto *input,
                       Hadoop__Mapreduce__GetCountersResponseProto_Closure closure,
                       void *closure_data);
  void (*get_task_attempt_completion_events)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                                             const Hadoop__Mapreduce__GetTaskAttemptCompletionEventsRequestProto *input,
                                             Hadoop__Mapreduce__GetTaskAttemptCompletionEventsResponseProto_Closure closure,
                                             void *closure_data);
  void (*get_task_reports)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                           const Hadoop__Mapreduce__GetTaskReportsRequestProto *input,
                           Hadoop__Mapreduce__GetTaskReportsResponseProto_Closure closure,
                           void *closure_data);
  void (*get_diagnostics)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                          const Hadoop__Mapreduce__GetDiagnosticsRequestProto *input,
                          Hadoop__Mapreduce__GetDiagnosticsResponseProto_Closure closure,
                          void *closure_data);
  void (*get_delegation_token)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                               const Hadoop__Common__GetDelegationTokenRequestProto *input,
                               Hadoop__Common__GetDelegationTokenResponseProto_Closure closure,
                               void *closure_data);
  void (*kill_job)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                   const Hadoop__Mapreduce__KillJobRequestProto *input,
                   Hadoop__Mapreduce__KillJobResponseProto_Closure closure,
                   void *closure_data);
  void (*kill_task)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                    const Hadoop__Mapreduce__KillTaskRequestProto *input,
                    Hadoop__Mapreduce__KillTaskResponseProto_Closure closure,
                    void *closure_data);
  void (*kill_task_attempt)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                            const Hadoop__Mapreduce__KillTaskAttemptRequestProto *input,
                            Hadoop__Mapreduce__KillTaskAttemptResponseProto_Closure closure,
                            void *closure_data);
  void (*fail_task_attempt)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                            const Hadoop__Mapreduce__FailTaskAttemptRequestProto *input,
                            Hadoop__Mapreduce__FailTaskAttemptResponseProto_Closure closure,
                            void *closure_data);
  void (*renew_delegation_token)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                                 const Hadoop__Common__RenewDelegationTokenRequestProto *input,
                                 Hadoop__Common__RenewDelegationTokenResponseProto_Closure closure,
                                 void *closure_data);
  void (*cancel_delegation_token)(Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                                  const Hadoop__Common__CancelDelegationTokenRequestProto *input,
                                  Hadoop__Common__CancelDelegationTokenResponseProto_Closure closure,
                                  void *closure_data);
};
typedef void (*Hadoop__Mapreduce__MRClientProtocolService_ServiceDestroy)(Hadoop__Mapreduce__MRClientProtocolService_Service *);
void hadoop__mapreduce__mrclient_protocol_service__init (Hadoop__Mapreduce__MRClientProtocolService_Service *service,
                                                         Hadoop__Mapreduce__MRClientProtocolService_ServiceDestroy destroy);
#define HADOOP__MAPREDUCE__MRCLIENT_PROTOCOL_SERVICE__BASE_INIT \
    { &hadoop__mapreduce__mrclient_protocol_service__descriptor, protobuf_c_service_invoke_internal, NULL }
#define HADOOP__MAPREDUCE__MRCLIENT_PROTOCOL_SERVICE__INIT(function_prefix__) \
    { HADOOP__MAPREDUCE__MRCLIENT_PROTOCOL_SERVICE__BASE_INIT,\
      function_prefix__ ## get_job_report,\
      function_prefix__ ## get_task_report,\
      function_prefix__ ## get_task_attempt_report,\
      function_prefix__ ## get_counters,\
      function_prefix__ ## get_task_attempt_completion_events,\
      function_prefix__ ## get_task_reports,\
      function_prefix__ ## get_diagnostics,\
      function_prefix__ ## get_delegation_token,\
      function_prefix__ ## kill_job,\
      function_prefix__ ## kill_task,\
      function_prefix__ ## kill_task_attempt,\
      function_prefix__ ## fail_task_attempt,\
      function_prefix__ ## renew_delegation_token,\
      function_prefix__ ## cancel_delegation_token  }
void hadoop__mapreduce__mrclient_protocol_service__get_job_report(ProtobufCService *service,
                                                                  const Hadoop__Mapreduce__GetJobReportRequestProto *input,
                                                                  Hadoop__Mapreduce__GetJobReportResponseProto_Closure closure,
                                                                  void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__get_task_report(ProtobufCService *service,
                                                                   const Hadoop__Mapreduce__GetTaskReportRequestProto *input,
                                                                   Hadoop__Mapreduce__GetTaskReportResponseProto_Closure closure,
                                                                   void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__get_task_attempt_report(ProtobufCService *service,
                                                                           const Hadoop__Mapreduce__GetTaskAttemptReportRequestProto *input,
                                                                           Hadoop__Mapreduce__GetTaskAttemptReportResponseProto_Closure closure,
                                                                           void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__get_counters(ProtobufCService *service,
                                                                const Hadoop__Mapreduce__GetCountersRequestProto *input,
                                                                Hadoop__Mapreduce__GetCountersResponseProto_Closure closure,
                                                                void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__get_task_attempt_completion_events(ProtobufCService *service,
                                                                                      const Hadoop__Mapreduce__GetTaskAttemptCompletionEventsRequestProto *input,
                                                                                      Hadoop__Mapreduce__GetTaskAttemptCompletionEventsResponseProto_Closure closure,
                                                                                      void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__get_task_reports(ProtobufCService *service,
                                                                    const Hadoop__Mapreduce__GetTaskReportsRequestProto *input,
                                                                    Hadoop__Mapreduce__GetTaskReportsResponseProto_Closure closure,
                                                                    void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__get_diagnostics(ProtobufCService *service,
                                                                   const Hadoop__Mapreduce__GetDiagnosticsRequestProto *input,
                                                                   Hadoop__Mapreduce__GetDiagnosticsResponseProto_Closure closure,
                                                                   void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__get_delegation_token(ProtobufCService *service,
                                                                        const Hadoop__Common__GetDelegationTokenRequestProto *input,
                                                                        Hadoop__Common__GetDelegationTokenResponseProto_Closure closure,
                                                                        void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__kill_job(ProtobufCService *service,
                                                            const Hadoop__Mapreduce__KillJobRequestProto *input,
                                                            Hadoop__Mapreduce__KillJobResponseProto_Closure closure,
                                                            void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__kill_task(ProtobufCService *service,
                                                             const Hadoop__Mapreduce__KillTaskRequestProto *input,
                                                             Hadoop__Mapreduce__KillTaskResponseProto_Closure closure,
                                                             void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__kill_task_attempt(ProtobufCService *service,
                                                                     const Hadoop__Mapreduce__KillTaskAttemptRequestProto *input,
                                                                     Hadoop__Mapreduce__KillTaskAttemptResponseProto_Closure closure,
                                                                     void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__fail_task_attempt(ProtobufCService *service,
                                                                     const Hadoop__Mapreduce__FailTaskAttemptRequestProto *input,
                                                                     Hadoop__Mapreduce__FailTaskAttemptResponseProto_Closure closure,
                                                                     void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__renew_delegation_token(ProtobufCService *service,
                                                                          const Hadoop__Common__RenewDelegationTokenRequestProto *input,
                                                                          Hadoop__Common__RenewDelegationTokenResponseProto_Closure closure,
                                                                          void *closure_data);
void hadoop__mapreduce__mrclient_protocol_service__cancel_delegation_token(ProtobufCService *service,
                                                                           const Hadoop__Common__CancelDelegationTokenRequestProto *input,
                                                                           Hadoop__Common__CancelDelegationTokenResponseProto_Closure closure,
                                                                           void *closure_data);

/* --- descriptors --- */

extern const ProtobufCServiceDescriptor hadoop__mapreduce__mrclient_protocol_service__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_MRClientProtocol_2eproto__INCLUDED */
