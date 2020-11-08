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

typedef struct { char _private[2]; } Imath_half CPPMM_ALIGN(2);


void  Imath_half_setBits(Imath_half* self, unsigned short bits);


Imath_half  Imath_half_sNan();


Imath_half  Imath_half_qNan();


Imath_half  Imath_half_posInf();


bool  Imath_half_isDenormalized(const Imath_half* self);


bool  Imath_half_isNormalized(const Imath_half* self);


void  Imath_half_copy(Imath_half* self, const Imath_half* other);


void  Imath_half_dtor(Imath_half* self);


Imath_half  Imath_half_negInf();


Imath_half  Imath_half_neg(const Imath_half* self);


Imath_half  Imath_half_round(const Imath_half* self, unsigned int n);


unsigned short  Imath_half_bits(const Imath_half* self);


bool  Imath_half_isNegative(const Imath_half* self);


bool  Imath_half_isInfinity(const Imath_half* self);


Imath_half*  Imath_half_assign(Imath_half* self, const Imath_half* other);


Imath_half*  Imath_half_mul_assign_float(Imath_half* self, float f);


Imath_half*  Imath_half_add_assign(Imath_half* self, Imath_half h);


bool  Imath_half_isNan(const Imath_half* self);


bool  Imath_half_isZero(const Imath_half* self);


float  Imath_half_to_float(const Imath_half* self);


void  Imath_half_ctor(Imath_half* self);


Imath_half*  Imath_half_add_assign_float(Imath_half* self, float f);


Imath_half*  Imath_half_div_assign(Imath_half* self, Imath_half h);


bool  Imath_half_isFinite(const Imath_half* self);


Imath_half*  Imath_half_sub_assign(Imath_half* self, Imath_half h);


void  Imath_half_from_float(Imath_half* self, float f);


Imath_half*  Imath_half_mul_assign(Imath_half* self, Imath_half h);


Imath_half*  Imath_half_sub_assign_float(Imath_half* self, float f);


Imath_half*  Imath_half_div_assign_float(Imath_half* self, float f);


#undef CPPMM_ALIGN

#ifdef __cplusplus
}
#endif
    