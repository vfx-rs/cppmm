#include <OpenEXR/ImfFlatImageIO.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

IMFUTIL_EXPORT
void saveFlatImage(const std::string& fileName, const Imf::Header& hdr,
                   const Imf::FlatImage& img, Imf::DataWindowSource dws)
    CPPMM_RENAME(saveFlatImage_with_header);

IMFUTIL_EXPORT
void saveFlatImage(const std::string& fileName, const Imf::FlatImage& img);

IMFUTIL_EXPORT
void loadFlatImage(const std::string& fileName, Imf::Header& hdr,
                   Imf::FlatImage& img);

IMFUTIL_EXPORT
void loadFlatImage(const std::string& fileName, Imf::FlatImage& img);

IMFUTIL_EXPORT
void saveFlatScanLineImage(const std::string& fileName, const Imf::Header& hdr,
                           const Imf::FlatImage& img, Imf::DataWindowSource dws)
    CPPMM_RENAME(saveFlatScanLineImage_with_header);

IMFUTIL_EXPORT
void saveFlatScanLineImage(const std::string& fileName,
                           const Imf::FlatImage& img);

IMFUTIL_EXPORT
void loadFlatScanLineImage(const std::string& fileName, Imf::Header& hdr,
                           Imf::FlatImage& img)
    CPPMM_RENAME(loadFlatScanLineImage_with_header);

IMFUTIL_EXPORT
void loadFlatScanLineImage(const std::string& fileName, Imf::FlatImage& img);

IMFUTIL_EXPORT
void saveFlatTiledImage(const std::string& fileName, const Imf::Header& hdr,
                        const Imf::FlatImage& img, Imf::DataWindowSource dws)
    CPPMM_RENAME(saveFlatTiledImage_with_header);

IMFUTIL_EXPORT
void saveFlatTiledImage(const std::string& fileName, const Imf::FlatImage& img);

IMFUTIL_EXPORT
void loadFlatTiledImage(const std::string& fileName, Imf::Header& hdr,
                        Imf::FlatImage& img)
    CPPMM_RENAME(loadFlatTiledImage_with_header);

IMFUTIL_EXPORT
void loadFlatTiledImage(const std::string& fileName, Imf::FlatImage& img);
} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
