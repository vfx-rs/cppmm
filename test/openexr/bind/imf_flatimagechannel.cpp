#include <OpenEXR/ImfFlatImageChannel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct FlatImageChannel {
    using BoundType = Imf::FlatImageChannel;

    // Inherited from ImageChannel
    virtual Imf::PixelType pixelType() const = 0;
    int xSampling() const;
    int ySampling() const;
    bool pLinear() const;
    int pixelsPerRow() const;
    int pixelsPerColumn() const;
    size_t numPixels() const;
    Imf::ImageLevel& level();
    const Imf::ImageLevel& level() const;

    // this class
    virtual Imf::Slice slice() const = 0;
    IMFUTIL_EXPORT
    Imf::FlatImageLevel& flatLevel();
    IMFUTIL_EXPORT
    const Imf::FlatImageLevel& flatLevel() const;

} CPPMM_OPAQUEPTR;

template <typename T> struct TypedFlatImageChannel {
    using BoundType = Imf::TypedFlatImageChannel<T>;

    // Inherited from ImageChannel
    virtual Imf::PixelType pixelType() const = 0;
    int xSampling() const;
    int ySampling() const;
    bool pLinear() const;
    int pixelsPerRow() const;
    int pixelsPerColumn() const;
    size_t numPixels() const;
    Imf::ImageLevel& level();
    const Imf::ImageLevel& level() const;

    // Imherited from FlatImageChannel
    virtual Imf::Slice slice() const;
    IMFUTIL_EXPORT
    Imf::FlatImageLevel& flatLevel();
    IMFUTIL_EXPORT
    const Imf::FlatImageLevel& flatLevel() const;

    // This class
    T& operator()(int x, int y) CPPMM_RENAME(index);
    const T& operator()(int x, int y) const CPPMM_RENAME(index_const);
    T& at(int x, int y) CPPMM_RENAME(at)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);
    const T& at(int x, int y) const CPPMM_RENAME(at_const)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);
    T* row(int r);
    const T* row(int r) const CPPMM_RENAME(row_const);

} CPPMM_OPAQUEBYTES;

template class TypedFlatImageChannel<half>;
using FlatHalfChannel = Imf::TypedFlatImageChannel<half>;

template class TypedFlatImageChannel<float>;
using FlatFloatChannel = Imf::TypedFlatImageChannel<float>;

template class TypedFlatImageChannel<unsigned int>;
using FlatUIntChannel = Imf::TypedFlatImageChannel<unsigned int>;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind

template class Imf::TypedFlatImageChannel<half>;
template class Imf::TypedFlatImageChannel<float>;
template class Imf::TypedFlatImageChannel<unsigned int>;
