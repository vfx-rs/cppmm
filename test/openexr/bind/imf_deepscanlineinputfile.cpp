#include <OpenEXR/ImfDeepScanLineInputFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepScanLineInputFile {
    using BoundType = Imf::DeepScanLineInputFile;

    IMF_EXPORT
    DeepScanLineInputFile(const char fileName[], int numThreads);

    IMF_EXPORT
    DeepScanLineInputFile(const Imf::Header& header, Imf::IStream* is,
                          int version, /*version field from file*/
                          int numThreads);

    IMF_EXPORT
    virtual ~DeepScanLineInputFile();
    IMF_EXPORT
    const char* fileName() const;

    IMF_EXPORT
    const Imf::Header& header() const;

    IMF_EXPORT
    int version() const;

    IMF_EXPORT
    void setFrameBuffer(const Imf::DeepFrameBuffer& frameBuffer);

    IMF_EXPORT
    const Imf::DeepFrameBuffer& frameBuffer() const;

    IMF_EXPORT
    bool isComplete() const;

    IMF_EXPORT
    void readPixels(int scanLine1, int scanLine2);
    IMF_EXPORT
    void readPixels(int scanLine) CPPMM_IGNORE;

    IMF_EXPORT
    void readPixels(const char* rawPixelData,
                    const Imf::DeepFrameBuffer& frameBuffer, int scanLine1,
                    int scanLine2) const
        CPPMM_RENAME(readPixels_from_frame_buffer);

    IMF_EXPORT
    void rawPixelData(int firstScanLine, char* pixelData,
                      Imf::Int64& pixelDataSize);

    IMF_EXPORT
    int firstScanLineInChunk(int y) const;
    IMF_EXPORT
    int lastScanLineInChunk(int y) const;

    IMF_EXPORT
    void readPixelSampleCounts(int scanline1, int scanline2);
    IMF_EXPORT
    void readPixelSampleCounts(int scanline) CPPMM_IGNORE;

    IMF_EXPORT
    void readPixelSampleCounts(const char* rawdata,
                               const Imf::DeepFrameBuffer& frameBuffer,
                               int scanLine1, int scanLine2) const
        CPPMM_RENAME(readPixelSampleCounts_into_frame_buffer);

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
