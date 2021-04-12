#pragma once
#include <imath_vec_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imath_2_5_M33f_s {
    char data[36];
} __attribute__((aligned(4))) Imath_2_5_M33f;
typedef struct Imath_2_5_M33d_s {
    char data[72];
} __attribute__((aligned(8))) Imath_2_5_M33d;
typedef struct Imath_2_5_M44f_s {
    char data[64];
} __attribute__((aligned(4))) Imath_2_5_M44f;
typedef struct Imath_2_5_M44d_s {
    char data[128];
} __attribute__((aligned(8))) Imath_2_5_M44d;


float * Imath_2_5_M33f__index(
    Imath_2_5_M33f * this_
    , int i);


float const * Imath_2_5_M33f__index_1(
    Imath_2_5_M33f const * this_
    , int i);


void Imath_2_5_M33f_Matrix33(
    Imath_2_5_M33f * this_);


void Imath_2_5_M33f_Matrix33_1(
    Imath_2_5_M33f * this_
    , float a);


void Imath_2_5_M33f_Matrix33_2(
    Imath_2_5_M33f * this_
    , float a
    , float b
    , float c
    , float d
    , float e
    , float f
    , float g
    , float h
    , float i);


void Imath_2_5_M33f_Matrix33_3(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v);


Imath_2_5_M33f const * Imath_2_5_M33f__assign(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v);


Imath_2_5_M33f const * Imath_2_5_M33f__assign_1(
    Imath_2_5_M33f * this_
    , float a);


void Imath_2_5_M33f_dtor(
    Imath_2_5_M33f * this_);


float * Imath_2_5_M33f_getValue(
    Imath_2_5_M33f * this_);


float const * Imath_2_5_M33f_getValue_1(
    Imath_2_5_M33f const * this_);


void Imath_2_5_M33f_makeIdentity(
    Imath_2_5_M33f * this_);


_Bool Imath_2_5_M33f__eq(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v);


_Bool Imath_2_5_M33f__ne(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v);


_Bool Imath_2_5_M33f_equalWithAbsError(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v
    , float e);


_Bool Imath_2_5_M33f_equalWithRelError(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v
    , float e);


Imath_2_5_M33f const * Imath_2_5_M33f__op_iadd(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v);


Imath_2_5_M33f const * Imath_2_5_M33f__op_iadd_1(
    Imath_2_5_M33f * this_
    , float a);


Imath_2_5_M33f Imath_2_5_M33f__op_add(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v);


Imath_2_5_M33f const * Imath_2_5_M33f__op_isub(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v);


Imath_2_5_M33f const * Imath_2_5_M33f__op_isub_1(
    Imath_2_5_M33f * this_
    , float a);


Imath_2_5_M33f Imath_2_5_M33f__op_sub(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v);


Imath_2_5_M33f Imath_2_5_M33f__op_sub_1(
    Imath_2_5_M33f const * this_);


Imath_2_5_M33f const * Imath_2_5_M33f_negate(
    Imath_2_5_M33f * this_);


Imath_2_5_M33f const * Imath_2_5_M33f__op_imul(
    Imath_2_5_M33f * this_
    , float a);


Imath_2_5_M33f Imath_2_5_M33f__op_mul(
    Imath_2_5_M33f const * this_
    , float a);


Imath_2_5_M33f const * Imath_2_5_M33f__op_imul_1(
    Imath_2_5_M33f * this_
    , Imath_2_5_M33f const * v);


Imath_2_5_M33f Imath_2_5_M33f__op_mul_1(
    Imath_2_5_M33f const * this_
    , Imath_2_5_M33f const * v);


Imath_2_5_M33f const * Imath_2_5_M33f__op_idiv(
    Imath_2_5_M33f * this_
    , float a);


Imath_2_5_M33f Imath_2_5_M33f__op_div(
    Imath_2_5_M33f const * this_
    , float a);


Imath_2_5_M33f const * Imath_2_5_M33f_transpose(
    Imath_2_5_M33f * this_);


Imath_2_5_M33f Imath_2_5_M33f_transposed(
    Imath_2_5_M33f const * this_);


Imath_2_5_M33f const * Imath_2_5_M33f_invert(
    Imath_2_5_M33f * this_
    , _Bool singExc);


Imath_2_5_M33f Imath_2_5_M33f_inverse(
    Imath_2_5_M33f const * this_
    , _Bool singExc);


Imath_2_5_M33f const * Imath_2_5_M33f_gjInvert(
    Imath_2_5_M33f * this_
    , _Bool singExc);


Imath_2_5_M33f Imath_2_5_M33f_gjInverse(
    Imath_2_5_M33f const * this_
    , _Bool singExc);


float Imath_2_5_M33f_minorOf(
    Imath_2_5_M33f const * this_
    , int const r
    , int const c);


float Imath_2_5_M33f_fastMinor(
    Imath_2_5_M33f const * this_
    , int const r0
    , int const r1
    , int const c0
    , int const c1);


float Imath_2_5_M33f_determinant(
    Imath_2_5_M33f const * this_);


Imath_2_5_M33f const * Imath_2_5_M33f_setScale(
    Imath_2_5_M33f * this_
    , float s);


Imath_2_5_V2f Imath_2_5_M33f_translation(
    Imath_2_5_M33f const * this_);











double * Imath_2_5_M33d__index(
    Imath_2_5_M33d * this_
    , int i);


double const * Imath_2_5_M33d__index_1(
    Imath_2_5_M33d const * this_
    , int i);


void Imath_2_5_M33d_Matrix33(
    Imath_2_5_M33d * this_);


void Imath_2_5_M33d_Matrix33_1(
    Imath_2_5_M33d * this_
    , double a);


void Imath_2_5_M33d_Matrix33_2(
    Imath_2_5_M33d * this_
    , double a
    , double b
    , double c
    , double d
    , double e
    , double f
    , double g
    , double h
    , double i);


void Imath_2_5_M33d_Matrix33_3(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v);


Imath_2_5_M33d const * Imath_2_5_M33d__assign(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v);


Imath_2_5_M33d const * Imath_2_5_M33d__assign_1(
    Imath_2_5_M33d * this_
    , double a);


void Imath_2_5_M33d_dtor(
    Imath_2_5_M33d * this_);


double * Imath_2_5_M33d_getValue(
    Imath_2_5_M33d * this_);


double const * Imath_2_5_M33d_getValue_1(
    Imath_2_5_M33d const * this_);


void Imath_2_5_M33d_makeIdentity(
    Imath_2_5_M33d * this_);


_Bool Imath_2_5_M33d__eq(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v);


_Bool Imath_2_5_M33d__ne(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v);


_Bool Imath_2_5_M33d_equalWithAbsError(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v
    , double e);


_Bool Imath_2_5_M33d_equalWithRelError(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v
    , double e);


Imath_2_5_M33d const * Imath_2_5_M33d__op_iadd(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v);


Imath_2_5_M33d const * Imath_2_5_M33d__op_iadd_1(
    Imath_2_5_M33d * this_
    , double a);


Imath_2_5_M33d Imath_2_5_M33d__op_add(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v);


Imath_2_5_M33d const * Imath_2_5_M33d__op_isub(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v);


Imath_2_5_M33d const * Imath_2_5_M33d__op_isub_1(
    Imath_2_5_M33d * this_
    , double a);


Imath_2_5_M33d Imath_2_5_M33d__op_sub(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v);


Imath_2_5_M33d Imath_2_5_M33d__op_sub_1(
    Imath_2_5_M33d const * this_);


Imath_2_5_M33d const * Imath_2_5_M33d_negate(
    Imath_2_5_M33d * this_);


Imath_2_5_M33d const * Imath_2_5_M33d__op_imul(
    Imath_2_5_M33d * this_
    , double a);


Imath_2_5_M33d Imath_2_5_M33d__op_mul(
    Imath_2_5_M33d const * this_
    , double a);


Imath_2_5_M33d const * Imath_2_5_M33d__op_imul_1(
    Imath_2_5_M33d * this_
    , Imath_2_5_M33d const * v);


Imath_2_5_M33d Imath_2_5_M33d__op_mul_1(
    Imath_2_5_M33d const * this_
    , Imath_2_5_M33d const * v);


Imath_2_5_M33d const * Imath_2_5_M33d__op_idiv(
    Imath_2_5_M33d * this_
    , double a);


Imath_2_5_M33d Imath_2_5_M33d__op_div(
    Imath_2_5_M33d const * this_
    , double a);


Imath_2_5_M33d const * Imath_2_5_M33d_transpose(
    Imath_2_5_M33d * this_);


Imath_2_5_M33d Imath_2_5_M33d_transposed(
    Imath_2_5_M33d const * this_);


Imath_2_5_M33d const * Imath_2_5_M33d_invert(
    Imath_2_5_M33d * this_
    , _Bool singExc);


Imath_2_5_M33d Imath_2_5_M33d_inverse(
    Imath_2_5_M33d const * this_
    , _Bool singExc);


Imath_2_5_M33d const * Imath_2_5_M33d_gjInvert(
    Imath_2_5_M33d * this_
    , _Bool singExc);


Imath_2_5_M33d Imath_2_5_M33d_gjInverse(
    Imath_2_5_M33d const * this_
    , _Bool singExc);


double Imath_2_5_M33d_minorOf(
    Imath_2_5_M33d const * this_
    , int const r
    , int const c);


double Imath_2_5_M33d_fastMinor(
    Imath_2_5_M33d const * this_
    , int const r0
    , int const r1
    , int const c0
    , int const c1);


double Imath_2_5_M33d_determinant(
    Imath_2_5_M33d const * this_);


Imath_2_5_M33d const * Imath_2_5_M33d_setScale(
    Imath_2_5_M33d * this_
    , double s);


Imath_2_5_V2d Imath_2_5_M33d_translation(
    Imath_2_5_M33d const * this_);











float * Imath_2_5_M44f__index(
    Imath_2_5_M44f * this_
    , int i);


float const * Imath_2_5_M44f__index_1(
    Imath_2_5_M44f const * this_
    , int i);


void Imath_2_5_M44f_Matrix44(
    Imath_2_5_M44f * this_);


void Imath_2_5_M44f_Matrix44_1(
    Imath_2_5_M44f * this_
    , float a);


void Imath_2_5_M44f_Matrix44_2(
    Imath_2_5_M44f * this_
    , float a
    , float b
    , float c
    , float d
    , float e
    , float f
    , float g
    , float h
    , float i
    , float j
    , float k
    , float l
    , float m
    , float n
    , float o
    , float p);


void Imath_2_5_M44f_Matrix44_3(
    Imath_2_5_M44f * this_
    , Imath_2_5_M33f r
    , Imath_2_5_V3f t);


void Imath_2_5_M44f_dtor(
    Imath_2_5_M44f * this_);


void Imath_2_5_M44f_Matrix44_4(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v);


Imath_2_5_M44f const * Imath_2_5_M44f__assign(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v);


Imath_2_5_M44f const * Imath_2_5_M44f__assign_1(
    Imath_2_5_M44f * this_
    , float a);


float * Imath_2_5_M44f_getValue(
    Imath_2_5_M44f * this_);


float const * Imath_2_5_M44f_getValue_1(
    Imath_2_5_M44f const * this_);


void Imath_2_5_M44f_makeIdentity(
    Imath_2_5_M44f * this_);


_Bool Imath_2_5_M44f__eq(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v);


_Bool Imath_2_5_M44f__ne(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v);


_Bool Imath_2_5_M44f_equalWithAbsError(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v
    , float e);


_Bool Imath_2_5_M44f_equalWithRelError(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v
    , float e);


Imath_2_5_M44f const * Imath_2_5_M44f__op_iadd(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v);


Imath_2_5_M44f const * Imath_2_5_M44f__op_iadd_1(
    Imath_2_5_M44f * this_
    , float a);


Imath_2_5_M44f Imath_2_5_M44f__op_add(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v);


Imath_2_5_M44f const * Imath_2_5_M44f__op_isub(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v);


Imath_2_5_M44f const * Imath_2_5_M44f__op_isub_1(
    Imath_2_5_M44f * this_
    , float a);


Imath_2_5_M44f Imath_2_5_M44f__op_sub(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v);


Imath_2_5_M44f Imath_2_5_M44f__op_sub_1(
    Imath_2_5_M44f const * this_);


Imath_2_5_M44f const * Imath_2_5_M44f_negate(
    Imath_2_5_M44f * this_);


Imath_2_5_M44f const * Imath_2_5_M44f__op_imul(
    Imath_2_5_M44f * this_
    , float a);


Imath_2_5_M44f Imath_2_5_M44f__op_mul(
    Imath_2_5_M44f const * this_
    , float a);


Imath_2_5_M44f const * Imath_2_5_M44f__op_imul_1(
    Imath_2_5_M44f * this_
    , Imath_2_5_M44f const * v);


Imath_2_5_M44f Imath_2_5_M44f__op_mul_1(
    Imath_2_5_M44f const * this_
    , Imath_2_5_M44f const * v);


Imath_2_5_M44f const * Imath_2_5_M44f__op_idiv(
    Imath_2_5_M44f * this_
    , float a);


Imath_2_5_M44f Imath_2_5_M44f__op_div(
    Imath_2_5_M44f const * this_
    , float a);


Imath_2_5_M44f const * Imath_2_5_M44f_transpose(
    Imath_2_5_M44f * this_);


Imath_2_5_M44f Imath_2_5_M44f_transposed(
    Imath_2_5_M44f const * this_);


Imath_2_5_M44f const * Imath_2_5_M44f_invert(
    Imath_2_5_M44f * this_
    , _Bool singExc);


Imath_2_5_M44f Imath_2_5_M44f_inverse(
    Imath_2_5_M44f const * this_
    , _Bool singExc);


Imath_2_5_M44f const * Imath_2_5_M44f_gjInvert(
    Imath_2_5_M44f * this_
    , _Bool singExc);


Imath_2_5_M44f Imath_2_5_M44f_gjInverse(
    Imath_2_5_M44f const * this_
    , _Bool singExc);


float Imath_2_5_M44f_minorOf(
    Imath_2_5_M44f const * this_
    , int const r
    , int const c);


float Imath_2_5_M44f_fastMinor(
    Imath_2_5_M44f const * this_
    , int const r0
    , int const r1
    , int const r2
    , int const c0
    , int const c1
    , int const c2);


float Imath_2_5_M44f_determinant(
    Imath_2_5_M44f const * this_);


Imath_2_5_M44f const * Imath_2_5_M44f_setScale(
    Imath_2_5_M44f * this_
    , float s);


Imath_2_5_V3f const Imath_2_5_M44f_translation(
    Imath_2_5_M44f const * this_);











double * Imath_2_5_M44d__index(
    Imath_2_5_M44d * this_
    , int i);


double const * Imath_2_5_M44d__index_1(
    Imath_2_5_M44d const * this_
    , int i);


void Imath_2_5_M44d_Matrix44(
    Imath_2_5_M44d * this_);


void Imath_2_5_M44d_Matrix44_1(
    Imath_2_5_M44d * this_
    , double a);


void Imath_2_5_M44d_Matrix44_2(
    Imath_2_5_M44d * this_
    , double a
    , double b
    , double c
    , double d
    , double e
    , double f
    , double g
    , double h
    , double i
    , double j
    , double k
    , double l
    , double m
    , double n
    , double o
    , double p);


void Imath_2_5_M44d_Matrix44_3(
    Imath_2_5_M44d * this_
    , Imath_2_5_M33d r
    , Imath_2_5_V3d t);


void Imath_2_5_M44d_dtor(
    Imath_2_5_M44d * this_);


void Imath_2_5_M44d_Matrix44_4(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v);


Imath_2_5_M44d const * Imath_2_5_M44d__assign(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v);


Imath_2_5_M44d const * Imath_2_5_M44d__assign_1(
    Imath_2_5_M44d * this_
    , double a);


double * Imath_2_5_M44d_getValue(
    Imath_2_5_M44d * this_);


double const * Imath_2_5_M44d_getValue_1(
    Imath_2_5_M44d const * this_);


void Imath_2_5_M44d_makeIdentity(
    Imath_2_5_M44d * this_);


_Bool Imath_2_5_M44d__eq(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v);


_Bool Imath_2_5_M44d__ne(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v);


_Bool Imath_2_5_M44d_equalWithAbsError(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v
    , double e);


_Bool Imath_2_5_M44d_equalWithRelError(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v
    , double e);


Imath_2_5_M44d const * Imath_2_5_M44d__op_iadd(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v);


Imath_2_5_M44d const * Imath_2_5_M44d__op_iadd_1(
    Imath_2_5_M44d * this_
    , double a);


Imath_2_5_M44d Imath_2_5_M44d__op_add(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v);


Imath_2_5_M44d const * Imath_2_5_M44d__op_isub(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v);


Imath_2_5_M44d const * Imath_2_5_M44d__op_isub_1(
    Imath_2_5_M44d * this_
    , double a);


Imath_2_5_M44d Imath_2_5_M44d__op_sub(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v);


Imath_2_5_M44d Imath_2_5_M44d__op_sub_1(
    Imath_2_5_M44d const * this_);


Imath_2_5_M44d const * Imath_2_5_M44d_negate(
    Imath_2_5_M44d * this_);


Imath_2_5_M44d const * Imath_2_5_M44d__op_imul(
    Imath_2_5_M44d * this_
    , double a);


Imath_2_5_M44d Imath_2_5_M44d__op_mul(
    Imath_2_5_M44d const * this_
    , double a);


Imath_2_5_M44d const * Imath_2_5_M44d__op_imul_1(
    Imath_2_5_M44d * this_
    , Imath_2_5_M44d const * v);


Imath_2_5_M44d Imath_2_5_M44d__op_mul_1(
    Imath_2_5_M44d const * this_
    , Imath_2_5_M44d const * v);


Imath_2_5_M44d const * Imath_2_5_M44d__op_idiv(
    Imath_2_5_M44d * this_
    , double a);


Imath_2_5_M44d Imath_2_5_M44d__op_div(
    Imath_2_5_M44d const * this_
    , double a);


Imath_2_5_M44d const * Imath_2_5_M44d_transpose(
    Imath_2_5_M44d * this_);


Imath_2_5_M44d Imath_2_5_M44d_transposed(
    Imath_2_5_M44d const * this_);


Imath_2_5_M44d const * Imath_2_5_M44d_invert(
    Imath_2_5_M44d * this_
    , _Bool singExc);


Imath_2_5_M44d Imath_2_5_M44d_inverse(
    Imath_2_5_M44d const * this_
    , _Bool singExc);


Imath_2_5_M44d const * Imath_2_5_M44d_gjInvert(
    Imath_2_5_M44d * this_
    , _Bool singExc);


Imath_2_5_M44d Imath_2_5_M44d_gjInverse(
    Imath_2_5_M44d const * this_
    , _Bool singExc);


double Imath_2_5_M44d_minorOf(
    Imath_2_5_M44d const * this_
    , int const r
    , int const c);


double Imath_2_5_M44d_fastMinor(
    Imath_2_5_M44d const * this_
    , int const r0
    , int const r1
    , int const r2
    , int const c0
    , int const c1
    , int const c2);


double Imath_2_5_M44d_determinant(
    Imath_2_5_M44d const * this_);


Imath_2_5_M44d const * Imath_2_5_M44d_setScale(
    Imath_2_5_M44d * this_
    , double s);


Imath_2_5_V3d const Imath_2_5_M44d_translation(
    Imath_2_5_M44d const * this_);









#ifdef __cplusplus
}
#endif
