#pragma once
#include "imath-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct Imath_2_5__Vec3_float__t_s {
    float x;
    float y;
    float z;
} IMATH_CPPMM_ALIGN(4) Imath_2_5__Vec3_float__t;
typedef Imath_2_5__Vec3_float__t Imath_V3f_t;

typedef struct Imath_2_5__Vec3_int__t_s {
    int x;
    int y;
    int z;
} IMATH_CPPMM_ALIGN(4) Imath_2_5__Vec3_int__t;
typedef Imath_2_5__Vec3_int__t Imath_V3i_t;


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__ctor(
    Imath_V3f_t * this_);
#define Imath_V3f_ctor Imath_2_5__Vec3_float__ctor


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__ctor_1(
    Imath_V3f_t * this_
    , Imath_V3f_t const * rhs);
#define Imath_V3f_ctor_1 Imath_2_5__Vec3_float__ctor_1


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__setValue(
    Imath_V3f_t * this_
    , float a
    , float b
    , float c);
#define Imath_V3f_setValue Imath_2_5__Vec3_float__setValue


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__dot(
    Imath_V3f_t const * this_
    , float * return_
    , Imath_V3f_t const * v);
#define Imath_V3f_dot Imath_2_5__Vec3_float__dot


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__cross(
    Imath_V3f_t const * this_
    , Imath_V3f_t * return_
    , Imath_V3f_t const * v);
#define Imath_V3f_cross Imath_2_5__Vec3_float__cross


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__op_iadd(
    Imath_V3f_t * this_
    , Imath_V3f_t const * * return_
    , Imath_V3f_t const * v);
#define Imath_V3f_op_iadd Imath_2_5__Vec3_float__op_iadd


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__length(
    Imath_V3f_t const * this_
    , float * return_);
#define Imath_V3f_length Imath_2_5__Vec3_float__length


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__length2(
    Imath_V3f_t const * this_
    , float * return_);
#define Imath_V3f_length2 Imath_2_5__Vec3_float__length2


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__normalize(
    Imath_V3f_t * this_
    , Imath_V3f_t const * * return_);
#define Imath_V3f_normalize Imath_2_5__Vec3_float__normalize


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_float__normalized(
    Imath_V3f_t const * this_
    , Imath_V3f_t * return_);
#define Imath_V3f_normalized Imath_2_5__Vec3_float__normalized


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_int__ctor(
    Imath_V3i_t * this_);
#define Imath_V3i_ctor Imath_2_5__Vec3_int__ctor


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_int__ctor_1(
    Imath_V3i_t * this_
    , Imath_V3i_t const * rhs);
#define Imath_V3i_ctor_1 Imath_2_5__Vec3_int__ctor_1


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_int__dot(
    Imath_V3i_t const * this_
    , int * return_
    , Imath_V3i_t const * v);
#define Imath_V3i_dot Imath_2_5__Vec3_int__dot


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_int__cross(
    Imath_V3i_t const * this_
    , Imath_V3i_t * return_
    , Imath_V3i_t const * v);
#define Imath_V3i_cross Imath_2_5__Vec3_int__cross


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_int__op_iadd(
    Imath_V3i_t * this_
    , Imath_V3i_t const * * return_
    , Imath_V3i_t const * v);
#define Imath_V3i_op_iadd Imath_2_5__Vec3_int__op_iadd


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_int__length(
    Imath_V3i_t const * this_
    , int * return_);
#define Imath_V3i_length Imath_2_5__Vec3_int__length


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_int__length2(
    Imath_V3i_t const * this_
    , int * return_);
#define Imath_V3i_length2 Imath_2_5__Vec3_int__length2


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_int__normalize(
    Imath_V3i_t * this_
    , Imath_V3i_t const * * return_);
#define Imath_V3i_normalize Imath_2_5__Vec3_int__normalize


IMATH_CPPMM_API unsigned int Imath_2_5__Vec3_int__normalized(
    Imath_V3i_t const * this_
    , Imath_V3i_t * return_);
#define Imath_V3i_normalized Imath_2_5__Vec3_int__normalized


#ifdef __cplusplus
}
#endif
