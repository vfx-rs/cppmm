#pragma once



#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#define CPPMM_ALIGN(x) __declspec(align(x))
#else
#define CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif

typedef struct { char _private[2]; } Imath_3_0_half CPPMM_ALIGN(2);


void Imath_3_0_half_setBits(Imath_3_0_half* self, unsigned short bits);


Imath_3_0_half Imath_3_0_half_sNan();


Imath_3_0_half Imath_3_0_half_qNan();


Imath_3_0_half Imath_3_0_half_posInf();


bool Imath_3_0_half_isDenormalized(const Imath_3_0_half* self);


bool Imath_3_0_half_isNormalized(const Imath_3_0_half* self);


void Imath_3_0_half_copy(Imath_3_0_half* self, const Imath_3_0_half* other);


void Imath_3_0_half_dtor(Imath_3_0_half* self);


Imath_3_0_half Imath_3_0_half_negInf();


Imath_3_0_half Imath_3_0_half_neg(const Imath_3_0_half* self);


Imath_3_0_half Imath_3_0_half_round(const Imath_3_0_half* self, unsigned int n);


unsigned short Imath_3_0_half_bits(const Imath_3_0_half* self);


bool Imath_3_0_half_isNegative(const Imath_3_0_half* self);


bool Imath_3_0_half_isInfinity(const Imath_3_0_half* self);


Imath_3_0_half* Imath_3_0_half_assign(Imath_3_0_half* self, const Imath_3_0_half* other);


Imath_3_0_half* Imath_3_0_half_mul_assign_float(Imath_3_0_half* self, float f);


Imath_3_0_half* Imath_3_0_half_add_assign(Imath_3_0_half* self, Imath_3_0_half h);


bool Imath_3_0_half_isNan(const Imath_3_0_half* self);


bool Imath_3_0_half_isZero(const Imath_3_0_half* self);


float Imath_3_0_half_to_float(const Imath_3_0_half* self);


void Imath_3_0_half_ctor(Imath_3_0_half* self);


Imath_3_0_half* Imath_3_0_half_add_assign_float(Imath_3_0_half* self, float f);


Imath_3_0_half* Imath_3_0_half_div_assign(Imath_3_0_half* self, Imath_3_0_half h);


bool Imath_3_0_half_isFinite(const Imath_3_0_half* self);


Imath_3_0_half* Imath_3_0_half_sub_assign(Imath_3_0_half* self, Imath_3_0_half h);


void Imath_3_0_half_from_float(Imath_3_0_half* self, float f);


Imath_3_0_half* Imath_3_0_half_mul_assign(Imath_3_0_half* self, Imath_3_0_half h);


Imath_3_0_half* Imath_3_0_half_sub_assign_float(Imath_3_0_half* self, float f);


Imath_3_0_half* Imath_3_0_half_div_assign_float(Imath_3_0_half* self, float f);


#undef CPPMM_ALIGN

#ifdef __cplusplus
}
#endif
    