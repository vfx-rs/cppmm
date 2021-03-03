#include <OpenEXR/ImfAcesFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

const Imf::Chromaticities& acesChromaticities();

class AcesOutputFile {
public:
    using BoundType = Imf::AcesOutputFile;

    IMF_EXPORT
    AcesOutputFile(const std::string& name, const Imf::Header& header,
                   Imf::RgbaChannels rgbaChannels, int numThreads)
        CPPMM_RENAME(new);

    IMF_EXPORT
    AcesOutputFile(Imf::OStream& os, const Imf::Header& header,
                   Imf::RgbaChannels rgbaChannels, int numThreads)
        CPPMM_RENAME(new_with_stream);

    IMF_EXPORT
    AcesOutputFile(const std::string& name, const Imath::Box2i& displayWindow,
                   const IMATH_INTERNAL_NAMESPACE::Box2i& dataWindow,
                   Imf::RgbaChannels rgbaChannels, float pixelAspectRatio,
                   const Imath::V2f screenWindowCenter, float screenWindowWidth,
                   Imf::LineOrder lineOrder, Imf::Compression compression,
                   int numThreads) CPPMM_RENAME(new_with_header);

    IMF_EXPORT
    AcesOutputFile(const std::string& name, int width, int height,
                   Imf::RgbaChannels rgbaChannels, float pixelAspectRatio,
                   const Imath::V2f screenWindowCenter, float screenWindowWidth,
                   Imf::LineOrder lineOrder, Imf::Compression compression,
                   int numThreads) CPPMM_IGNORE;

    IMF_EXPORT
    virtual ~AcesOutputFile();

    IMF_EXPORT
    void setFrameBuffer(const Imf::Rgba* base, size_t xStride, size_t yStride);

    IMF_EXPORT
    void writePixels(int numScanLines);
    IMF_EXPORT
    int currentScanLine() const;

    IMF_EXPORT
    const Imf::Header& header() const;
    IMF_EXPORT
    const Imath::Box2i& displayWindow() const;
    IMF_EXPORT
    const Imath::Box2i& dataWindow() const;
    IMF_EXPORT
    float pixelAspectRatio() const;
    IMF_EXPORT
    const Imath::V2f screenWindowCenter() const;
    IMF_EXPORT
    float screenWindowWidth() const;
    IMF_EXPORT
    Imf::LineOrder lineOrder() const;
    IMF_EXPORT
    Imf::Compression compression() const;
    IMF_EXPORT
    Imf::RgbaChannels channels() const;

    IMF_EXPORT
    void updatePreviewImage(const Imf::PreviewRgba newPixels[]);
} CPPMM_OPAQUEPTR;

class AcesInputFile {
public:
    using BoundType = Imf::AcesInputFile;

    IMF_EXPORT
    AcesInputFile(const std::string& name, int numThreads) CPPMM_RENAME(new);

    IMF_EXPORT
    AcesInputFile(Imf::IStream& is, int numThreads)
        CPPMM_RENAME(new_with_stream);

    IMF_EXPORT
    virtual ~AcesInputFile();

    IMF_EXPORT
    void setFrameBuffer(Imf::Rgba* base, size_t xStride, size_t yStride);

    IMF_EXPORT
    void readPixels(int scanLine1, int scanLine2);

    IMF_EXPORT
    void readPixels(int scanLine) CPPMM_IGNORE;

    IMF_EXPORT
    const Imf::Header& header() const;
    IMF_EXPORT
    const IMATH_NAMESPACE::Box2i& displayWindow() const;
    IMF_EXPORT
    const IMATH_NAMESPACE::Box2i& dataWindow() const;
    IMF_EXPORT
    float pixelAspectRatio() const;
    IMF_EXPORT
    const IMATH_NAMESPACE::V2f screenWindowCenter() const;
    IMF_EXPORT
    float screenWindowWidth() const;
    IMF_EXPORT
    Imf::LineOrder lineOrder() const;
    IMF_EXPORT
    Imf::Compression compression() const;
    IMF_EXPORT
    Imf::RgbaChannels channels() const;
    IMF_EXPORT
    const char* fileName() const;
    IMF_EXPORT
    bool isComplete() const;

    IMF_EXPORT
    int version() const;

} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
