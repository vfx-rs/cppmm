#include <imf_flatimage_private_.h>

#include <imath_box_private_.h>
#include <imf_flatimagelevel_private_.h>
#include <new>


int Imf_2_5_FlatImage_numLevels(
    Imf_2_5_FlatImage const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_FlatImage_numXLevels(
    Imf_2_5_FlatImage const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_FlatImage_numYLevels(
    Imf_2_5_FlatImage const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

Imath_2_5_Box2i const * Imf_2_5_FlatImage_dataWindow(
    Imf_2_5_FlatImage const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

Imath_2_5_Box2i const * Imf_2_5_FlatImage_dataWindowForLevel(
    Imf_2_5_FlatImage const * this_
    , int l)
{
    return to_c((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i const * Imf_2_5_FlatImage_dataWindowForLevel_1(
    Imf_2_5_FlatImage const * this_
    , int lx
    , int ly)
{
    return to_c((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

int Imf_2_5_FlatImage_levelWidth(
    Imf_2_5_FlatImage const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_FlatImage_levelHeight(
    Imf_2_5_FlatImage const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

void Imf_2_5_FlatImage_resize(
    Imf_2_5_FlatImage * this_
    , Imath_2_5_Box2i const * dataWindow)
{
    (to_cpp(this_)) -> resize(to_cpp_ref(dataWindow));
}

void Imf_2_5_FlatImage_shiftPixels(
    Imf_2_5_FlatImage * this_
    , int dx
    , int dy)
{
    (to_cpp(this_)) -> shiftPixels(dx, dy);
}

void Imf_2_5_FlatImage_clearChannels(
    Imf_2_5_FlatImage * this_)
{
    (to_cpp(this_)) -> clearChannels();
}

void Imf_2_5_FlatImage_FlatImage(
    Imf_2_5_FlatImage * this_)
{
    new (this_) Imf_2_5::FlatImage();
}

void Imf_2_5_FlatImage_dtor(
    Imf_2_5_FlatImage * this_)
{
    (to_cpp(this_)) -> Imf_2_5::FlatImage::~FlatImage();
}

Imf_2_5_FlatImageLevel * Imf_2_5_FlatImage_level(
    Imf_2_5_FlatImage * this_
    , int l)
{
    return to_c((to_cpp(this_)) -> level(l));
}

Imf_2_5_FlatImageLevel const * Imf_2_5_FlatImage_level_1(
    Imf_2_5_FlatImage const * this_
    , int l)
{
    return to_c((to_cpp(this_)) -> level(l));
}

Imf_2_5_FlatImageLevel * Imf_2_5_FlatImage_level_2(
    Imf_2_5_FlatImage * this_
    , int lx
    , int ly)
{
    return to_c((to_cpp(this_)) -> level(lx, ly));
}

Imf_2_5_FlatImageLevel const * Imf_2_5_FlatImage_level_3(
    Imf_2_5_FlatImage const * this_
    , int lx
    , int ly)
{
    return to_c((to_cpp(this_)) -> level(lx, ly));
}
