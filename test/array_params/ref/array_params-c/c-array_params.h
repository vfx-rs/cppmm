#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct imath__Matrix44_float__t_s {
    float data[4][4];
} __attribute__((aligned(4))) imath__Matrix44_float__t;
typedef imath__Matrix44_float__t imath_M44f_t;



void imath__Matrix44_float__from_array(
    imath_M44f_t * this_
    , float const a[4][4]);
#define imath_M44f_from_array imath__Matrix44_float__from_array










#ifdef __cplusplus
}
#endif
