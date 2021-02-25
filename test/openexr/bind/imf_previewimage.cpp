#include <OpenEXR/ImfPreviewImage.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct PreviewRgba {
    using BoundType = Imf::PreviewRgba;

    PreviewRgba(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0,
                unsigned char a = 255);
} CPPMM_VALUETYPE;

struct PreviewImage {
    using BoundType = Imf::PreviewImage;

    IMF_EXPORT
    PreviewImage(unsigned int width = 0, unsigned int height = 0,
                 const Imf::PreviewRgba pixels[] = 0);

    IMF_EXPORT
    PreviewImage(const Imf::PreviewImage& other);
    IMF_EXPORT
    ~PreviewImage();

    IMF_EXPORT
    Imf::PreviewImage& operator=(const Imf::PreviewImage& other);

    //-----------------------------------------------
    // Access to width, height and to the pixel array
    //-----------------------------------------------

    inline unsigned int width() const;
    inline unsigned int height() const;

    inline Imf::PreviewRgba* pixels();
    inline const Imf::PreviewRgba* pixels() const CPPMM_RENAME(pixels_const);

    //----------------------------
    // Access to individual pixels
    //----------------------------

    inline Imf::PreviewRgba& pixel(unsigned int x, unsigned int y);

    inline const Imf::PreviewRgba& pixel(unsigned int x, unsigned int y) const
        CPPMM_RENAME(pixel_const);

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
