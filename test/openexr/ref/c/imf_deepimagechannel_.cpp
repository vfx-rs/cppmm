#include <imf_deepimagechannel_private_.h>

#include <half_private_.h>
#include <imf_channellist_private_.h>
#include <imf_deepframebuffer_private_.h>
#include <imf_deepimagelevel_private_.h>
#include <imf_samplecountchannel_private_.h>


Imf_2_5_Channel Imf_2_5_DeepImageChannel_channel(
    Imf_2_5_DeepImageChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> channel());
}

int Imf_2_5_DeepImageChannel_xSampling(
    Imf_2_5_DeepImageChannel const * this_)
{
    return (to_cpp(this_)) -> xSampling();
}

int Imf_2_5_DeepImageChannel_ySampling(
    Imf_2_5_DeepImageChannel const * this_)
{
    return (to_cpp(this_)) -> ySampling();
}

_Bool Imf_2_5_DeepImageChannel_pLinear(
    Imf_2_5_DeepImageChannel const * this_)
{
    return (to_cpp(this_)) -> pLinear();
}

int Imf_2_5_DeepImageChannel_pixelsPerRow(
    Imf_2_5_DeepImageChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerRow();
}

int Imf_2_5_DeepImageChannel_pixelsPerColumn(
    Imf_2_5_DeepImageChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerColumn();
}

unsigned long Imf_2_5_DeepImageChannel_numPixels(
    Imf_2_5_DeepImageChannel const * this_)
{
    return (to_cpp(this_)) -> numPixels();
}

Imf_2_5_DeepSlice Imf_2_5_DeepImageChannel_slice(
    Imf_2_5_DeepImageChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> slice());
}

Imf_2_5_DeepImageLevel * Imf_2_5_DeepImageChannel_deepLevel(
    Imf_2_5_DeepImageChannel * this_)
{
    return to_c((to_cpp(this_)) -> deepLevel());
}

Imf_2_5_DeepImageLevel const * Imf_2_5_DeepImageChannel_deepLevel_1(
    Imf_2_5_DeepImageChannel const * this_)
{
    return to_c((to_cpp(this_)) -> deepLevel());
}

Imf_2_5_SampleCountChannel * Imf_2_5_DeepImageChannel_sampleCounts(
    Imf_2_5_DeepImageChannel * this_)
{
    return to_c((to_cpp(this_)) -> sampleCounts());
}

Imf_2_5_SampleCountChannel const * Imf_2_5_DeepImageChannel_sampleCounts_1(
    Imf_2_5_DeepImageChannel const * this_)
{
    return to_c((to_cpp(this_)) -> sampleCounts());
}

Imf_2_5_Channel Imf_2_5_DeepHalfChannel_channel(
    Imf_2_5_DeepHalfChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> channel());
}

int Imf_2_5_DeepHalfChannel_xSampling(
    Imf_2_5_DeepHalfChannel const * this_)
{
    return (to_cpp(this_)) -> xSampling();
}

int Imf_2_5_DeepHalfChannel_ySampling(
    Imf_2_5_DeepHalfChannel const * this_)
{
    return (to_cpp(this_)) -> ySampling();
}

_Bool Imf_2_5_DeepHalfChannel_pLinear(
    Imf_2_5_DeepHalfChannel const * this_)
{
    return (to_cpp(this_)) -> pLinear();
}

int Imf_2_5_DeepHalfChannel_pixelsPerRow(
    Imf_2_5_DeepHalfChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerRow();
}

int Imf_2_5_DeepHalfChannel_pixelsPerColumn(
    Imf_2_5_DeepHalfChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerColumn();
}

unsigned long Imf_2_5_DeepHalfChannel_numPixels(
    Imf_2_5_DeepHalfChannel const * this_)
{
    return (to_cpp(this_)) -> numPixels();
}

Imf_2_5_DeepSlice Imf_2_5_DeepHalfChannel_slice(
    Imf_2_5_DeepHalfChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> slice());
}

Imath_2_5_half * Imf_2_5_DeepHalfChannel_operator()(
    Imf_2_5_DeepHalfChannel * this_
    , int x
    , int y)
{
    return to_c((to_cpp(this_)) -> operator()(x, y));
}

Imath_2_5_half const * Imf_2_5_DeepHalfChannel_operator()_1(
    Imf_2_5_DeepHalfChannel const * this_
    , int x
    , int y)
{
    return to_c((to_cpp(this_)) -> operator()(x, y));
}

Imath_2_5_half * Imf_2_5_DeepHalfChannel_at(
    Imf_2_5_DeepHalfChannel * this_
    , int x
    , int y)
{
    return to_c((to_cpp(this_)) -> at(x, y));
}

Imath_2_5_half const * Imf_2_5_DeepHalfChannel_at_1(
    Imf_2_5_DeepHalfChannel const * this_
    , int x
    , int y)
{
    return to_c((to_cpp(this_)) -> at(x, y));
}

Imath_2_5_half * * Imf_2_5_DeepHalfChannel_row(
    Imf_2_5_DeepHalfChannel * this_
    , int r)
{
    return to_c((to_cpp(this_)) -> row(r));
}

Imath_2_5_half const * * Imf_2_5_DeepHalfChannel_row_1(
    Imf_2_5_DeepHalfChannel const * this_
    , int r)
{
    return to_c((to_cpp(this_)) -> row(r));
}

Imf_2_5_Channel Imf_2_5_DeepFloatChannel_channel(
    Imf_2_5_DeepFloatChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> channel());
}

int Imf_2_5_DeepFloatChannel_xSampling(
    Imf_2_5_DeepFloatChannel const * this_)
{
    return (to_cpp(this_)) -> xSampling();
}

int Imf_2_5_DeepFloatChannel_ySampling(
    Imf_2_5_DeepFloatChannel const * this_)
{
    return (to_cpp(this_)) -> ySampling();
}

_Bool Imf_2_5_DeepFloatChannel_pLinear(
    Imf_2_5_DeepFloatChannel const * this_)
{
    return (to_cpp(this_)) -> pLinear();
}

int Imf_2_5_DeepFloatChannel_pixelsPerRow(
    Imf_2_5_DeepFloatChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerRow();
}

int Imf_2_5_DeepFloatChannel_pixelsPerColumn(
    Imf_2_5_DeepFloatChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerColumn();
}

unsigned long Imf_2_5_DeepFloatChannel_numPixels(
    Imf_2_5_DeepFloatChannel const * this_)
{
    return (to_cpp(this_)) -> numPixels();
}

Imf_2_5_DeepSlice Imf_2_5_DeepFloatChannel_slice(
    Imf_2_5_DeepFloatChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> slice());
}

float * Imf_2_5_DeepFloatChannel_operator()(
    Imf_2_5_DeepFloatChannel * this_
    , int x
    , int y)
{
    return (to_cpp(this_)) -> operator()(x, y);
}

float const * Imf_2_5_DeepFloatChannel_operator()_1(
    Imf_2_5_DeepFloatChannel const * this_
    , int x
    , int y)
{
    return (to_cpp(this_)) -> operator()(x, y);
}

float * Imf_2_5_DeepFloatChannel_at(
    Imf_2_5_DeepFloatChannel * this_
    , int x
    , int y)
{
    return (to_cpp(this_)) -> at(x, y);
}

float const * Imf_2_5_DeepFloatChannel_at_1(
    Imf_2_5_DeepFloatChannel const * this_
    , int x
    , int y)
{
    return (to_cpp(this_)) -> at(x, y);
}

float * * Imf_2_5_DeepFloatChannel_row(
    Imf_2_5_DeepFloatChannel * this_
    , int r)
{
    return to_c((to_cpp(this_)) -> row(r));
}

float const * * Imf_2_5_DeepFloatChannel_row_1(
    Imf_2_5_DeepFloatChannel const * this_
    , int r)
{
    return to_c((to_cpp(this_)) -> row(r));
}

Imf_2_5_Channel Imf_2_5_DeepUIntChannel_channel(
    Imf_2_5_DeepUIntChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> channel());
}

int Imf_2_5_DeepUIntChannel_xSampling(
    Imf_2_5_DeepUIntChannel const * this_)
{
    return (to_cpp(this_)) -> xSampling();
}

int Imf_2_5_DeepUIntChannel_ySampling(
    Imf_2_5_DeepUIntChannel const * this_)
{
    return (to_cpp(this_)) -> ySampling();
}

_Bool Imf_2_5_DeepUIntChannel_pLinear(
    Imf_2_5_DeepUIntChannel const * this_)
{
    return (to_cpp(this_)) -> pLinear();
}

int Imf_2_5_DeepUIntChannel_pixelsPerRow(
    Imf_2_5_DeepUIntChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerRow();
}

int Imf_2_5_DeepUIntChannel_pixelsPerColumn(
    Imf_2_5_DeepUIntChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerColumn();
}

unsigned long Imf_2_5_DeepUIntChannel_numPixels(
    Imf_2_5_DeepUIntChannel const * this_)
{
    return (to_cpp(this_)) -> numPixels();
}

Imf_2_5_DeepSlice Imf_2_5_DeepUIntChannel_slice(
    Imf_2_5_DeepUIntChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> slice());
}

unsigned int * Imf_2_5_DeepUIntChannel_operator()(
    Imf_2_5_DeepUIntChannel * this_
    , int x
    , int y)
{
    return (to_cpp(this_)) -> operator()(x, y);
}

unsigned int const * Imf_2_5_DeepUIntChannel_operator()_1(
    Imf_2_5_DeepUIntChannel const * this_
    , int x
    , int y)
{
    return (to_cpp(this_)) -> operator()(x, y);
}

unsigned int * Imf_2_5_DeepUIntChannel_at(
    Imf_2_5_DeepUIntChannel * this_
    , int x
    , int y)
{
    return (to_cpp(this_)) -> at(x, y);
}

unsigned int const * Imf_2_5_DeepUIntChannel_at_1(
    Imf_2_5_DeepUIntChannel const * this_
    , int x
    , int y)
{
    return (to_cpp(this_)) -> at(x, y);
}

unsigned int * * Imf_2_5_DeepUIntChannel_row(
    Imf_2_5_DeepUIntChannel * this_
    , int r)
{
    return to_c((to_cpp(this_)) -> row(r));
}

unsigned int const * * Imf_2_5_DeepUIntChannel_row_1(
    Imf_2_5_DeepUIntChannel const * this_
    , int r)
{
    return to_c((to_cpp(this_)) -> row(r));
}
