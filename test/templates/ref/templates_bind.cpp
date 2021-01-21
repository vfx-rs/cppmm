//
#include "templates_bind.h"
#include "templates.hpp"



namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(templates::Vector3<float>, templates_V3f)
CPPMM_DEFINE_POINTER_CASTS(templates::Vector3<int>, templates_V3i)

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {
static_assert(sizeof(templates::Vector3<int>) == sizeof(templates_V3i), "sizes do not match");
static_assert(alignof(templates::Vector3<int>) == alignof(templates_V3i), "alignments do not match");
static_assert(offsetof(templates::Vector3<int>, x) == offsetof(templates_V3i, x), "field offset does not match");
static_assert(offsetof(templates::Vector3<int>, y) == offsetof(templates_V3i, y), "field offset does not match");
static_assert(offsetof(templates::Vector3<int>, z) == offsetof(templates_V3i, z), "field offset does not match");

static_assert(sizeof(templates::Vector3<float>) == sizeof(templates_V3f), "sizes do not match");
static_assert(alignof(templates::Vector3<float>) == alignof(templates_V3f), "alignments do not match");
static_assert(offsetof(templates::Vector3<float>, x) == offsetof(templates_V3f, x), "field offset does not match");
static_assert(offsetof(templates::Vector3<float>, y) == offsetof(templates_V3f, y), "field offset does not match");
static_assert(offsetof(templates::Vector3<float>, z) == offsetof(templates_V3f, z), "field offset does not match");


void templates_takes_vector3_and_t(templates_V3i* v, float w) {
    templates::takes_vector3_and_t(*to_cpp(v), w);
}



void templates_takes_two_vector3(templates_V3i* v, templates_V3f* w) {
    templates::takes_two_vector3(*to_cpp(v), *to_cpp(w));
}



void templates_takes_vector3(templates_V3f* v) {
    templates::takes_vector3(*to_cpp(v));
}



void templates_takes_vector3(templates_V3i* v) {
    templates::takes_vector3(*to_cpp(v));
}



void templates_V3i_some_other(templates_V3i* self, int t) {
    to_cpp(self)->some_other(t);
}



int templates_V3i_length(const templates_V3i* self) {
    return to_cpp(self)->length();
}



void templates_V3f_some_other(templates_V3f* self, float t) {
    to_cpp(self)->some_other(t);
}



float templates_V3f_length(const templates_V3f* self) {
    return to_cpp(self)->length();
}



}
    