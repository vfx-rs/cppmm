#pragma once

#include "cppmm_containers.h"


#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#define CPPMM_ALIGN(x) __declspec(align(x))
#else
#define CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif

typedef struct {
    int x;
    int y;
    int z;
} templates_V3i;

typedef struct {
    float x;
    float y;
    float z;
} templates_V3f;



void templates_takes_vector3_and_t(templates_V3i* v, float w);


void templates_takes_two_vector3(templates_V3i* v, templates_V3f* w);


void templates_takes_vector3(templates_V3f* v);


void templates_takes_vector3(templates_V3i* v);


void templates_V3i_some_other(templates_V3i* self, int t);


int templates_V3i_length(const templates_V3i* self);


void templates_V3f_some_other(templates_V3f* self, float t);


float templates_V3f_length(const templates_V3f* self);


#undef CPPMM_ALIGN

#define templates_V3i templates_V3i
#define templates_V3f templates_V3f
#define templates_takes_vector3_and_t templates_takes_vector3_and_t
#define templates_takes_two_vector3 templates_takes_two_vector3
#define templates_takes_vector3 templates_takes_vector3
#define templates_takes_vector3 templates_takes_vector3
#define templates_V3i_some_other templates_V3i_some_other
#define templates_V3i_length templates_V3i_length
#define templates_V3f_some_other templates_V3f_some_other
#define templates_V3f_length templates_V3f_length

#ifdef __cplusplus
}
#endif
    