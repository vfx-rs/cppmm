#include <OpenEXR/ImfOutputPart.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct OutputPart {
    using BoundType = Imf::OutputPart;

    IMF_EXPORT
    OutputPart(Imf::MultiPartOutputFile& multiPartFile, int partNumber);

    IMF_EXPORT
    const char* fileName() const;
    IMF_EXPORT
    const Imf::Header& header() const;
    IMF_EXPORT
    void setFrameBuffer(const Imf::FrameBuffer& frameBuffer);
    IMF_EXPORT
    const Imf::FrameBuffer& frameBuffer() const;
    IMF_EXPORT
    void writePixels(int numScanLines = 1);
    IMF_EXPORT
    int currentScanLine() const;
    IMF_EXPORT
    void copyPixels(Imf::InputFile& in);
    IMF_EXPORT
    void copyPixels(Imf::InputPart& in);

    IMF_EXPORT
    void updatePreviewImage(const Imf::PreviewRgba newPixels[]);
    IMF_EXPORT
    void breakScanLine(int y, int offset, int length, char c);

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
