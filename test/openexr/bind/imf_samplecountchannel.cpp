#include <OpenEXR/ImfSampleCountChannel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct SampleCountChannel {
    using BoundType = Imf::SampleCountChannel;

    IMFUTIL_EXPORT
    virtual Imf::PixelType pixelType() const;

    IMFUTIL_EXPORT
    Imf::Slice slice() const;

    IMFUTIL_EXPORT
    Imf::DeepImageLevel& deepLevel();
    IMFUTIL_EXPORT
    const Imf::DeepImageLevel& deepLevel() const;

    IMFUTIL_EXPORT
    const unsigned int& operator()(int x, int y) const CPPMM_RENAME(index);

    IMFUTIL_EXPORT
    const unsigned int& at(int x, int y) const
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    IMFUTIL_EXPORT
    const unsigned int* row(int r) const;

    IMFUTIL_EXPORT
    void set(int x, int y, unsigned int newNumSamples)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);
    IMFUTIL_EXPORT
    void set(int r, unsigned int newNumSamples[]) CPPMM_RENAME(set_row)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);
    IMFUTIL_EXPORT
    void clear();

    IMFUTIL_EXPORT
    unsigned int* beginEdit();
    IMFUTIL_EXPORT
    void endEdit();

    IMFUTIL_EXPORT
    const unsigned int* numSamples() const;
    IMFUTIL_EXPORT
    const unsigned int* sampleListSizes() const;
    IMFUTIL_EXPORT
    const size_t* sampleListPositions() const;
    IMFUTIL_EXPORT
    size_t sampleBufferSize() const;

    struct Edit {
        using BoundType = Imf::SampleCountChannel::Edit;

        IMFUTIL_EXPORT
        Edit(Imf::SampleCountChannel& level);
        IMFUTIL_EXPORT
        ~Edit();

        IMFUTIL_EXPORT
        unsigned int* sampleCounts() const;

    } CPPMM_OPAQUEBYTES;

} CPPMM_VALUETYPE;

enum RgbaChannels {};

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
