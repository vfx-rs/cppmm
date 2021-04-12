#include <imf_previewimage_private_.h>

#include <new>


void Imf_2_5_PreviewRgba_PreviewRgba(
    Imf_2_5_PreviewRgba * this_
    , unsigned char r
    , unsigned char g
    , unsigned char b
    , unsigned char a)
{
    new (this_) Imf_2_5::PreviewRgba(r, g, b, a);
}

void Imf_2_5_PreviewImage_PreviewImage(
    Imf_2_5_PreviewImage * this_
    , unsigned int width
    , unsigned int height
    , Imf_2_5_PreviewRgba const * pixels)
{
    new (this_) Imf_2_5::PreviewImage(width, height, to_cpp(pixels));
}

void Imf_2_5_PreviewImage_PreviewImage_1(
    Imf_2_5_PreviewImage * this_
    , Imf_2_5_PreviewImage const * other)
{
    new (this_) Imf_2_5::PreviewImage(to_cpp_ref(other));
}

void Imf_2_5_PreviewImage_dtor(
    Imf_2_5_PreviewImage * this_)
{
    (to_cpp(this_)) -> Imf_2_5::PreviewImage::~PreviewImage();
}

Imf_2_5_PreviewImage * Imf_2_5_PreviewImage__assign(
    Imf_2_5_PreviewImage * this_
    , Imf_2_5_PreviewImage const * other)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(other)));
}

unsigned int Imf_2_5_PreviewImage_width(
    Imf_2_5_PreviewImage const * this_)
{
    return (to_cpp(this_)) -> width();
}

unsigned int Imf_2_5_PreviewImage_height(
    Imf_2_5_PreviewImage const * this_)
{
    return (to_cpp(this_)) -> height();
}

Imf_2_5_PreviewRgba * Imf_2_5_PreviewImage_pixels(
    Imf_2_5_PreviewImage * this_)
{
    return to_c((to_cpp(this_)) -> pixels());
}

Imf_2_5_PreviewRgba const * Imf_2_5_PreviewImage_pixels_1(
    Imf_2_5_PreviewImage const * this_)
{
    return to_c((to_cpp(this_)) -> pixels());
}

Imf_2_5_PreviewRgba * Imf_2_5_PreviewImage_pixel(
    Imf_2_5_PreviewImage * this_
    , unsigned int x
    , unsigned int y)
{
    return to_c((to_cpp(this_)) -> pixel(x, y));
}

Imf_2_5_PreviewRgba const * Imf_2_5_PreviewImage_pixel_1(
    Imf_2_5_PreviewImage const * this_
    , unsigned int x
    , unsigned int y)
{
    return to_c((to_cpp(this_)) -> pixel(x, y));
}
