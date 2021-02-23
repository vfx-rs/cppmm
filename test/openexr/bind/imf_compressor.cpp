#include <OpenEXR/ImfCompressor.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

class Compressor {
public:
    using BoundType = Imf::Compressor;

    enum Format {};

    IMF_EXPORT
    Compressor(const Imf::Header& hdr, size_t maxScanLineSize,
               size_t numScanLines, bool optFlatFields);

    IMF_EXPORT
    virtual ~Compressor();

    IMF_EXPORT
    virtual int numScanLines() const;

    IMF_EXPORT
    virtual Imf::Compressor::Format format() const;

    IMF_EXPORT
    virtual int compress(const char* inPtr, int inSize, int minY,
                         const char*& outPtr);

    IMF_EXPORT
    virtual int compressTile(const char* inPtr, int inSize,
                             IMATH_NAMESPACE::Box2i range, const char*& outPtr);

    IMF_EXPORT
    virtual int uncompress(const char* inPtr, int inSize, int minY,
                           const char*& outPtr);

    IMF_EXPORT
    virtual int uncompressTile(const char* inPtr, int inSize,
                               IMATH_NAMESPACE::Box2i range,
                               const char*& outPtr);
} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
