#pragma once
#include "nested-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct nest__NestAE_t_s {
    int a;
} NESTED_CPPMM_ALIGN(4) nest__NestAE_t;
typedef nest__NestAE_t nest_NestAE_t;


NESTED_CPPMM_API unsigned int nest__NestAE_do_something(
    nest_NestAE_t * this_);
#define nest_NestAE_do_something nest__NestAE_do_something


#ifdef __cplusplus
}
#endif
