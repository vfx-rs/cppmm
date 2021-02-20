#include <OpenEXR/ImfLut.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct HalfLut {
    using BoundType = Imf::HalfLut;

} CPPMM_OPAQUEBYTES;

struct RgbaLut {
    using BoundType = Imf::RgbaLut;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
