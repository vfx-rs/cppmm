#include <OpenEXR/ImfImageIO.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

IMFUTIL_EXPORT
void saveImage(const std::string& fileName, const Imf::Header& hdr,
               const Imf::Image& img, Imf::DataWindowSource dws);

IMFUTIL_EXPORT
void saveImage(const std::string& fileName, const Imf::Image& img);

IMFUTIL_EXPORT
Imf::Image* loadImage(const std::string& fileName, Imf::Header& hdr);

IMFUTIL_EXPORT
Imf::Image* loadImage(const std::string& fileName);

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
