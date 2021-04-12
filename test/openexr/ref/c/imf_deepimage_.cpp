#include <imf_deepimage_private_.h>

#include <imath_box_private_.h>
#include <imf_deepimagelevel_private_.h>
#include <new>


int Imf_2_5_DeepImage_numLevels(
    Imf_2_5_DeepImage const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_DeepImage_numXLevels(
    Imf_2_5_DeepImage const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_DeepImage_numYLevels(
    Imf_2_5_DeepImage const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

Imath_2_5_Box2i const * Imf_2_5_DeepImage_dataWindow(
    Imf_2_5_DeepImage const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

Imath_2_5_Box2i const * Imf_2_5_DeepImage_dataWindowForLevel(
    Imf_2_5_DeepImage const * this_
    , int l)
{
    return to_c((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i const * Imf_2_5_DeepImage_dataWindowForLevel_1(
    Imf_2_5_DeepImage const * this_
    , int lx
    , int ly)
{
    return to_c((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

int Imf_2_5_DeepImage_levelWidth(
    Imf_2_5_DeepImage const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_DeepImage_levelHeight(
    Imf_2_5_DeepImage const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

void Imf_2_5_DeepImage_resize(
    Imf_2_5_DeepImage * this_
    , Imath_2_5_Box2i const * dataWindow)
{
    (to_cpp(this_)) -> resize(to_cpp_ref(dataWindow));
}

void Imf_2_5_DeepImage_shiftPixels(
    Imf_2_5_DeepImage * this_
    , int dx
    , int dy)
{
    (to_cpp(this_)) -> shiftPixels(dx, dy);
}

void Imf_2_5_DeepImage_clearChannels(
    Imf_2_5_DeepImage * this_)
{
    (to_cpp(this_)) -> clearChannels();
}

void Imf_2_5_DeepImage_DeepImage(
    Imf_2_5_DeepImage * this_)
{
    new (this_) Imf_2_5::DeepImage();
}

void Imf_2_5_DeepImage_dtor(
    Imf_2_5_DeepImage * this_)
{
    (to_cpp(this_)) -> Imf_2_5::DeepImage::~DeepImage();
}

Imf_2_5_DeepImageLevel * Imf_2_5_DeepImage_level(
    Imf_2_5_DeepImage * this_
    , int l)
{
    return to_c((to_cpp(this_)) -> level(l));
}

Imf_2_5_DeepImageLevel const * Imf_2_5_DeepImage_level_1(
    Imf_2_5_DeepImage const * this_
    , int l)
{
    return to_c((to_cpp(this_)) -> level(l));
}

Imf_2_5_DeepImageLevel * Imf_2_5_DeepImage_level_2(
    Imf_2_5_DeepImage * this_
    , int lx
    , int ly)
{
    return to_c((to_cpp(this_)) -> level(lx, ly));
}

Imf_2_5_DeepImageLevel const * Imf_2_5_DeepImage_level_3(
    Imf_2_5_DeepImage const * this_
    , int lx
    , int ly)
{
    return to_c((to_cpp(this_)) -> level(lx, ly));
}
