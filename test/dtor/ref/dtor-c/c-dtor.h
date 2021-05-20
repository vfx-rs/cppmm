#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dtor__Struct_t_s {
    char _unused;
} __attribute__((aligned(8))) dtor__Struct_t;
typedef dtor__Struct_t dtor_Struct_t;



unsigned int dtor__Struct_ctor(
    dtor_Struct_t * * this_);
#define dtor_Struct_ctor dtor__Struct_ctor


unsigned int dtor__Struct_dtor(
    dtor_Struct_t * this_);
#define dtor_Struct_dtor dtor__Struct_dtor









#ifdef __cplusplus
}
#endif
