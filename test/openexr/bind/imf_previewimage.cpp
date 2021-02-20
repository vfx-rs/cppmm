#include <OpenEXR/ImfPreviewImage.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct PreviewRgba {
    using BoundType = Imf::PreviewRgba;
} CPPMM_VALUETYPE;

struct PreviewImage {
    using BoundType = Imf::PreviewImage;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
