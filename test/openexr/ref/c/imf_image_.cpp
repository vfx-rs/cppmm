#include <imf_image_private_.h>

#include <imath_box_private_.h>
#include <imf_imagelevel_private_.h>


void Imf_2_5_Image_dtor(
    Imf_2_5_Image * this_)
{
    (to_cpp(this_)) -> Imf_2_5::Image::~Image();
}

int Imf_2_5_Image_numLevels(
    Imf_2_5_Image const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_Image_numXLevels(
    Imf_2_5_Image const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_Image_numYLevels(
    Imf_2_5_Image const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

Imath_2_5_Box2i const * Imf_2_5_Image_dataWindow(
    Imf_2_5_Image const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

Imath_2_5_Box2i const * Imf_2_5_Image_dataWindowForLevel(
    Imf_2_5_Image const * this_
    , int l)
{
    return to_c((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i const * Imf_2_5_Image_dataWindowForLevel_1(
    Imf_2_5_Image const * this_
    , int lx
    , int ly)
{
    return to_c((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

int Imf_2_5_Image_levelWidth(
    Imf_2_5_Image const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_Image_levelHeight(
    Imf_2_5_Image const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

void Imf_2_5_Image_resize(
    Imf_2_5_Image * this_
    , Imath_2_5_Box2i const * dataWindow)
{
    (to_cpp(this_)) -> resize(to_cpp_ref(dataWindow));
}

void Imf_2_5_Image_shiftPixels(
    Imf_2_5_Image * this_
    , int dx
    , int dy)
{
    (to_cpp(this_)) -> shiftPixels(dx, dy);
}

void Imf_2_5_Image_clearChannels(
    Imf_2_5_Image * this_)
{
    (to_cpp(this_)) -> clearChannels();
}

Imf_2_5_ImageLevel * Imf_2_5_Image_level(
    Imf_2_5_Image * this_
    , int l)
{
    return to_c((to_cpp(this_)) -> level(l));
}

Imf_2_5_ImageLevel const * Imf_2_5_Image_level_1(
    Imf_2_5_Image const * this_
    , int l)
{
    return to_c((to_cpp(this_)) -> level(l));
}

Imf_2_5_ImageLevel * Imf_2_5_Image_level_2(
    Imf_2_5_Image * this_
    , int lx
    , int ly)
{
    return to_c((to_cpp(this_)) -> level(lx, ly));
}

Imf_2_5_ImageLevel const * Imf_2_5_Image_level_3(
    Imf_2_5_Image const * this_
    , int lx
    , int ly)
{
    return to_c((to_cpp(this_)) -> level(lx, ly));
}
