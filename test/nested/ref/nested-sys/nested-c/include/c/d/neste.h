#pragma once
#include "nested-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct nest__NestCDE_t_s {
    int cd;
} NESTED_CPPMM_ALIGN(4) nest__NestCDE_t;
typedef nest__NestCDE_t nest_NestCDE_t;


NESTED_CPPMM_API unsigned int nest__NestCDE_do_something(
    nest_NestCDE_t * this_);
#define nest_NestCDE_do_something nest__NestCDE_do_something


#ifdef __cplusplus
}
#endif
