#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imath_2_5_half_s {
    char data[2];
} __attribute__((aligned(2))) Imath_2_5_half;


void Imath_2_5_half_half(
    Imath_2_5_half * this_);


void Imath_2_5_half_half_1(
    Imath_2_5_half * this_
    , float f);


void Imath_2_5_half_dtor(
    Imath_2_5_half * this_);


void Imath_2_5_half_half_2(
    Imath_2_5_half * this_
    , Imath_2_5_half const * rhs);


void Imath_2_5_half_half_3(
    Imath_2_5_half * this_
    , Imath_2_5_half * );


float Imath_2_5_half_operatorfloat(
    Imath_2_5_half const * this_);


Imath_2_5_half Imath_2_5_half__op_sub(
    Imath_2_5_half const * this_);


Imath_2_5_half * Imath_2_5_half__assign(
    Imath_2_5_half * this_
    , Imath_2_5_half const * h);


Imath_2_5_half * Imath_2_5_half__assign_1(
    Imath_2_5_half * this_
    , Imath_2_5_half * h);


Imath_2_5_half * Imath_2_5_half__assign_2(
    Imath_2_5_half * this_
    , float f);


Imath_2_5_half * Imath_2_5_half__op_iadd(
    Imath_2_5_half * this_
    , Imath_2_5_half h);


Imath_2_5_half * Imath_2_5_half__op_iadd_1(
    Imath_2_5_half * this_
    , float f);


Imath_2_5_half * Imath_2_5_half__op_isub(
    Imath_2_5_half * this_
    , Imath_2_5_half h);


Imath_2_5_half * Imath_2_5_half__op_isub_1(
    Imath_2_5_half * this_
    , float f);


Imath_2_5_half * Imath_2_5_half__op_imul(
    Imath_2_5_half * this_
    , Imath_2_5_half h);


Imath_2_5_half * Imath_2_5_half__op_imul_1(
    Imath_2_5_half * this_
    , float f);


Imath_2_5_half * Imath_2_5_half__op_idiv(
    Imath_2_5_half * this_
    , Imath_2_5_half h);


Imath_2_5_half * Imath_2_5_half__op_idiv_1(
    Imath_2_5_half * this_
    , float f);


Imath_2_5_half Imath_2_5_half_round(
    Imath_2_5_half const * this_
    , unsigned int n);


_Bool Imath_2_5_half_isFinite(
    Imath_2_5_half const * this_);


_Bool Imath_2_5_half_isNormalized(
    Imath_2_5_half const * this_);


_Bool Imath_2_5_half_isDenormalized(
    Imath_2_5_half const * this_);


_Bool Imath_2_5_half_isZero(
    Imath_2_5_half const * this_);


_Bool Imath_2_5_half_isNan(
    Imath_2_5_half const * this_);


_Bool Imath_2_5_half_isInfinity(
    Imath_2_5_half const * this_);


_Bool Imath_2_5_half_isNegative(
    Imath_2_5_half const * this_);


unsigned short Imath_2_5_half_bits(
    Imath_2_5_half const * this_);


void Imath_2_5_half_setBits(
    Imath_2_5_half * this_
    , unsigned short bits);









#ifdef __cplusplus
}
#endif
