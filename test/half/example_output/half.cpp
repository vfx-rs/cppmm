//
#include "half.h"
#include <Imath/half.h>

namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(Imath::half, Imath_half)

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {
static_assert(sizeof(Imath::half) == sizeof(Imath_half), "sizes do not match");
static_assert(alignof(Imath::half) == alignof(Imath_half), "alignments do not match");

void Imath_half_setBits(Imath_half* self, unsigned short bits) {
    to_cpp(self)->setBits(bits);
}



Imath_half Imath_half_sNan() {
    return bit_cast<Imath_half>(Imath::half::sNan());
}



Imath_half Imath_half_qNan() {
    return bit_cast<Imath_half>(Imath::half::qNan());
}



Imath_half Imath_half_posInf() {
    return bit_cast<Imath_half>(Imath::half::posInf());
}



bool Imath_half_isDenormalized(const Imath_half* self) {
    return to_cpp(self)->isDenormalized();
}



bool Imath_half_isNormalized(const Imath_half* self) {
    return to_cpp(self)->isNormalized();
}



void Imath_half_copy(Imath_half* self, const Imath_half* other) {
    self = to_c(new (self) Imath::half(*to_cpp(other)));
}



void Imath_half_dtor(Imath_half* self) {
    to_cpp(self)->~half();
}



Imath_half Imath_half_negInf() {
    return bit_cast<Imath_half>(Imath::half::negInf());
}



Imath_half Imath_half_neg(const Imath_half* self) {
    return bit_cast<Imath_half>(-(*to_cpp(self)));
}



Imath_half Imath_half_round(const Imath_half* self, unsigned int n) {
    return bit_cast<Imath_half>(to_cpp(self)->round(n));
}



unsigned short Imath_half_bits(const Imath_half* self) {
    return to_cpp(self)->bits();
}



bool Imath_half_isNegative(const Imath_half* self) {
    return to_cpp(self)->isNegative();
}



bool Imath_half_isInfinity(const Imath_half* self) {
    return to_cpp(self)->isInfinity();
}



Imath_half* Imath_half_assign(Imath_half* self, const Imath_half* other) {
    *to_cpp(self) = *to_cpp(other);
    return self;
}



Imath_half* Imath_half_mul_assign_float(Imath_half* self, float f) {
    *to_cpp(self) *= f;
    return self;
}



Imath_half* Imath_half_add_assign(Imath_half* self, Imath_half h) {
    *to_cpp(self) += bit_cast<Imath::half>(h);
    return self;
}



bool Imath_half_isNan(const Imath_half* self) {
    return to_cpp(self)->isNan();
}



bool Imath_half_isZero(const Imath_half* self) {
    return to_cpp(self)->isZero();
}



float Imath_half_to_float(const Imath_half* self) {
    return to_cpp(self)->operator float();
}



void Imath_half_ctor(Imath_half* self) {
    self = to_c(new (self) Imath::half());
}



Imath_half* Imath_half_add_assign_float(Imath_half* self, float f) {
    *to_cpp(self) += f;
    return self;
}



Imath_half* Imath_half_div_assign(Imath_half* self, Imath_half h) {
    *to_cpp(self) /= bit_cast<Imath::half>(h);
    return self;
}



bool Imath_half_isFinite(const Imath_half* self) {
    return to_cpp(self)->isFinite();
}



Imath_half* Imath_half_sub_assign(Imath_half* self, Imath_half h) {
    *to_cpp(self) -= bit_cast<Imath::half>(h);
    return self;
}



void Imath_half_from_float(Imath_half* self, float f) {
    self = to_c(new (self) Imath::half(f));
}



Imath_half* Imath_half_mul_assign(Imath_half* self, Imath_half h) {
    *to_cpp(self) *= bit_cast<Imath::half>(h);
    return self;
}



Imath_half* Imath_half_sub_assign_float(Imath_half* self, float f) {
    *to_cpp(self) -= f;
    return self;
}



Imath_half* Imath_half_div_assign_float(Imath_half* self, float f) {
    *to_cpp(self) /= f;
    return self;
}



}
    