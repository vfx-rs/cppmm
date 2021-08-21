#pragma once
#include "exceptions-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct ex__Struct_t_s {
    char data[1];
} EXCEPTIONS_CPPMM_ALIGN(1) ex__Struct_t;
typedef ex__Struct_t ex_Struct_t;


/** returns the size of this type in bytes */
EXCEPTIONS_CPPMM_API unsigned int ex__Struct_sizeof();
#define ex_Struct_sizeof ex__Struct_sizeof


/** returns the size of this type in bytes */
EXCEPTIONS_CPPMM_API unsigned int ex__Struct_alignof();
#define ex_Struct_alignof ex__Struct_alignof


EXCEPTIONS_CPPMM_API unsigned int ex__Struct_m1(
    ex_Struct_t * this_);
#define ex_Struct_m1 ex__Struct_m1


EXCEPTIONS_CPPMM_API unsigned int ex__Struct_m2(
    ex_Struct_t * this_
    , float * return_
    , float a);
#define ex_Struct_m2 ex__Struct_m2


EXCEPTIONS_CPPMM_API unsigned int ex__Struct_m3(
    ex_Struct_t const * this_
    , float * return_
    , int a);
#define ex_Struct_m3 ex__Struct_m3


EXCEPTIONS_CPPMM_API unsigned int ex__Struct_m4(
    ex_Struct_t const * this_
    , float * return_
    , int a);
#define ex_Struct_m4 ex__Struct_m4


EXCEPTIONS_CPPMM_API unsigned int ex_f1(
    float * return_
    , int a);

EXCEPTIONS_CPPMM_API unsigned int ex_f2();

#ifdef __cplusplus
}
#endif
