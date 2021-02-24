#include <OpenEXR/ImfDeepImageIO.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

IMFUTIL_EXPORT
void saveDeepImage(const std::string& fileName, const Imf::Header& hdr,
                   const Imf::DeepImage& img, Imf::DataWindowSource dws)
    CPPMM_RENAME(saveDeepImage_with_header);

IMFUTIL_EXPORT
void saveDeepImage(const std::string& fileName, const Imf::DeepImage& img);

IMFUTIL_EXPORT
void loadDeepImage(const std::string& fileName, Imf::Header& hdr,
                   Imf::DeepImage& img) CPPMM_RENAME(loadDeepImage_with_header);
IMFUTIL_EXPORT
void loadDeepImage(const std::string& fileName, Imf::DeepImage& img);

IMFUTIL_EXPORT
void saveDeepScanLineImage(const std::string& fileName, const Imf::Header& hdr,
                           const Imf::DeepImage& img, Imf::DataWindowSource dws)
    CPPMM_RENAME(saveDeepScanLineImage_with_header);

IMFUTIL_EXPORT
void saveDeepScanLineImage(const std::string& fileName,
                           const Imf::DeepImage& img);

IMFUTIL_EXPORT
void loadDeepScanLineImage(const std::string& fileName, Imf::Header& hdr,
                           Imf::DeepImage& img)
    CPPMM_RENAME(loadDeepScanLineImage_with_header);

IMFUTIL_EXPORT
void loadDeepScanLineImage(const std::string& fileName, Imf::DeepImage& img);

IMFUTIL_EXPORT
void saveDeepTiledImage(const std::string& fileName, const Imf::Header& hdr,
                        const Imf::DeepImage& img, Imf::DataWindowSource dws)
    CPPMM_RENAME(saveDeepTiledImage_with_header);

IMFUTIL_EXPORT
void saveDeepTiledImage(const std::string& fileName, const Imf::DeepImage& img);

IMFUTIL_EXPORT
void loadDeepTiledImage(const std::string& fileName, Imf::Header& hdr,
                        Imf::DeepImage& img)
    CPPMM_RENAME(loadDeepTiledImage_with_header);

IMFUTIL_EXPORT
void loadDeepTiledImage(const std::string& fileName, Imf::DeepImage& img);

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE
} // namespace cppmm_bind
