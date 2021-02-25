#include <OpenEXR/ImfLut.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct HalfLut {
    using BoundType = Imf::HalfLut;

    template <class Function> HalfLut(Function f);

    IMF_EXPORT
    void apply(half* data, int nData, int stride = 1) const;

    IMF_EXPORT
    void apply(const Imf::Slice& data,
               const IMATH_NAMESPACE::Box2i& dataWindow) const;

} CPPMM_OPAQUEBYTES;

struct RgbaLut {
    using BoundType = Imf::RgbaLut;

    template <class Function> RgbaLut(Function f, Imf::RgbaChannels chn);

    //----------------------------------------------------------------------
    // Apply the table to data[0], data[stride] ... data[(nData-1) * stride]
    //----------------------------------------------------------------------

    IMF_EXPORT
    void apply(Imf::Rgba* data, int nData, int stride = 1) const;

    //-----------------------------------------------------------------------
    // Apply the table to a frame buffer (see RgbaOutpuFile.setFrameBuffer())
    //-----------------------------------------------------------------------

    IMF_EXPORT
    void apply(Imf::Rgba* base, int xStride, int yStride,
               const IMATH_NAMESPACE::Box2i& dataWindow) const;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
