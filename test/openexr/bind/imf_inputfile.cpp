#include <OpenEXR/ImfInputFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct InputFile {
    using BoundType = Imf::InputFile;

    IMF_EXPORT
    InputFile(const char fileName[], int numThreads);

    IMF_EXPORT
    InputFile(Imf::IStream& is, int numThreads) CPPMM_RENAME(from_stream);

    IMF_EXPORT
    virtual ~InputFile();

    IMF_EXPORT
    const char* fileName() const;

    IMF_EXPORT
    const Imf::Header& header() const;

    IMF_EXPORT
    int version() const;

    IMF_EXPORT
    void setFrameBuffer(const Imf::FrameBuffer& frameBuffer);

    IMF_EXPORT
    const Imf::FrameBuffer& frameBuffer() const;

    IMF_EXPORT
    bool isComplete() const;

    IMF_EXPORT
    bool isOptimizationEnabled() const;

    IMF_EXPORT
    void readPixels(int scanLine1, int scanLine2);
    IMF_EXPORT
    void readPixels(int scanLine) CPPMM_IGNORE;

    IMF_EXPORT
    void rawPixelData(int firstScanLine, const char*& pixelData,
                      int& pixelDataSize);

    IMF_EXPORT
    void rawPixelDataToBuffer(int scanLine, char* pixelData,
                              int& pixelDataSize) const;

    IMF_EXPORT
    void rawTileData(int& dx, int& dy, int& lx, int& ly, const char*& pixelData,
                     int& pixelDataSize);

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
