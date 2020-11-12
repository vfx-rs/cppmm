//
#include "half.h"
#include <Imath/half.h>

namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(Imath_3_0::half, Imath_3_0_half)

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {
static_assert(sizeof(Imath_3_0::half) == sizeof(Imath_3_0_half), "sizes do not match");
static_assert(alignof(Imath_3_0::half) == alignof(Imath_3_0_half), "alignments do not match");

void Imath_3_0_half_setBits(Imath_3_0_half* self, unsigned short bits) {
    to_cpp(self)->setBits(bits);
}



Imath_3_0_half Imath_3_0_half_sNan() {
    return bit_cast<Imath_3_0_half>(Imath_3_0::half::sNan());
}



Imath_3_0_half Imath_3_0_half_qNan() {
    return bit_cast<Imath_3_0_half>(Imath_3_0::half::qNan());
}



Imath_3_0_half Imath_3_0_half_posInf() {
    return bit_cast<Imath_3_0_half>(Imath_3_0::half::posInf());
}



bool Imath_3_0_half_isDenormalized(const Imath_3_0_half* self) {
    return to_cpp(self)->isDenormalized();
}



bool Imath_3_0_half_isNormalized(const Imath_3_0_half* self) {
    return to_cpp(self)->isNormalized();
}



void Imath_3_0_half_copy(Imath_3_0_half* self, const Imath_3_0_half* other) {
    self = to_c(new (self) Imath_3_0::half(*to_cpp(other)));
}



void Imath_3_0_half_dtor(Imath_3_0_half* self) {
    to_cpp(self)->~half();
}



Imath_3_0_half Imath_3_0_half_negInf() {
    return bit_cast<Imath_3_0_half>(Imath_3_0::half::negInf());
}



Imath_3_0_half Imath_3_0_half_neg(const Imath_3_0_half* self) {
    return bit_cast<Imath_3_0_half>(-(*to_cpp(self)));
}



Imath_3_0_half Imath_3_0_half_round(const Imath_3_0_half* self, unsigned int n) {
    return bit_cast<Imath_3_0_half>(to_cpp(self)->round(n));
}



unsigned short Imath_3_0_half_bits(const Imath_3_0_half* self) {
    return to_cpp(self)->bits();
}



bool Imath_3_0_half_isNegative(const Imath_3_0_half* self) {
    return to_cpp(self)->isNegative();
}



bool Imath_3_0_half_isInfinity(const Imath_3_0_half* self) {
    return to_cpp(self)->isInfinity();
}



Imath_3_0_half* Imath_3_0_half_assign(Imath_3_0_half* self, const Imath_3_0_half* other) {
    *to_cpp(self) = *to_cpp(other);
    return self;
}



Imath_3_0_half* Imath_3_0_half_mul_assign_float(Imath_3_0_half* self, float f) {
    *to_cpp(self) *= f;
    return self;
}



Imath_3_0_half* Imath_3_0_half_add_assign(Imath_3_0_half* self, Imath_3_0_half h) {
    *to_cpp(self) += bit_cast<Imath_3_0::half>(h);
    return self;
}



bool Imath_3_0_half_isNan(const Imath_3_0_half* self) {
    return to_cpp(self)->isNan();
}



bool Imath_3_0_half_isZero(const Imath_3_0_half* self) {
    return to_cpp(self)->isZero();
}



float Imath_3_0_half_to_float(const Imath_3_0_half* self) {
    return to_cpp(self)->operator float();
}



void Imath_3_0_half_ctor(Imath_3_0_half* self) {
    self = to_c(new (self) Imath_3_0::half());
}



Imath_3_0_half* Imath_3_0_half_add_assign_float(Imath_3_0_half* self, float f) {
    *to_cpp(self) += f;
    return self;
}



Imath_3_0_half* Imath_3_0_half_div_assign(Imath_3_0_half* self, Imath_3_0_half h) {
    *to_cpp(self) /= bit_cast<Imath_3_0::half>(h);
    return self;
}



bool Imath_3_0_half_isFinite(const Imath_3_0_half* self) {
    return to_cpp(self)->isFinite();
}



Imath_3_0_half* Imath_3_0_half_sub_assign(Imath_3_0_half* self, Imath_3_0_half h) {
    *to_cpp(self) -= bit_cast<Imath_3_0::half>(h);
    return self;
}



void Imath_3_0_half_from_float(Imath_3_0_half* self, float f) {
    self = to_c(new (self) Imath_3_0::half(f));
}



Imath_3_0_half* Imath_3_0_half_mul_assign(Imath_3_0_half* self, Imath_3_0_half h) {
    *to_cpp(self) *= bit_cast<Imath_3_0::half>(h);
    return self;
}



Imath_3_0_half* Imath_3_0_half_sub_assign_float(Imath_3_0_half* self, float f) {
    *to_cpp(self) -= f;
    return self;
}



Imath_3_0_half* Imath_3_0_half_div_assign_float(Imath_3_0_half* self, float f) {
    *to_cpp(self) /= f;
    return self;
}



}
    