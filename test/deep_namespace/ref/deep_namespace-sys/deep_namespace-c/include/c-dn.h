#pragma once
#include "deep_namespace-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

enum DN__v2_2__Class__Enum_e {
    DN_Class_Enum_One = 0,
    DN_Class_Enum_Two = 1,
    DN_Class_Enum_Three = 2,
};
typedef unsigned int DN_Class_Enum;

typedef struct DN__v2_2__Class_t_s {
    char _unused;
} DEEP_NAMESPACE_CPPMM_ALIGN(4) DN__v2_2__Class_t;
typedef DN__v2_2__Class_t DN_Class_t;

typedef struct DN__v2_2__Class__Struct_t_s {
    int a;
    float b;
} DEEP_NAMESPACE_CPPMM_ALIGN(4) DN__v2_2__Class__Struct_t;
typedef DN__v2_2__Class__Struct_t DN_Class_Struct_t;


DEEP_NAMESPACE_CPPMM_API unsigned int DN__v2_2__Class__Struct_structMethod(
    DN_Class_Struct_t * this_);
#define DN_Class_Struct_structMethod DN__v2_2__Class__Struct_structMethod


DEEP_NAMESPACE_CPPMM_API unsigned int DN_v2_2_someFunction();
#define DN_someFunction DN_v2_2_someFunction


#ifdef __cplusplus
}
#endif
