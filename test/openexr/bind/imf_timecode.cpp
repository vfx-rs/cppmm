#include <OpenEXR/ImfTimeCode.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct TimeCode {
    using BoundType = Imf::TimeCode;
    enum Packing {};

} CPPMM_VALUETYPE;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
