//
#include "c-typedesc.h"
#include <OpenImageIO/typedesc.h>

namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(OIIO::TypeDesc, OIIO_TypeDesc)
CPPMM_DEFINE_POINTER_CASTS(std::vector<OIIO::TypeDesc>, OIIO_TypeDesc_vector);

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {


void OIIO_TypeDesc_vector_ctor(OIIO_TypeDesc_vector* vec) {
    new (vec) std::vector<OIIO::TypeDesc>();
}

void OIIO_TypeDesc_vector_dtor(const OIIO_TypeDesc_vector* vec) {
    to_cpp(vec)->~vector();
}

void OIIO_TypeDesc_vector_get(const OIIO_TypeDesc_vector* vec, int index, OIIO_TypeDesc* element) {
    const std::vector<OIIO::TypeDesc>& v = *to_cpp(vec);
    const OIIO::TypeDesc* p = &v[index];
    *element = *to_c(p);
}

void OIIO_TypeDesc_vector_set(OIIO_TypeDesc_vector* vec, int index, OIIO_TypeDesc* element) {
    (*to_cpp(vec))[index] = *to_cpp(element);
}

int OIIO_TypeDesc_vector_size(const OIIO_TypeDesc_vector* vec) {
    return to_cpp(vec)->size();
}

OIIO_TypeDesc* OIIO_TypeDesc_vector_data(OIIO_TypeDesc_vector* vec) {
    return to_c(to_cpp(vec)->data());
}

static_assert(sizeof(OIIO::TypeDesc) == sizeof(OIIO_TypeDesc), "sizes do not match");
static_assert(alignof(OIIO::TypeDesc) == alignof(OIIO_TypeDesc), "alignments do not match");
static_assert(offsetof(OIIO::TypeDesc, basetype) == offsetof(OIIO_TypeDesc, basetype), "field offset does not match");
static_assert(offsetof(OIIO::TypeDesc, aggregate) == offsetof(OIIO_TypeDesc, aggregate), "field offset does not match");
static_assert(offsetof(OIIO::TypeDesc, vecsemantics) == offsetof(OIIO_TypeDesc, vecsemantics), "field offset does not match");
static_assert(offsetof(OIIO::TypeDesc, reserved) == offsetof(OIIO_TypeDesc, reserved), "field offset does not match");
static_assert(offsetof(OIIO::TypeDesc, arraylen) == offsetof(OIIO_TypeDesc, arraylen), "field offset does not match");


}
    