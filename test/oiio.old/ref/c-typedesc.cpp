//
#include "c-typedesc.h"
#include <OpenImageIO/typedesc.h>



namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(OpenImageIO_v2_2::TypeDesc, OpenImageIO_v2_2_TypeDesc)
CPPMM_DEFINE_POINTER_CASTS(std::vector<OpenImageIO_v2_2::TypeDesc>, OpenImageIO_v2_2_TypeDesc_vector);

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {

void OpenImageIO_v2_2_TypeDesc_vector_ctor(OpenImageIO_v2_2_TypeDesc_vector* vec) {
    new (vec) std::vector<OpenImageIO_v2_2::TypeDesc>();
}

void OpenImageIO_v2_2_TypeDesc_vector_dtor(const OpenImageIO_v2_2_TypeDesc_vector* vec) {
    to_cpp(vec)->~vector();
}

int OpenImageIO_v2_2_TypeDesc_vector_size(const OpenImageIO_v2_2_TypeDesc_vector* vec) {
    return to_cpp(vec)->size();
}

OpenImageIO_v2_2_TypeDesc* OpenImageIO_v2_2_TypeDesc_vector_data(OpenImageIO_v2_2_TypeDesc_vector* vec) {
    return to_c(to_cpp(vec)->data());
}

void OpenImageIO_v2_2_TypeDesc_vector_get(const OpenImageIO_v2_2_TypeDesc_vector* vec, int index, OpenImageIO_v2_2_TypeDesc* element) {
    const std::vector<OpenImageIO_v2_2::TypeDesc>& v = *to_cpp(vec);
    const OpenImageIO_v2_2::TypeDesc* p = &v[index];
    *element = *to_c(p);
}

void OpenImageIO_v2_2_TypeDesc_vector_set(OpenImageIO_v2_2_TypeDesc_vector* vec, int index, OpenImageIO_v2_2_TypeDesc* element) {
    (*to_cpp(vec))[index] = *to_cpp(element);
}
static_assert(sizeof(OpenImageIO_v2_2::TypeDesc) == sizeof(OpenImageIO_v2_2_TypeDesc), "sizes do not match");
static_assert(alignof(OpenImageIO_v2_2::TypeDesc) == alignof(OpenImageIO_v2_2_TypeDesc), "alignments do not match");
static_assert(offsetof(OpenImageIO_v2_2::TypeDesc, basetype) == offsetof(OpenImageIO_v2_2_TypeDesc, basetype), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::TypeDesc, aggregate) == offsetof(OpenImageIO_v2_2_TypeDesc, aggregate), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::TypeDesc, vecsemantics) == offsetof(OpenImageIO_v2_2_TypeDesc, vecsemantics), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::TypeDesc, reserved) == offsetof(OpenImageIO_v2_2_TypeDesc, reserved), "field offset does not match");
static_assert(offsetof(OpenImageIO_v2_2::TypeDesc, arraylen) == offsetof(OpenImageIO_v2_2_TypeDesc, arraylen), "field offset does not match");


}
    