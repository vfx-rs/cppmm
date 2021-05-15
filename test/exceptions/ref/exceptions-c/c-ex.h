#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ex__Struct_t_s {
    char data[1];
} __attribute__((aligned(1))) ex__Struct_t;
typedef ex__Struct_t ex_Struct_t;



/** returns the size of this type in bytes */
unsigned int ex__Struct_sizeof();
#define ex_Struct_sizeof ex__Struct_sizeof


/** returns the size of this type in bytes */
unsigned int ex__Struct_alignof();
#define ex_Struct_alignof ex__Struct_alignof


unsigned int ex__Struct_m1(
    ex_Struct_t * this_);
#define ex_Struct_m1 ex__Struct_m1


unsigned int ex__Struct_m2(
    ex_Struct_t * this_
    , float * return_
    , float a);
#define ex_Struct_m2 ex__Struct_m2











unsigned int ex_f1(
    float * return_
    , int a);

unsigned int ex_f2();
#ifdef __cplusplus
}
#endif
