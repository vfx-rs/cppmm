#pragma once
#include "dtor-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct dtor__Struct_t_s {
    char _unused;
} DTOR_CPPMM_ALIGN(8) dtor__Struct_t;
typedef dtor__Struct_t dtor_Struct_t;


DTOR_CPPMM_API unsigned int dtor__Struct_ctor(
    dtor_Struct_t * * this_);
#define dtor_Struct_ctor dtor__Struct_ctor


DTOR_CPPMM_API unsigned int dtor__Struct_dtor(
    dtor_Struct_t * this_);
#define dtor_Struct_dtor dtor__Struct_dtor


#ifdef __cplusplus
}
#endif
