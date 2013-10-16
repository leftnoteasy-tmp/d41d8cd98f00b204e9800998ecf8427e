/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_mr_5fprotos_2eproto__INCLUDED
#define PROTOBUF_C_mr_5fprotos_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS

#include "yarn_protos.pb-c.h"

typedef struct _JobIdProto JobIdProto;
typedef struct _TaskIdProto TaskIdProto;
typedef struct _TaskAttemptIdProto TaskAttemptIdProto;
typedef struct _CounterProto CounterProto;
typedef struct _CounterGroupProto CounterGroupProto;
typedef struct _CountersProto CountersProto;
typedef struct _TaskReportProto TaskReportProto;
typedef struct _TaskAttemptReportProto TaskAttemptReportProto;
typedef struct _JobReportProto JobReportProto;
typedef struct _AMInfoProto AMInfoProto;
typedef struct _TaskAttemptCompletionEventProto TaskAttemptCompletionEventProto;
typedef struct _StringCounterMapProto StringCounterMapProto;
typedef struct _StringCounterGroupMapProto StringCounterGroupMapProto;


/* --- enums --- */

typedef enum _TaskTypeProto {
  TASK_TYPE_PROTO__MAP = 1,
  TASK_TYPE_PROTO__REDUCE = 2
} TaskTypeProto;
typedef enum _TaskStateProto {
  TASK_STATE_PROTO__TS_NEW = 1,
  TASK_STATE_PROTO__TS_SCHEDULED = 2,
  TASK_STATE_PROTO__TS_RUNNING = 3,
  TASK_STATE_PROTO__TS_SUCCEEDED = 4,
  TASK_STATE_PROTO__TS_FAILED = 5,
  TASK_STATE_PROTO__TS_KILLED = 6
} TaskStateProto;
typedef enum _PhaseProto {
  PHASE_PROTO__P_STARTING = 1,
  PHASE_PROTO__P_MAP = 2,
  PHASE_PROTO__P_SHUFFLE = 3,
  PHASE_PROTO__P_SORT = 4,
  PHASE_PROTO__P_REDUCE = 5,
  PHASE_PROTO__P_CLEANUP = 6
} PhaseProto;
typedef enum _TaskAttemptStateProto {
  TASK_ATTEMPT_STATE_PROTO__TA_NEW = 1,
  TASK_ATTEMPT_STATE_PROTO__TA_STARTING = 2,
  TASK_ATTEMPT_STATE_PROTO__TA_RUNNING = 3,
  TASK_ATTEMPT_STATE_PROTO__TA_COMMIT_PENDING = 4,
  TASK_ATTEMPT_STATE_PROTO__TA_SUCCEEDED = 5,
  TASK_ATTEMPT_STATE_PROTO__TA_FAILED = 6,
  TASK_ATTEMPT_STATE_PROTO__TA_KILLED = 7
} TaskAttemptStateProto;
typedef enum _JobStateProto {
  JOB_STATE_PROTO__J_NEW = 1,
  JOB_STATE_PROTO__J_INITED = 2,
  JOB_STATE_PROTO__J_RUNNING = 3,
  JOB_STATE_PROTO__J_SUCCEEDED = 4,
  JOB_STATE_PROTO__J_FAILED = 5,
  JOB_STATE_PROTO__J_KILLED = 6,
  JOB_STATE_PROTO__J_ERROR = 7
} JobStateProto;
typedef enum _TaskAttemptCompletionEventStatusProto {
  TASK_ATTEMPT_COMPLETION_EVENT_STATUS_PROTO__TACE_FAILED = 1,
  TASK_ATTEMPT_COMPLETION_EVENT_STATUS_PROTO__TACE_KILLED = 2,
  TASK_ATTEMPT_COMPLETION_EVENT_STATUS_PROTO__TACE_SUCCEEDED = 3,
  TASK_ATTEMPT_COMPLETION_EVENT_STATUS_PROTO__TACE_OBSOLETE = 4,
  TASK_ATTEMPT_COMPLETION_EVENT_STATUS_PROTO__TACE_TIPFAILED = 5
} TaskAttemptCompletionEventStatusProto;

/* --- messages --- */

struct  _JobIdProto
{
  ProtobufCMessage base;
  ApplicationIdProto *app_id;
  protobuf_c_boolean has_id;
  int32_t id;
};
#define JOB_ID_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&job_id_proto__descriptor) \
    , NULL, 0,0 }


struct  _TaskIdProto
{
  ProtobufCMessage base;
  JobIdProto *job_id;
  protobuf_c_boolean has_task_type;
  TaskTypeProto task_type;
  protobuf_c_boolean has_id;
  int32_t id;
};
#define TASK_ID_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&task_id_proto__descriptor) \
    , NULL, 0,0, 0,0 }


struct  _TaskAttemptIdProto
{
  ProtobufCMessage base;
  TaskIdProto *task_id;
  protobuf_c_boolean has_id;
  int32_t id;
};
#define TASK_ATTEMPT_ID_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&task_attempt_id_proto__descriptor) \
    , NULL, 0,0 }


struct  _CounterProto
{
  ProtobufCMessage base;
  char *name;
  char *display_name;
  protobuf_c_boolean has_value;
  int64_t value;
};
#define COUNTER_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&counter_proto__descriptor) \
    , NULL, NULL, 0,0 }


struct  _CounterGroupProto
{
  ProtobufCMessage base;
  char *name;
  char *display_name;
  size_t n_counters;
  StringCounterMapProto **counters;
};
#define COUNTER_GROUP_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&counter_group_proto__descriptor) \
    , NULL, NULL, 0,NULL }


struct  _CountersProto
{
  ProtobufCMessage base;
  size_t n_counter_groups;
  StringCounterGroupMapProto **counter_groups;
};
#define COUNTERS_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&counters_proto__descriptor) \
    , 0,NULL }


struct  _TaskReportProto
{
  ProtobufCMessage base;
  TaskIdProto *task_id;
  protobuf_c_boolean has_task_state;
  TaskStateProto task_state;
  protobuf_c_boolean has_progress;
  float progress;
  protobuf_c_boolean has_start_time;
  int64_t start_time;
  protobuf_c_boolean has_finish_time;
  int64_t finish_time;
  CountersProto *counters;
  size_t n_running_attempts;
  TaskAttemptIdProto **running_attempts;
  TaskAttemptIdProto *successful_attempt;
  size_t n_diagnostics;
  char **diagnostics;
};
#define TASK_REPORT_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&task_report_proto__descriptor) \
    , NULL, 0,0, 0,0, 0,0, 0,0, NULL, 0,NULL, NULL, 0,NULL }


struct  _TaskAttemptReportProto
{
  ProtobufCMessage base;
  TaskAttemptIdProto *task_attempt_id;
  protobuf_c_boolean has_task_attempt_state;
  TaskAttemptStateProto task_attempt_state;
  protobuf_c_boolean has_progress;
  float progress;
  protobuf_c_boolean has_start_time;
  int64_t start_time;
  protobuf_c_boolean has_finish_time;
  int64_t finish_time;
  CountersProto *counters;
  char *diagnostic_info;
  char *state_string;
  protobuf_c_boolean has_phase;
  PhaseProto phase;
  protobuf_c_boolean has_shuffle_finish_time;
  int64_t shuffle_finish_time;
  protobuf_c_boolean has_sort_finish_time;
  int64_t sort_finish_time;
  char *node_manager_host;
  protobuf_c_boolean has_node_manager_port;
  int32_t node_manager_port;
  protobuf_c_boolean has_node_manager_http_port;
  int32_t node_manager_http_port;
  ContainerIdProto *container_id;
};
#define TASK_ATTEMPT_REPORT_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&task_attempt_report_proto__descriptor) \
    , NULL, 0,0, 0,0, 0,0, 0,0, NULL, NULL, NULL, 0,0, 0,0, 0,0, NULL, 0,0, 0,0, NULL }


struct  _JobReportProto
{
  ProtobufCMessage base;
  JobIdProto *job_id;
  protobuf_c_boolean has_job_state;
  JobStateProto job_state;
  protobuf_c_boolean has_map_progress;
  float map_progress;
  protobuf_c_boolean has_reduce_progress;
  float reduce_progress;
  protobuf_c_boolean has_cleanup_progress;
  float cleanup_progress;
  protobuf_c_boolean has_setup_progress;
  float setup_progress;
  protobuf_c_boolean has_start_time;
  int64_t start_time;
  protobuf_c_boolean has_finish_time;
  int64_t finish_time;
  char *user;
  char *jobname;
  char *trackingurl;
  char *diagnostics;
  char *jobfile;
  size_t n_am_infos;
  AMInfoProto **am_infos;
  protobuf_c_boolean has_submit_time;
  int64_t submit_time;
  protobuf_c_boolean has_is_uber;
  protobuf_c_boolean is_uber;
};
#define JOB_REPORT_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&job_report_proto__descriptor) \
    , NULL, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, NULL, NULL, NULL, NULL, NULL, 0,NULL, 0,0, 0,0 }


struct  _AMInfoProto
{
  ProtobufCMessage base;
  ApplicationAttemptIdProto *application_attempt_id;
  protobuf_c_boolean has_start_time;
  int64_t start_time;
  ContainerIdProto *container_id;
  char *node_manager_host;
  protobuf_c_boolean has_node_manager_port;
  int32_t node_manager_port;
  protobuf_c_boolean has_node_manager_http_port;
  int32_t node_manager_http_port;
};
#define AMINFO_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&aminfo_proto__descriptor) \
    , NULL, 0,0, NULL, NULL, 0,0, 0,0 }


struct  _TaskAttemptCompletionEventProto
{
  ProtobufCMessage base;
  TaskAttemptIdProto *attempt_id;
  protobuf_c_boolean has_status;
  TaskAttemptCompletionEventStatusProto status;
  char *map_output_server_address;
  protobuf_c_boolean has_attempt_run_time;
  int32_t attempt_run_time;
  protobuf_c_boolean has_event_id;
  int32_t event_id;
};
#define TASK_ATTEMPT_COMPLETION_EVENT_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&task_attempt_completion_event_proto__descriptor) \
    , NULL, 0,0, NULL, 0,0, 0,0 }


struct  _StringCounterMapProto
{
  ProtobufCMessage base;
  char *key;
  CounterProto *value;
};
#define STRING_COUNTER_MAP_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&string_counter_map_proto__descriptor) \
    , NULL, NULL }


struct  _StringCounterGroupMapProto
{
  ProtobufCMessage base;
  char *key;
  CounterGroupProto *value;
};
#define STRING_COUNTER_GROUP_MAP_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&string_counter_group_map_proto__descriptor) \
    , NULL, NULL }


/* JobIdProto methods */
void   job_id_proto__init
                     (JobIdProto         *message);
size_t job_id_proto__get_packed_size
                     (const JobIdProto   *message);
size_t job_id_proto__pack
                     (const JobIdProto   *message,
                      uint8_t             *out);
size_t job_id_proto__pack_to_buffer
                     (const JobIdProto   *message,
                      ProtobufCBuffer     *buffer);
JobIdProto *
       job_id_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   job_id_proto__free_unpacked
                     (JobIdProto *message,
                      ProtobufCAllocator *allocator);
/* TaskIdProto methods */
void   task_id_proto__init
                     (TaskIdProto         *message);
size_t task_id_proto__get_packed_size
                     (const TaskIdProto   *message);
size_t task_id_proto__pack
                     (const TaskIdProto   *message,
                      uint8_t             *out);
size_t task_id_proto__pack_to_buffer
                     (const TaskIdProto   *message,
                      ProtobufCBuffer     *buffer);
TaskIdProto *
       task_id_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   task_id_proto__free_unpacked
                     (TaskIdProto *message,
                      ProtobufCAllocator *allocator);
/* TaskAttemptIdProto methods */
void   task_attempt_id_proto__init
                     (TaskAttemptIdProto         *message);
size_t task_attempt_id_proto__get_packed_size
                     (const TaskAttemptIdProto   *message);
size_t task_attempt_id_proto__pack
                     (const TaskAttemptIdProto   *message,
                      uint8_t             *out);
size_t task_attempt_id_proto__pack_to_buffer
                     (const TaskAttemptIdProto   *message,
                      ProtobufCBuffer     *buffer);
TaskAttemptIdProto *
       task_attempt_id_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   task_attempt_id_proto__free_unpacked
                     (TaskAttemptIdProto *message,
                      ProtobufCAllocator *allocator);
/* CounterProto methods */
void   counter_proto__init
                     (CounterProto         *message);
size_t counter_proto__get_packed_size
                     (const CounterProto   *message);
size_t counter_proto__pack
                     (const CounterProto   *message,
                      uint8_t             *out);
size_t counter_proto__pack_to_buffer
                     (const CounterProto   *message,
                      ProtobufCBuffer     *buffer);
CounterProto *
       counter_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   counter_proto__free_unpacked
                     (CounterProto *message,
                      ProtobufCAllocator *allocator);
/* CounterGroupProto methods */
void   counter_group_proto__init
                     (CounterGroupProto         *message);
size_t counter_group_proto__get_packed_size
                     (const CounterGroupProto   *message);
size_t counter_group_proto__pack
                     (const CounterGroupProto   *message,
                      uint8_t             *out);
size_t counter_group_proto__pack_to_buffer
                     (const CounterGroupProto   *message,
                      ProtobufCBuffer     *buffer);
CounterGroupProto *
       counter_group_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   counter_group_proto__free_unpacked
                     (CounterGroupProto *message,
                      ProtobufCAllocator *allocator);
/* CountersProto methods */
void   counters_proto__init
                     (CountersProto         *message);
size_t counters_proto__get_packed_size
                     (const CountersProto   *message);
size_t counters_proto__pack
                     (const CountersProto   *message,
                      uint8_t             *out);
size_t counters_proto__pack_to_buffer
                     (const CountersProto   *message,
                      ProtobufCBuffer     *buffer);
CountersProto *
       counters_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   counters_proto__free_unpacked
                     (CountersProto *message,
                      ProtobufCAllocator *allocator);
/* TaskReportProto methods */
void   task_report_proto__init
                     (TaskReportProto         *message);
size_t task_report_proto__get_packed_size
                     (const TaskReportProto   *message);
size_t task_report_proto__pack
                     (const TaskReportProto   *message,
                      uint8_t             *out);
size_t task_report_proto__pack_to_buffer
                     (const TaskReportProto   *message,
                      ProtobufCBuffer     *buffer);
TaskReportProto *
       task_report_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   task_report_proto__free_unpacked
                     (TaskReportProto *message,
                      ProtobufCAllocator *allocator);
/* TaskAttemptReportProto methods */
void   task_attempt_report_proto__init
                     (TaskAttemptReportProto         *message);
size_t task_attempt_report_proto__get_packed_size
                     (const TaskAttemptReportProto   *message);
size_t task_attempt_report_proto__pack
                     (const TaskAttemptReportProto   *message,
                      uint8_t             *out);
size_t task_attempt_report_proto__pack_to_buffer
                     (const TaskAttemptReportProto   *message,
                      ProtobufCBuffer     *buffer);
TaskAttemptReportProto *
       task_attempt_report_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   task_attempt_report_proto__free_unpacked
                     (TaskAttemptReportProto *message,
                      ProtobufCAllocator *allocator);
/* JobReportProto methods */
void   job_report_proto__init
                     (JobReportProto         *message);
size_t job_report_proto__get_packed_size
                     (const JobReportProto   *message);
size_t job_report_proto__pack
                     (const JobReportProto   *message,
                      uint8_t             *out);
size_t job_report_proto__pack_to_buffer
                     (const JobReportProto   *message,
                      ProtobufCBuffer     *buffer);
JobReportProto *
       job_report_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   job_report_proto__free_unpacked
                     (JobReportProto *message,
                      ProtobufCAllocator *allocator);
/* AMInfoProto methods */
void   aminfo_proto__init
                     (AMInfoProto         *message);
size_t aminfo_proto__get_packed_size
                     (const AMInfoProto   *message);
size_t aminfo_proto__pack
                     (const AMInfoProto   *message,
                      uint8_t             *out);
size_t aminfo_proto__pack_to_buffer
                     (const AMInfoProto   *message,
                      ProtobufCBuffer     *buffer);
AMInfoProto *
       aminfo_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   aminfo_proto__free_unpacked
                     (AMInfoProto *message,
                      ProtobufCAllocator *allocator);
/* TaskAttemptCompletionEventProto methods */
void   task_attempt_completion_event_proto__init
                     (TaskAttemptCompletionEventProto         *message);
size_t task_attempt_completion_event_proto__get_packed_size
                     (const TaskAttemptCompletionEventProto   *message);
size_t task_attempt_completion_event_proto__pack
                     (const TaskAttemptCompletionEventProto   *message,
                      uint8_t             *out);
size_t task_attempt_completion_event_proto__pack_to_buffer
                     (const TaskAttemptCompletionEventProto   *message,
                      ProtobufCBuffer     *buffer);
TaskAttemptCompletionEventProto *
       task_attempt_completion_event_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   task_attempt_completion_event_proto__free_unpacked
                     (TaskAttemptCompletionEventProto *message,
                      ProtobufCAllocator *allocator);
/* StringCounterMapProto methods */
void   string_counter_map_proto__init
                     (StringCounterMapProto         *message);
size_t string_counter_map_proto__get_packed_size
                     (const StringCounterMapProto   *message);
size_t string_counter_map_proto__pack
                     (const StringCounterMapProto   *message,
                      uint8_t             *out);
size_t string_counter_map_proto__pack_to_buffer
                     (const StringCounterMapProto   *message,
                      ProtobufCBuffer     *buffer);
StringCounterMapProto *
       string_counter_map_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   string_counter_map_proto__free_unpacked
                     (StringCounterMapProto *message,
                      ProtobufCAllocator *allocator);
/* StringCounterGroupMapProto methods */
void   string_counter_group_map_proto__init
                     (StringCounterGroupMapProto         *message);
size_t string_counter_group_map_proto__get_packed_size
                     (const StringCounterGroupMapProto   *message);
size_t string_counter_group_map_proto__pack
                     (const StringCounterGroupMapProto   *message,
                      uint8_t             *out);
size_t string_counter_group_map_proto__pack_to_buffer
                     (const StringCounterGroupMapProto   *message,
                      ProtobufCBuffer     *buffer);
StringCounterGroupMapProto *
       string_counter_group_map_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   string_counter_group_map_proto__free_unpacked
                     (StringCounterGroupMapProto *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*JobIdProto_Closure)
                 (const JobIdProto *message,
                  void *closure_data);
typedef void (*TaskIdProto_Closure)
                 (const TaskIdProto *message,
                  void *closure_data);
typedef void (*TaskAttemptIdProto_Closure)
                 (const TaskAttemptIdProto *message,
                  void *closure_data);
typedef void (*CounterProto_Closure)
                 (const CounterProto *message,
                  void *closure_data);
typedef void (*CounterGroupProto_Closure)
                 (const CounterGroupProto *message,
                  void *closure_data);
typedef void (*CountersProto_Closure)
                 (const CountersProto *message,
                  void *closure_data);
typedef void (*TaskReportProto_Closure)
                 (const TaskReportProto *message,
                  void *closure_data);
typedef void (*TaskAttemptReportProto_Closure)
                 (const TaskAttemptReportProto *message,
                  void *closure_data);
typedef void (*JobReportProto_Closure)
                 (const JobReportProto *message,
                  void *closure_data);
typedef void (*AMInfoProto_Closure)
                 (const AMInfoProto *message,
                  void *closure_data);
typedef void (*TaskAttemptCompletionEventProto_Closure)
                 (const TaskAttemptCompletionEventProto *message,
                  void *closure_data);
typedef void (*StringCounterMapProto_Closure)
                 (const StringCounterMapProto *message,
                  void *closure_data);
typedef void (*StringCounterGroupMapProto_Closure)
                 (const StringCounterGroupMapProto *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    task_type_proto__descriptor;
extern const ProtobufCEnumDescriptor    task_state_proto__descriptor;
extern const ProtobufCEnumDescriptor    phase_proto__descriptor;
extern const ProtobufCEnumDescriptor    task_attempt_state_proto__descriptor;
extern const ProtobufCEnumDescriptor    job_state_proto__descriptor;
extern const ProtobufCEnumDescriptor    task_attempt_completion_event_status_proto__descriptor;
extern const ProtobufCMessageDescriptor job_id_proto__descriptor;
extern const ProtobufCMessageDescriptor task_id_proto__descriptor;
extern const ProtobufCMessageDescriptor task_attempt_id_proto__descriptor;
extern const ProtobufCMessageDescriptor counter_proto__descriptor;
extern const ProtobufCMessageDescriptor counter_group_proto__descriptor;
extern const ProtobufCMessageDescriptor counters_proto__descriptor;
extern const ProtobufCMessageDescriptor task_report_proto__descriptor;
extern const ProtobufCMessageDescriptor task_attempt_report_proto__descriptor;
extern const ProtobufCMessageDescriptor job_report_proto__descriptor;
extern const ProtobufCMessageDescriptor aminfo_proto__descriptor;
extern const ProtobufCMessageDescriptor task_attempt_completion_event_proto__descriptor;
extern const ProtobufCMessageDescriptor string_counter_map_proto__descriptor;
extern const ProtobufCMessageDescriptor string_counter_group_map_proto__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_mr_5fprotos_2eproto__INCLUDED */