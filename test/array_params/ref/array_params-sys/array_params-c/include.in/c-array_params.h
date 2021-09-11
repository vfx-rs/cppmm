#pragma once
#include "array_params-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct imath__Matrix44_float__t_s {
    float data[4][4];
} ARRAY_PARAMS_CPPMM_ALIGN(4) imath__Matrix44_float__t;
typedef imath__Matrix44_float__t imath_M44f_t;


ARRAY_PARAMS_CPPMM_API unsigned int imath__Matrix44_float__from_array(
    imath_M44f_t * this_
    , float a[4][4]);
#define imath_M44f_from_array imath__Matrix44_float__from_array


#ifdef __cplusplus
}
#endif
