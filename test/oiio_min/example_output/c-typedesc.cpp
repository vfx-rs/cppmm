//
#include "c-typedesc.h"
#include <OpenImageIO/typedesc.h>

namespace {
#include "casts.h"
CPPMM_DEFINE_POINTER_CASTS(OIIO::TypeDesc, OIIO_TypeDesc)

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {
static_assert(sizeof(OIIO::TypeDesc) == sizeof(OIIO_TypeDesc), "sizes do not match");
static_assert(alignof(OIIO::TypeDesc) == alignof(OIIO_TypeDesc), "alignments do not match");
static_assert(offsetof(OIIO::TypeDesc, basetype) == offsetof(OIIO_TypeDesc, basetype), "field offset does not match");
static_assert(offsetof(OIIO::TypeDesc, aggregate) == offsetof(OIIO_TypeDesc, aggregate), "field offset does not match");
static_assert(offsetof(OIIO::TypeDesc, vecsemantics) == offsetof(OIIO_TypeDesc, vecsemantics), "field offset does not match");
static_assert(offsetof(OIIO::TypeDesc, reserved) == offsetof(OIIO_TypeDesc, reserved), "field offset does not match");
static_assert(offsetof(OIIO::TypeDesc, arraylen) == offsetof(OIIO_TypeDesc, arraylen), "field offset does not match");


}
    