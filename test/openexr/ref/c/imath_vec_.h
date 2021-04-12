#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imath_2_5_V2s_s {
    char data[4];
} __attribute__((aligned(2))) Imath_2_5_V2s;
typedef struct Imath_2_5_V2i_s {
    char data[8];
} __attribute__((aligned(4))) Imath_2_5_V2i;
typedef struct Imath_2_5_V2f_s {
    char data[8];
} __attribute__((aligned(4))) Imath_2_5_V2f;
typedef struct Imath_2_5_V2d_s {
    char data[16];
} __attribute__((aligned(8))) Imath_2_5_V2d;
typedef struct Imath_2_5_V3s_s {
    char data[6];
} __attribute__((aligned(2))) Imath_2_5_V3s;
typedef struct Imath_2_5_V3i_s {
    char data[12];
} __attribute__((aligned(4))) Imath_2_5_V3i;
typedef struct Imath_2_5_V3f_s {
    char data[12];
} __attribute__((aligned(4))) Imath_2_5_V3f;
typedef struct Imath_2_5_V3d_s {
    char data[24];
} __attribute__((aligned(8))) Imath_2_5_V3d;
typedef struct Imath_2_5_V4s_s {
    char data[8];
} __attribute__((aligned(2))) Imath_2_5_V4s;
typedef struct Imath_2_5_V4i_s {
    char data[16];
} __attribute__((aligned(4))) Imath_2_5_V4i;
typedef struct Imath_2_5_V4f_s {
    char data[16];
} __attribute__((aligned(4))) Imath_2_5_V4f;
typedef struct Imath_2_5_V4d_s {
    char data[32];
} __attribute__((aligned(8))) Imath_2_5_V4d;


short * Imath_2_5_V2s__index(
    Imath_2_5_V2s * this_
    , int i);


short const * Imath_2_5_V2s__index_1(
    Imath_2_5_V2s const * this_
    , int i);


void Imath_2_5_V2s_Vec2(
    Imath_2_5_V2s * this_);


void Imath_2_5_V2s_Vec2_1(
    Imath_2_5_V2s * this_
    , short a);


void Imath_2_5_V2s_Vec2_2(
    Imath_2_5_V2s * this_
    , short a
    , short b);


void Imath_2_5_V2s_Vec2_3(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s const * Imath_2_5_V2s__assign(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v);


void Imath_2_5_V2s_dtor(
    Imath_2_5_V2s * this_);


short * Imath_2_5_V2s_getValue(
    Imath_2_5_V2s * this_);


short const * Imath_2_5_V2s_getValue_1(
    Imath_2_5_V2s const * this_);


_Bool Imath_2_5_V2s_equalWithAbsError(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v
    , short e);


_Bool Imath_2_5_V2s_equalWithRelError(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v
    , short e);


short Imath_2_5_V2s_dot(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v);


short Imath_2_5_V2s_operator^(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v);


short Imath_2_5_V2s_cross(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v);


short Imath_2_5_V2s_operator%(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s const * Imath_2_5_V2s__op_iadd(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s Imath_2_5_V2s__op_add(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s const * Imath_2_5_V2s__op_isub(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s Imath_2_5_V2s__op_sub(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s Imath_2_5_V2s__op_sub_1(
    Imath_2_5_V2s const * this_);


Imath_2_5_V2s const * Imath_2_5_V2s_negate(
    Imath_2_5_V2s * this_);


Imath_2_5_V2s const * Imath_2_5_V2s__op_imul(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s const * Imath_2_5_V2s__op_imul_1(
    Imath_2_5_V2s * this_
    , short a);


Imath_2_5_V2s Imath_2_5_V2s__op_mul(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s Imath_2_5_V2s__op_mul_1(
    Imath_2_5_V2s const * this_
    , short a);


Imath_2_5_V2s const * Imath_2_5_V2s__op_idiv(
    Imath_2_5_V2s * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s const * Imath_2_5_V2s__op_idiv_1(
    Imath_2_5_V2s * this_
    , short a);


Imath_2_5_V2s Imath_2_5_V2s__op_div(
    Imath_2_5_V2s const * this_
    , Imath_2_5_V2s const * v);


Imath_2_5_V2s Imath_2_5_V2s__op_div_1(
    Imath_2_5_V2s const * this_
    , short a);


short Imath_2_5_V2s_length(
    Imath_2_5_V2s const * this_);


short Imath_2_5_V2s_length2(
    Imath_2_5_V2s const * this_);


Imath_2_5_V2s const * Imath_2_5_V2s_normalize(
    Imath_2_5_V2s * this_);


Imath_2_5_V2s const * Imath_2_5_V2s_normalizeExc(
    Imath_2_5_V2s * this_);


Imath_2_5_V2s const * Imath_2_5_V2s_normalizeNonNull(
    Imath_2_5_V2s * this_);


Imath_2_5_V2s Imath_2_5_V2s_normalized(
    Imath_2_5_V2s const * this_);


Imath_2_5_V2s Imath_2_5_V2s_normalizedExc(
    Imath_2_5_V2s const * this_);


Imath_2_5_V2s Imath_2_5_V2s_normalizedNonNull(
    Imath_2_5_V2s const * this_);











int * Imath_2_5_V2i__index(
    Imath_2_5_V2i * this_
    , int i);


int const * Imath_2_5_V2i__index_1(
    Imath_2_5_V2i const * this_
    , int i);


void Imath_2_5_V2i_Vec2(
    Imath_2_5_V2i * this_);


void Imath_2_5_V2i_Vec2_1(
    Imath_2_5_V2i * this_
    , int a);


void Imath_2_5_V2i_Vec2_2(
    Imath_2_5_V2i * this_
    , int a
    , int b);


void Imath_2_5_V2i_Vec2_3(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i const * Imath_2_5_V2i__assign(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v);


void Imath_2_5_V2i_dtor(
    Imath_2_5_V2i * this_);


int * Imath_2_5_V2i_getValue(
    Imath_2_5_V2i * this_);


int const * Imath_2_5_V2i_getValue_1(
    Imath_2_5_V2i const * this_);


_Bool Imath_2_5_V2i_equalWithAbsError(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v
    , int e);


_Bool Imath_2_5_V2i_equalWithRelError(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v
    , int e);


int Imath_2_5_V2i_dot(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v);


int Imath_2_5_V2i_operator^(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v);


int Imath_2_5_V2i_cross(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v);


int Imath_2_5_V2i_operator%(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i const * Imath_2_5_V2i__op_iadd(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i Imath_2_5_V2i__op_add(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i const * Imath_2_5_V2i__op_isub(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i Imath_2_5_V2i__op_sub(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i Imath_2_5_V2i__op_sub_1(
    Imath_2_5_V2i const * this_);


Imath_2_5_V2i const * Imath_2_5_V2i_negate(
    Imath_2_5_V2i * this_);


Imath_2_5_V2i const * Imath_2_5_V2i__op_imul(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i const * Imath_2_5_V2i__op_imul_1(
    Imath_2_5_V2i * this_
    , int a);


Imath_2_5_V2i Imath_2_5_V2i__op_mul(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i Imath_2_5_V2i__op_mul_1(
    Imath_2_5_V2i const * this_
    , int a);


Imath_2_5_V2i const * Imath_2_5_V2i__op_idiv(
    Imath_2_5_V2i * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i const * Imath_2_5_V2i__op_idiv_1(
    Imath_2_5_V2i * this_
    , int a);


Imath_2_5_V2i Imath_2_5_V2i__op_div(
    Imath_2_5_V2i const * this_
    , Imath_2_5_V2i const * v);


Imath_2_5_V2i Imath_2_5_V2i__op_div_1(
    Imath_2_5_V2i const * this_
    , int a);


int Imath_2_5_V2i_length(
    Imath_2_5_V2i const * this_);


int Imath_2_5_V2i_length2(
    Imath_2_5_V2i const * this_);


Imath_2_5_V2i const * Imath_2_5_V2i_normalize(
    Imath_2_5_V2i * this_);


Imath_2_5_V2i const * Imath_2_5_V2i_normalizeExc(
    Imath_2_5_V2i * this_);


Imath_2_5_V2i const * Imath_2_5_V2i_normalizeNonNull(
    Imath_2_5_V2i * this_);


Imath_2_5_V2i Imath_2_5_V2i_normalized(
    Imath_2_5_V2i const * this_);


Imath_2_5_V2i Imath_2_5_V2i_normalizedExc(
    Imath_2_5_V2i const * this_);


Imath_2_5_V2i Imath_2_5_V2i_normalizedNonNull(
    Imath_2_5_V2i const * this_);











float * Imath_2_5_V2f__index(
    Imath_2_5_V2f * this_
    , int i);


float const * Imath_2_5_V2f__index_1(
    Imath_2_5_V2f const * this_
    , int i);


void Imath_2_5_V2f_Vec2(
    Imath_2_5_V2f * this_);


void Imath_2_5_V2f_Vec2_1(
    Imath_2_5_V2f * this_
    , float a);


void Imath_2_5_V2f_Vec2_2(
    Imath_2_5_V2f * this_
    , float a
    , float b);


void Imath_2_5_V2f_Vec2_3(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f const * Imath_2_5_V2f__assign(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v);


void Imath_2_5_V2f_dtor(
    Imath_2_5_V2f * this_);


float * Imath_2_5_V2f_getValue(
    Imath_2_5_V2f * this_);


float const * Imath_2_5_V2f_getValue_1(
    Imath_2_5_V2f const * this_);


_Bool Imath_2_5_V2f_equalWithAbsError(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v
    , float e);


_Bool Imath_2_5_V2f_equalWithRelError(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v
    , float e);


float Imath_2_5_V2f_dot(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v);


float Imath_2_5_V2f_operator^(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v);


float Imath_2_5_V2f_cross(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v);


float Imath_2_5_V2f_operator%(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f const * Imath_2_5_V2f__op_iadd(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f Imath_2_5_V2f__op_add(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f const * Imath_2_5_V2f__op_isub(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f Imath_2_5_V2f__op_sub(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f Imath_2_5_V2f__op_sub_1(
    Imath_2_5_V2f const * this_);


Imath_2_5_V2f const * Imath_2_5_V2f_negate(
    Imath_2_5_V2f * this_);


Imath_2_5_V2f const * Imath_2_5_V2f__op_imul(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f const * Imath_2_5_V2f__op_imul_1(
    Imath_2_5_V2f * this_
    , float a);


Imath_2_5_V2f Imath_2_5_V2f__op_mul(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f Imath_2_5_V2f__op_mul_1(
    Imath_2_5_V2f const * this_
    , float a);


Imath_2_5_V2f const * Imath_2_5_V2f__op_idiv(
    Imath_2_5_V2f * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f const * Imath_2_5_V2f__op_idiv_1(
    Imath_2_5_V2f * this_
    , float a);


Imath_2_5_V2f Imath_2_5_V2f__op_div(
    Imath_2_5_V2f const * this_
    , Imath_2_5_V2f const * v);


Imath_2_5_V2f Imath_2_5_V2f__op_div_1(
    Imath_2_5_V2f const * this_
    , float a);


float Imath_2_5_V2f_length(
    Imath_2_5_V2f const * this_);


float Imath_2_5_V2f_length2(
    Imath_2_5_V2f const * this_);


Imath_2_5_V2f const * Imath_2_5_V2f_normalize(
    Imath_2_5_V2f * this_);


Imath_2_5_V2f const * Imath_2_5_V2f_normalizeExc(
    Imath_2_5_V2f * this_);


Imath_2_5_V2f const * Imath_2_5_V2f_normalizeNonNull(
    Imath_2_5_V2f * this_);


Imath_2_5_V2f Imath_2_5_V2f_normalized(
    Imath_2_5_V2f const * this_);


Imath_2_5_V2f Imath_2_5_V2f_normalizedExc(
    Imath_2_5_V2f const * this_);


Imath_2_5_V2f Imath_2_5_V2f_normalizedNonNull(
    Imath_2_5_V2f const * this_);











double * Imath_2_5_V2d__index(
    Imath_2_5_V2d * this_
    , int i);


double const * Imath_2_5_V2d__index_1(
    Imath_2_5_V2d const * this_
    , int i);


void Imath_2_5_V2d_Vec2(
    Imath_2_5_V2d * this_);


void Imath_2_5_V2d_Vec2_1(
    Imath_2_5_V2d * this_
    , double a);


void Imath_2_5_V2d_Vec2_2(
    Imath_2_5_V2d * this_
    , double a
    , double b);


void Imath_2_5_V2d_Vec2_3(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d const * Imath_2_5_V2d__assign(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v);


void Imath_2_5_V2d_dtor(
    Imath_2_5_V2d * this_);


double * Imath_2_5_V2d_getValue(
    Imath_2_5_V2d * this_);


double const * Imath_2_5_V2d_getValue_1(
    Imath_2_5_V2d const * this_);


_Bool Imath_2_5_V2d_equalWithAbsError(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v
    , double e);


_Bool Imath_2_5_V2d_equalWithRelError(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v
    , double e);


double Imath_2_5_V2d_dot(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v);


double Imath_2_5_V2d_operator^(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v);


double Imath_2_5_V2d_cross(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v);


double Imath_2_5_V2d_operator%(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d const * Imath_2_5_V2d__op_iadd(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d Imath_2_5_V2d__op_add(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d const * Imath_2_5_V2d__op_isub(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d Imath_2_5_V2d__op_sub(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d Imath_2_5_V2d__op_sub_1(
    Imath_2_5_V2d const * this_);


Imath_2_5_V2d const * Imath_2_5_V2d_negate(
    Imath_2_5_V2d * this_);


Imath_2_5_V2d const * Imath_2_5_V2d__op_imul(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d const * Imath_2_5_V2d__op_imul_1(
    Imath_2_5_V2d * this_
    , double a);


Imath_2_5_V2d Imath_2_5_V2d__op_mul(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d Imath_2_5_V2d__op_mul_1(
    Imath_2_5_V2d const * this_
    , double a);


Imath_2_5_V2d const * Imath_2_5_V2d__op_idiv(
    Imath_2_5_V2d * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d const * Imath_2_5_V2d__op_idiv_1(
    Imath_2_5_V2d * this_
    , double a);


Imath_2_5_V2d Imath_2_5_V2d__op_div(
    Imath_2_5_V2d const * this_
    , Imath_2_5_V2d const * v);


Imath_2_5_V2d Imath_2_5_V2d__op_div_1(
    Imath_2_5_V2d const * this_
    , double a);


double Imath_2_5_V2d_length(
    Imath_2_5_V2d const * this_);


double Imath_2_5_V2d_length2(
    Imath_2_5_V2d const * this_);


Imath_2_5_V2d const * Imath_2_5_V2d_normalize(
    Imath_2_5_V2d * this_);


Imath_2_5_V2d const * Imath_2_5_V2d_normalizeExc(
    Imath_2_5_V2d * this_);


Imath_2_5_V2d const * Imath_2_5_V2d_normalizeNonNull(
    Imath_2_5_V2d * this_);


Imath_2_5_V2d Imath_2_5_V2d_normalized(
    Imath_2_5_V2d const * this_);


Imath_2_5_V2d Imath_2_5_V2d_normalizedExc(
    Imath_2_5_V2d const * this_);


Imath_2_5_V2d Imath_2_5_V2d_normalizedNonNull(
    Imath_2_5_V2d const * this_);











void Imath_2_5_V3s_Vec3(
    Imath_2_5_V3s * this_);


void Imath_2_5_V3s_Vec3_1(
    Imath_2_5_V3s * this_
    , Imath_2_5_V3s const * v);











void Imath_2_5_V3i_Vec3(
    Imath_2_5_V3i * this_);


void Imath_2_5_V3i_Vec3_1(
    Imath_2_5_V3i * this_
    , Imath_2_5_V3i const * v);











void Imath_2_5_V3f_Vec3(
    Imath_2_5_V3f * this_);


void Imath_2_5_V3f_Vec3_1(
    Imath_2_5_V3f * this_
    , Imath_2_5_V3f const * v);











void Imath_2_5_V3d_Vec3(
    Imath_2_5_V3d * this_);


void Imath_2_5_V3d_Vec3_1(
    Imath_2_5_V3d * this_
    , Imath_2_5_V3d const * v);











void Imath_2_5_V4s_Vec4(
    Imath_2_5_V4s * this_);


void Imath_2_5_V4s_Vec4_1(
    Imath_2_5_V4s * this_
    , Imath_2_5_V4s const * v);











void Imath_2_5_V4i_Vec4(
    Imath_2_5_V4i * this_);


void Imath_2_5_V4i_Vec4_1(
    Imath_2_5_V4i * this_
    , Imath_2_5_V4i const * v);











void Imath_2_5_V4f_Vec4(
    Imath_2_5_V4f * this_);


void Imath_2_5_V4f_Vec4_1(
    Imath_2_5_V4f * this_
    , Imath_2_5_V4f const * v);











void Imath_2_5_V4d_Vec4(
    Imath_2_5_V4d * this_);


void Imath_2_5_V4d_Vec4_1(
    Imath_2_5_V4d * this_
    , Imath_2_5_V4d const * v);









#ifdef __cplusplus
}
#endif
