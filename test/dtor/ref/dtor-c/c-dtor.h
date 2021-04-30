#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dtor__Struct_t_s {
    char data[48];
} __attribute__((aligned(8))) dtor__Struct_t;
typedef dtor__Struct_t dtor_Struct_t;



void dtor__Struct_Struct(
    dtor_Struct_t * this_);
#define dtor_Struct_Struct dtor__Struct_Struct


void dtor__Struct_dtor(
    dtor_Struct_t * this_);
#define dtor_Struct_dtor dtor__Struct_dtor









#ifdef __cplusplus
}
#endif
