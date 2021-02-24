#include <OpenImageIO/typedesc.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {
namespace OIIO_NAMESPACE {

// alias the main library namespace with a convenient short form here
namespace OIIO = ::OIIO_NAMESPACE;

struct TypeDesc {
    using BoundType = OIIO::TypeDesc;

    enum BASETYPE {};
    enum AGGREGATE {};
    enum VECSEMANTICS {};

} CPPMM_VALUETYPE;

} // namespace OIIO_NAMESPACE
} // namespace cppmm_bind
