#include <OpenEXR/ImfDeepScanLineOutputPart.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepScanLineOutputPart {
    using BoundType = Imf::DeepScanLineOutputPart;

    IMF_EXPORT
    DeepScanLineOutputPart(Imf::MultiPartOutputFile& multiPartFile,
                           int partNumber);

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
        CPPMM_RENAME(copyPixels_from_input_part);

    IMF_EXPORT
    void updatePreviewImage(const Imf::PreviewRgba newPixels[]);

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
