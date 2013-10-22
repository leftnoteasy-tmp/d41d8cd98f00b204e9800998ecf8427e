#include "log_utils.h"
#include "str_utils.h"
#include "yarn_protos_utils.h"

#include <stdlib.h>
#include <assert.h>

static void fill_yarn_string_string_map_proto(
    Hadoop__Yarn__StringStringMapProto* p, char* key, char* value);
static int get_count_of_env_arr(char** env);

void fill_yarn_priority_proto(Hadoop__Yarn__PriorityProto* p, int priority) {
    p->priority = priority;
    p->has_priority = true;
} 

void fill_container_launch_context_proto(
        Hadoop__Yarn__ContainerLaunchContextProto* p,
        containers_launch_context_t* ctx) {
    int i;

    // set env
    int count = get_count_of_env_arr(ctx->env);
    p->n_environment = count;
    p->environment = malloc(sizeof(void*) * count);
    for (i = 0; i < count; i++) {
        Hadoop__Yarn__StringStringMapProto strstr_proto = HADOOP__YARN__STRING_STRING_MAP_PROTO__INIT;
        p->environment[i] = &strstr_proto;
        fill_yarn_string_string_map_proto(
            p->environment[i], get_env_key(ctx->env[i]), get_env_val(ctx->env[i]));
    }

    // set cmd
    p->n_command = 1;
    p->command = malloc(sizeof(void*));
    p->command[0] = ctx->command;
}

void fill_yarn_resource_proto(Hadoop__Yarn__ResourceProto* p, yarn_resource_t* resource) {
    p->memory = resource->memory;
    p->virtual_cores = resource->cpu;
    p->has_memory = true;
    p->has_virtual_cores = true;
}

static void fill_yarn_string_string_map_proto(
    Hadoop__Yarn__StringStringMapProto* p, char* key, char* value) {
    assert ((key != NULL) && (value != NULL));
    p->key = key;
    p->value = value;
} 

static get_count_of_env_arr(char** env) {
    int idx = 0;
    while (!env[idx]) {
        idx++;
    }
    return idx;
}

