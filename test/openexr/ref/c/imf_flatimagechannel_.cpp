#include <imf_flatimagechannel_private_.h>

#include <half_private_.h>
#include <imf_flatimagelevel_private_.h>
#include <imf_framebuffer_private_.h>
#include <imf_imagelevel_private_.h>


int Imf_2_5_FlatImageChannel_xSampling(
    Imf_2_5_FlatImageChannel const * this_)
{
    return (to_cpp(this_)) -> xSampling();
}

int Imf_2_5_FlatImageChannel_ySampling(
    Imf_2_5_FlatImageChannel const * this_)
{
    return (to_cpp(this_)) -> ySampling();
}

_Bool Imf_2_5_FlatImageChannel_pLinear(
    Imf_2_5_FlatImageChannel const * this_)
{
    return (to_cpp(this_)) -> pLinear();
}

int Imf_2_5_FlatImageChannel_pixelsPerRow(
    Imf_2_5_FlatImageChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerRow();
}

int Imf_2_5_FlatImageChannel_pixelsPerColumn(
    Imf_2_5_FlatImageChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerColumn();
}

unsigned long Imf_2_5_FlatImageChannel_numPixels(
    Imf_2_5_FlatImageChannel const * this_)
{
    return (to_cpp(this_)) -> numPixels();
}

Imf_2_5_ImageLevel * Imf_2_5_FlatImageChannel_level(
    Imf_2_5_FlatImageChannel * this_)
{
    return to_c((to_cpp(this_)) -> level());
}

Imf_2_5_ImageLevel const * Imf_2_5_FlatImageChannel_level_1(
    Imf_2_5_FlatImageChannel const * this_)
{
    return to_c((to_cpp(this_)) -> level());
}

Imf_2_5_Slice Imf_2_5_FlatImageChannel_slice(
    Imf_2_5_FlatImageChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> slice());
}

Imf_2_5_FlatImageLevel * Imf_2_5_FlatImageChannel_flatLevel(
    Imf_2_5_FlatImageChannel * this_)
{
    return to_c((to_cpp(this_)) -> flatLevel());
}

Imf_2_5_FlatImageLevel const * Imf_2_5_FlatImageChannel_flatLevel_1(
    Imf_2_5_FlatImageChannel const * this_)
{
    return to_c((to_cpp(this_)) -> flatLevel());
}

int Imf_2_5_FlatHalfChannel_xSampling(
    Imf_2_5_FlatHalfChannel const * this_)
{
    return (to_cpp(this_)) -> xSampling();
}

int Imf_2_5_FlatHalfChannel_ySampling(
    Imf_2_5_FlatHalfChannel const * this_)
{
    return (to_cpp(this_)) -> ySampling();
}

_Bool Imf_2_5_FlatHalfChannel_pLinear(
    Imf_2_5_FlatHalfChannel const * this_)
{
    return (to_cpp(this_)) -> pLinear();
}

int Imf_2_5_FlatHalfChannel_pixelsPerRow(
    Imf_2_5_FlatHalfChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerRow();
}

int Imf_2_5_FlatHalfChannel_pixelsPerColumn(
    Imf_2_5_FlatHalfChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerColumn();
}

unsigned long Imf_2_5_FlatHalfChannel_numPixels(
    Imf_2_5_FlatHalfChannel const * this_)
{
    return (to_cpp(this_)) -> numPixels();
}

Imf_2_5_ImageLevel * Imf_2_5_FlatHalfChannel_level(
    Imf_2_5_FlatHalfChannel * this_)
{
    return to_c((to_cpp(this_)) -> level());
}

Imf_2_5_ImageLevel const * Imf_2_5_FlatHalfChannel_level_1(
    Imf_2_5_FlatHalfChannel const * this_)
{
    return to_c((to_cpp(this_)) -> level());
}

Imf_2_5_Slice Imf_2_5_FlatHalfChannel_slice(
    Imf_2_5_FlatHalfChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> slice());
}

Imf_2_5_FlatImageLevel * Imf_2_5_FlatHalfChannel_flatLevel(
    Imf_2_5_FlatHalfChannel * this_)
{
    return to_c((to_cpp(this_)) -> flatLevel());
}

Imf_2_5_FlatImageLevel const * Imf_2_5_FlatHalfChannel_flatLevel_1(
    Imf_2_5_FlatHalfChannel const * this_)
{
    return to_c((to_cpp(this_)) -> flatLevel());
}

Imath_2_5_half * Imf_2_5_FlatHalfChannel_operator()(
    Imf_2_5_FlatHalfChannel * this_
    , int x
    , int y)
{
    return to_c((to_cpp(this_)) -> operator()(x, y));
}

Imath_2_5_half const * Imf_2_5_FlatHalfChannel_operator()_1(
    Imf_2_5_FlatHalfChannel const * this_
    , int x
    , int y)
{
    return to_c((to_cpp(this_)) -> operator()(x, y));
}

Imath_2_5_half * Imf_2_5_FlatHalfChannel_at(
    Imf_2_5_FlatHalfChannel * this_
    , int x
    , int y)
{
    return to_c((to_cpp(this_)) -> at(x, y));
}

Imath_2_5_half const * Imf_2_5_FlatHalfChannel_at_1(
    Imf_2_5_FlatHalfChannel const * this_
    , int x
    , int y)
{
    return to_c((to_cpp(this_)) -> at(x, y));
}

Imath_2_5_half * Imf_2_5_FlatHalfChannel_row(
    Imf_2_5_FlatHalfChannel * this_
    , int r)
{
    return to_c((to_cpp(this_)) -> row(r));
}

Imath_2_5_half const * Imf_2_5_FlatHalfChannel_row_1(
    Imf_2_5_FlatHalfChannel const * this_
    , int r)
{
    return to_c((to_cpp(this_)) -> row(r));
}

int Imf_2_5_FlatFloatChannel_xSampling(
    Imf_2_5_FlatFloatChannel const * this_)
{
    return (to_cpp(this_)) -> xSampling();
}

int Imf_2_5_FlatFloatChannel_ySampling(
    Imf_2_5_FlatFloatChannel const * this_)
{
    return (to_cpp(this_)) -> ySampling();
}

_Bool Imf_2_5_FlatFloatChannel_pLinear(
    Imf_2_5_FlatFloatChannel const * this_)
{
    return (to_cpp(this_)) -> pLinear();
}

int Imf_2_5_FlatFloatChannel_pixelsPerRow(
    Imf_2_5_FlatFloatChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerRow();
}

int Imf_2_5_FlatFloatChannel_pixelsPerColumn(
    Imf_2_5_FlatFloatChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerColumn();
}

unsigned long Imf_2_5_FlatFloatChannel_numPixels(
    Imf_2_5_FlatFloatChannel const * this_)
{
    return (to_cpp(this_)) -> numPixels();
}

Imf_2_5_ImageLevel * Imf_2_5_FlatFloatChannel_level(
    Imf_2_5_FlatFloatChannel * this_)
{
    return to_c((to_cpp(this_)) -> level());
}

Imf_2_5_ImageLevel const * Imf_2_5_FlatFloatChannel_level_1(
    Imf_2_5_FlatFloatChannel const * this_)
{
    return to_c((to_cpp(this_)) -> level());
}

Imf_2_5_Slice Imf_2_5_FlatFloatChannel_slice(
    Imf_2_5_FlatFloatChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> slice());
}

Imf_2_5_FlatImageLevel * Imf_2_5_FlatFloatChannel_flatLevel(
    Imf_2_5_FlatFloatChannel * this_)
{
    return to_c((to_cpp(this_)) -> flatLevel());
}

Imf_2_5_FlatImageLevel const * Imf_2_5_FlatFloatChannel_flatLevel_1(
    Imf_2_5_FlatFloatChannel const * this_)
{
    return to_c((to_cpp(this_)) -> flatLevel());
}

float * Imf_2_5_FlatFloatChannel_operator()(
    Imf_2_5_FlatFloatChannel * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> operator()(x, y));
}

float const * Imf_2_5_FlatFloatChannel_operator()_1(
    Imf_2_5_FlatFloatChannel const * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> operator()(x, y));
}

float * Imf_2_5_FlatFloatChannel_at(
    Imf_2_5_FlatFloatChannel * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> at(x, y));
}

float const * Imf_2_5_FlatFloatChannel_at_1(
    Imf_2_5_FlatFloatChannel const * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> at(x, y));
}

float * Imf_2_5_FlatFloatChannel_row(
    Imf_2_5_FlatFloatChannel * this_
    , int r)
{
    return (to_cpp(this_)) -> row(r);
}

float const * Imf_2_5_FlatFloatChannel_row_1(
    Imf_2_5_FlatFloatChannel const * this_
    , int r)
{
    return (to_cpp(this_)) -> row(r);
}

int Imf_2_5_FlatUIntChannel_xSampling(
    Imf_2_5_FlatUIntChannel const * this_)
{
    return (to_cpp(this_)) -> xSampling();
}

int Imf_2_5_FlatUIntChannel_ySampling(
    Imf_2_5_FlatUIntChannel const * this_)
{
    return (to_cpp(this_)) -> ySampling();
}

_Bool Imf_2_5_FlatUIntChannel_pLinear(
    Imf_2_5_FlatUIntChannel const * this_)
{
    return (to_cpp(this_)) -> pLinear();
}

int Imf_2_5_FlatUIntChannel_pixelsPerRow(
    Imf_2_5_FlatUIntChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerRow();
}

int Imf_2_5_FlatUIntChannel_pixelsPerColumn(
    Imf_2_5_FlatUIntChannel const * this_)
{
    return (to_cpp(this_)) -> pixelsPerColumn();
}

unsigned long Imf_2_5_FlatUIntChannel_numPixels(
    Imf_2_5_FlatUIntChannel const * this_)
{
    return (to_cpp(this_)) -> numPixels();
}

Imf_2_5_ImageLevel * Imf_2_5_FlatUIntChannel_level(
    Imf_2_5_FlatUIntChannel * this_)
{
    return to_c((to_cpp(this_)) -> level());
}

Imf_2_5_ImageLevel const * Imf_2_5_FlatUIntChannel_level_1(
    Imf_2_5_FlatUIntChannel const * this_)
{
    return to_c((to_cpp(this_)) -> level());
}

Imf_2_5_Slice Imf_2_5_FlatUIntChannel_slice(
    Imf_2_5_FlatUIntChannel const * this_)
{
    return to_c_copy((to_cpp(this_)) -> slice());
}

Imf_2_5_FlatImageLevel * Imf_2_5_FlatUIntChannel_flatLevel(
    Imf_2_5_FlatUIntChannel * this_)
{
    return to_c((to_cpp(this_)) -> flatLevel());
}

Imf_2_5_FlatImageLevel const * Imf_2_5_FlatUIntChannel_flatLevel_1(
    Imf_2_5_FlatUIntChannel const * this_)
{
    return to_c((to_cpp(this_)) -> flatLevel());
}

unsigned int * Imf_2_5_FlatUIntChannel_operator()(
    Imf_2_5_FlatUIntChannel * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> operator()(x, y));
}

unsigned int const * Imf_2_5_FlatUIntChannel_operator()_1(
    Imf_2_5_FlatUIntChannel const * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> operator()(x, y));
}

unsigned int * Imf_2_5_FlatUIntChannel_at(
    Imf_2_5_FlatUIntChannel * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> at(x, y));
}

unsigned int const * Imf_2_5_FlatUIntChannel_at_1(
    Imf_2_5_FlatUIntChannel const * this_
    , int x
    , int y)
{
    return &((to_cpp(this_)) -> at(x, y));
}

unsigned int * Imf_2_5_FlatUIntChannel_row(
    Imf_2_5_FlatUIntChannel * this_
    , int r)
{
    return (to_cpp(this_)) -> row(r);
}

unsigned int const * Imf_2_5_FlatUIntChannel_row_1(
    Imf_2_5_FlatUIntChannel const * this_
    , int r)
{
    return (to_cpp(this_)) -> row(r);
}
