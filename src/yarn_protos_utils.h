#ifndef _YARN_YARN_PROTOS_UTILS_H
#define _YARN_YARN_PROTOS_UTILS_H

#include "yarn_protos.pb-c.h"

#include "yarn.h"

void fill_yarn_priority_proto(Hadoop__Yarn__PriorityProto* p, int priority);

void fill_container_launch_context_proto(Hadoop__Yarn__ContainerLaunchContextProto* p, containers_launch_context_t* ctx);

void fill_yarn_resource_proto(Hadoop__Yarn__ResourceProto* p, yarn_resource_t* resource);

#endif 