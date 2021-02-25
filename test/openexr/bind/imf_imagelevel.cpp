#include <OpenEXR/ImfImageLevel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct ImageLevel {
    using BoundType = Imf::ImageLevel;

    Imf::Image& image();
    const Imf::Image& image() const CPPMM_RENAME(image_const);

    int xLevelNumber();
    int yLevelNumber();

    const IMATH_NAMESPACE::Box2i& dataWindow();

} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
