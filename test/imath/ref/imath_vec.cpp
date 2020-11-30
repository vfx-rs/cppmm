//
#include "imath_vec.h"
#include <Imath/ImathVec.h>



namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(Imath_3_0::Vec3<float>, Imath_3_0_V3f)
CPPMM_DEFINE_POINTER_CASTS(Imath_3_0::Vec3<int>, Imath_3_0_V3i)

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {
static_assert(sizeof(Imath_3_0::Vec3<int>) == sizeof(Imath_3_0_V3i), "sizes do not match");
static_assert(alignof(Imath_3_0::Vec3<int>) == alignof(Imath_3_0_V3i), "alignments do not match");
static_assert(offsetof(Imath_3_0::Vec3<int>, x) == offsetof(Imath_3_0_V3i, x), "field offset does not match");
static_assert(offsetof(Imath_3_0::Vec3<int>, y) == offsetof(Imath_3_0_V3i, y), "field offset does not match");
static_assert(offsetof(Imath_3_0::Vec3<int>, z) == offsetof(Imath_3_0_V3i, z), "field offset does not match");

static_assert(sizeof(Imath_3_0::Vec3<float>) == sizeof(Imath_3_0_V3f), "sizes do not match");
static_assert(alignof(Imath_3_0::Vec3<float>) == alignof(Imath_3_0_V3f), "alignments do not match");
static_assert(offsetof(Imath_3_0::Vec3<float>, x) == offsetof(Imath_3_0_V3f, x), "field offset does not match");
static_assert(offsetof(Imath_3_0::Vec3<float>, y) == offsetof(Imath_3_0_V3f, y), "field offset does not match");
static_assert(offsetof(Imath_3_0::Vec3<float>, z) == offsetof(Imath_3_0_V3f, z), "field offset does not match");


int Imath_3_0_V3i_baseTypeEpsilon() {
    return Imath_3_0::Vec3<int>::baseTypeEpsilon();
}



int Imath_3_0_V3i_baseTypeSmallest() {
    return Imath_3_0::Vec3<int>::baseTypeSmallest();
}



int Imath_3_0_V3i_baseTypeMax() {
    return Imath_3_0::Vec3<int>::baseTypeMax();
}



Imath_3_0_V3i Imath_3_0_V3i_op_add(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    return bit_cast<Imath_3_0_V3i>(*to_cpp(self) + *to_cpp(v));
}



int Imath_3_0_V3i_dot(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    return to_cpp(self)->dot(*to_cpp(v));
}



Imath_3_0_V3i Imath_3_0_V3i_div_t(const Imath_3_0_V3i* self, int a) {
    return bit_cast<Imath_3_0_V3i>(*to_cpp(self) / a);
}



Imath_3_0_V3i Imath_3_0_V3i_cross(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    return bit_cast<Imath_3_0_V3i>(to_cpp(self)->cross(*to_cpp(v)));
}



int Imath_3_0_V3i_length2(const Imath_3_0_V3i* self) {
    return to_cpp(self)->length2();
}



bool Imath_3_0_V3i_equalWithAbsError(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v, int e) {
    return to_cpp(self)->equalWithAbsError(*to_cpp(v), e);
}



const Imath_3_0_V3i* Imath_3_0_V3i_op_add_assign(Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    *to_cpp(self) += *to_cpp(v);
    return self;
}



bool Imath_3_0_V3i_equalWithRelError(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v, int e) {
    return to_cpp(self)->equalWithRelError(*to_cpp(v), e);
}



Imath_3_0_V3i Imath_3_0_V3i_normalized(const Imath_3_0_V3i* self) {
    return bit_cast<Imath_3_0_V3i>(to_cpp(self)->normalized());
}



Imath_3_0_V3i Imath_3_0_V3i_op_div(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    return bit_cast<Imath_3_0_V3i>(*to_cpp(self) / *to_cpp(v));
}



const Imath_3_0_V3i* Imath_3_0_V3i_op_sub_assign(Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    *to_cpp(self) -= *to_cpp(v);
    return self;
}



Imath_3_0_V3i Imath_3_0_V3i_op_sub(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    return bit_cast<Imath_3_0_V3i>(*to_cpp(self) - *to_cpp(v));
}



Imath_3_0_V3i Imath_3_0_V3i_op_neg(const Imath_3_0_V3i* self) {
    return bit_cast<Imath_3_0_V3i>(-(*to_cpp(self)));
}



const Imath_3_0_V3i* Imath_3_0_V3i_op_div_assign(Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    *to_cpp(self) /= *to_cpp(v);
    return self;
}



int Imath_3_0_V3i_baseTypeMin() {
    return Imath_3_0::Vec3<int>::baseTypeMin();
}



unsigned int Imath_3_0_V3i_dimensions() {
    return Imath_3_0::Vec3<int>::dimensions();
}



int Imath_3_0_V3i_length(const Imath_3_0_V3i* self) {
    return to_cpp(self)->length();
}



const Imath_3_0_V3i* Imath_3_0_V3i_op_mul_assign(Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    *to_cpp(self) *= *to_cpp(v);
    return self;
}



const Imath_3_0_V3i* Imath_3_0_V3i_mul_assign_t(Imath_3_0_V3i* self, int a) {
    *to_cpp(self) *= a;
    return self;
}



Imath_3_0_V3i Imath_3_0_V3i_op_mul(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v) {
    return bit_cast<Imath_3_0_V3i>(*to_cpp(self) * *to_cpp(v));
}



const Imath_3_0_V3i* Imath_3_0_V3i_normalize(Imath_3_0_V3i* self) {
    return bit_cast<Imath_3_0_V3i>(to_cpp(self)->normalize());
}



Imath_3_0_V3i Imath_3_0_V3i_mul_t(const Imath_3_0_V3i* self, int a) {
    return bit_cast<Imath_3_0_V3i>(*to_cpp(self) * a);
}



const Imath_3_0_V3i* Imath_3_0_V3i_div_assign_t(Imath_3_0_V3i* self, int a) {
    *to_cpp(self) /= a;
    return self;
}



float Imath_3_0_V3f_baseTypeEpsilon() {
    return Imath_3_0::Vec3<float>::baseTypeEpsilon();
}



float Imath_3_0_V3f_baseTypeSmallest() {
    return Imath_3_0::Vec3<float>::baseTypeSmallest();
}



float Imath_3_0_V3f_baseTypeMax() {
    return Imath_3_0::Vec3<float>::baseTypeMax();
}



Imath_3_0_V3f Imath_3_0_V3f_op_add(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    return bit_cast<Imath_3_0_V3f>(*to_cpp(self) + *to_cpp(v));
}



float Imath_3_0_V3f_dot(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    return to_cpp(self)->dot(*to_cpp(v));
}



Imath_3_0_V3f Imath_3_0_V3f_div_t(const Imath_3_0_V3f* self, float a) {
    return bit_cast<Imath_3_0_V3f>(*to_cpp(self) / a);
}



Imath_3_0_V3f Imath_3_0_V3f_cross(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    return bit_cast<Imath_3_0_V3f>(to_cpp(self)->cross(*to_cpp(v)));
}



float Imath_3_0_V3f_length2(const Imath_3_0_V3f* self) {
    return to_cpp(self)->length2();
}



bool Imath_3_0_V3f_equalWithAbsError(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v, float e) {
    return to_cpp(self)->equalWithAbsError(*to_cpp(v), e);
}



const Imath_3_0_V3f* Imath_3_0_V3f_op_add_assign(Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    *to_cpp(self) += *to_cpp(v);
    return self;
}



bool Imath_3_0_V3f_equalWithRelError(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v, float e) {
    return to_cpp(self)->equalWithRelError(*to_cpp(v), e);
}



Imath_3_0_V3f Imath_3_0_V3f_normalized(const Imath_3_0_V3f* self) {
    return bit_cast<Imath_3_0_V3f>(to_cpp(self)->normalized());
}



Imath_3_0_V3f Imath_3_0_V3f_op_div(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    return bit_cast<Imath_3_0_V3f>(*to_cpp(self) / *to_cpp(v));
}



const Imath_3_0_V3f* Imath_3_0_V3f_op_sub_assign(Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    *to_cpp(self) -= *to_cpp(v);
    return self;
}



Imath_3_0_V3f Imath_3_0_V3f_op_sub(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    return bit_cast<Imath_3_0_V3f>(*to_cpp(self) - *to_cpp(v));
}



Imath_3_0_V3f Imath_3_0_V3f_op_neg(const Imath_3_0_V3f* self) {
    return bit_cast<Imath_3_0_V3f>(-(*to_cpp(self)));
}



const Imath_3_0_V3f* Imath_3_0_V3f_op_div_assign(Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    *to_cpp(self) /= *to_cpp(v);
    return self;
}



float Imath_3_0_V3f_baseTypeMin() {
    return Imath_3_0::Vec3<float>::baseTypeMin();
}



unsigned int Imath_3_0_V3f_dimensions() {
    return Imath_3_0::Vec3<float>::dimensions();
}



float Imath_3_0_V3f_length(const Imath_3_0_V3f* self) {
    return to_cpp(self)->length();
}



const Imath_3_0_V3f* Imath_3_0_V3f_op_mul_assign(Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    *to_cpp(self) *= *to_cpp(v);
    return self;
}



const Imath_3_0_V3f* Imath_3_0_V3f_mul_assign_t(Imath_3_0_V3f* self, float a) {
    *to_cpp(self) *= a;
    return self;
}



Imath_3_0_V3f Imath_3_0_V3f_op_mul(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v) {
    return bit_cast<Imath_3_0_V3f>(*to_cpp(self) * *to_cpp(v));
}



const Imath_3_0_V3f* Imath_3_0_V3f_normalize(Imath_3_0_V3f* self) {
    return bit_cast<Imath_3_0_V3f>(to_cpp(self)->normalize());
}



Imath_3_0_V3f Imath_3_0_V3f_mul_t(const Imath_3_0_V3f* self, float a) {
    return bit_cast<Imath_3_0_V3f>(*to_cpp(self) * a);
}



const Imath_3_0_V3f* Imath_3_0_V3f_div_assign_t(Imath_3_0_V3f* self, float a) {
    *to_cpp(self) /= a;
    return self;
}



}
    