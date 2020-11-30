//
#include "containers_bind.h"
#include "containers.hpp"



namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(containers::Containers, containers_Containers)
CPPMM_DEFINE_POINTER_CASTS(containers::CustomElement, containers_CustomElement)
CPPMM_DEFINE_POINTER_CASTS(containers::CustomOB, containers_CustomOB)
CPPMM_DEFINE_POINTER_CASTS(containers::CustomOP, containers_CustomOP)
CPPMM_DEFINE_POINTER_CASTS(containers::CustomVT, containers_CustomVT)
CPPMM_DEFINE_POINTER_CASTS(std::vector<containers::CustomElement>, containers_CustomElement_vector);
CPPMM_DEFINE_POINTER_CASTS(std::vector<std::string>, cppmm_string_vector);

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {

void containers_CustomElement_vector_ctor(containers_CustomElement_vector* vec) {
    new (vec) std::vector<containers::CustomElement>();
}

void containers_CustomElement_vector_dtor(const containers_CustomElement_vector* vec) {
    to_cpp(vec)->~vector();
}

int containers_CustomElement_vector_size(const containers_CustomElement_vector* vec) {
    return to_cpp(vec)->size();
}

containers_CustomElement* containers_CustomElement_vector_data(containers_CustomElement_vector* vec) {
    return to_c(to_cpp(vec)->data());
}

void containers_CustomElement_vector_get(const containers_CustomElement_vector* vec, int index, containers_CustomElement* element) {
    const std::vector<containers::CustomElement>& v = *to_cpp(vec);
    const containers::CustomElement* p = &v[index];
    *element = *to_c(p);
}

void containers_CustomElement_vector_set(containers_CustomElement_vector* vec, int index, containers_CustomElement* element) {
    (*to_cpp(vec))[index] = *to_cpp(element);
}
static_assert(sizeof(containers::CustomElement) == sizeof(containers_CustomElement), "sizes do not match");
static_assert(alignof(containers::CustomElement) == alignof(containers_CustomElement), "alignments do not match");
static_assert(sizeof(containers::CustomVT) == sizeof(containers_CustomVT), "sizes do not match");
static_assert(alignof(containers::CustomVT) == alignof(containers_CustomVT), "alignments do not match");
static_assert(offsetof(containers::CustomVT, a) == offsetof(containers_CustomVT, a), "field offset does not match");
static_assert(offsetof(containers::CustomVT, b) == offsetof(containers_CustomVT, b), "field offset does not match");

static_assert(sizeof(containers::CustomOB) == sizeof(containers_CustomOB), "sizes do not match");
static_assert(alignof(containers::CustomOB) == alignof(containers_CustomOB), "alignments do not match");

void containers_Containers_testint(containers_Containers* self, int a) {
    to_cpp(self)->testint(a);
}



void containers_Containers_takes_const_vec_custom_ref(containers_Containers* self, const containers_CustomElement_vector* vec) {
    to_cpp(self)->takes_const_vec_custom_ref(*to_cpp(vec));
}



void containers_Containers_takes_mut_vec_string_ref(cppmm_string_vector* vec) {
    containers::Containers::takes_mut_vec_string_ref(*to_cpp(vec));
}



void containers_Containers_takes_const_vec_string_ref(const cppmm_string_vector* vec) {
    containers::Containers::takes_const_vec_string_ref(*to_cpp(vec));
}



cppmm_string_vector containers_Containers_returns_vec_string() {
    std::vector<std::string> tmp = containers::Containers::returns_vec_string();
    cppmm_string_vector ret;
    new (&ret) std::vector<std::string>(std::move(tmp));
    return ret;
}



}
    