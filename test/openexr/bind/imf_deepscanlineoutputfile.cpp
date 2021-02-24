#include <OpenEXR/ImfDeepScanLineOutputFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepScanLineOutputFile {
    using BoundType = Imf::DeepScanLineOutputFile;

    IMF_EXPORT
    DeepScanLineOutputFile(const char fileName[], const Imf::Header& header,
                           int numThreads);

    IMF_EXPORT
    DeepScanLineOutputFile(Imf::OStream& os, const Imf::Header& header,
                           int numThreads) CPPMM_RENAME(from_stream);

    IMF_EXPORT
    virtual ~DeepScanLineOutputFile();

    IMF_EXPORT
    const char* fileName() const;

    IMF_EXPORT
    const Imf::Header& header() const;

    IMF_EXPORT
    void setFrameBuffer(const Imf::DeepFrameBuffer& frameBuffer);

    IMF_EXPORT
    const Imf::DeepFrameBuffer& frameBuffer() const;

    IMF_EXPORT
    void writePixels(int numScanLines);

    IMF_EXPORT
    int currentScanLine() const;

    IMF_EXPORT
    void copyPixels(Imf::DeepScanLineInputFile& in);

    IMF_EXPORT
    void copyPixels(Imf::DeepScanLineInputPart& in)
        CPPMM_RENAME(copyPixels_to_part);

    IMF_EXPORT
    void updatePreviewImage(const Imf::PreviewRgba newPixels[]);
} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
