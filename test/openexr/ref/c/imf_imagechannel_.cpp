#include <imf_imagechannel_private_.h>

#include <imf_channellist_private_.h>
#include <imf_imagelevel_private_.h>


Imf_2_5_Channel Imf_2_5_ImageChannel_channel(
    Imf_2_5_ImageChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> channel());
}

int Imf_2_5_ImageChannel_xSampling(
    Imf_2_5_ImageChannel const * this_)
{
    return (to_cpp(this_)) -> xSampling();
}

int Imf_2_5_ImageChannel_ySampling(
    Imf_2_5_ImageChannel const * this_)
{
    return (to_cpp(this_)) -> ySampling();
}

_Bool Imf_2_5_ImageChannel_pLinear(
    Imf_2_5_ImageChannel const * this_)
{
    return (to_cpp(this_)) -> pLinear();
}

int Imf_2_5_ImageChannel_pixelsPerRow(
    Imf_2_5_ImageChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerRow();
}

int Imf_2_5_ImageChannel_pixelsPerColumn(
    Imf_2_5_ImageChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerColumn();
}

unsigned long Imf_2_5_ImageChannel_numPixels(
    Imf_2_5_ImageChannel const * this_)
{
    return (to_cpp(this_)) -> numPixels();
}

Imf_2_5_ImageLevel * Imf_2_5_ImageChannel_level(
    Imf_2_5_ImageChannel * this_)
{
    return to_c((to_cpp(this_)) -> level());
}

Imf_2_5_ImageLevel const * Imf_2_5_ImageChannel_level_1(
    Imf_2_5_ImageChannel const * this_)
{
    return to_c((to_cpp(this_)) -> level());
}
