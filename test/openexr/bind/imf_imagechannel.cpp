#include <OpenEXR/ImfImageChannel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct ImageChannel {
    using BoundType = Imf::ImageChannel;

    // Inherited from ImageChannel
    virtual Imf::PixelType pixelType() const = 0;
    IMFUTIL_EXPORT
    Imf::Channel channel() const;
    int xSampling() const;
    int ySampling() const;
    bool pLinear() const;
    int pixelsPerRow() const;
    int pixelsPerColumn() const;
    size_t numPixels() const;
    Imf::ImageLevel& level();
    const Imf::ImageLevel& level() const;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
