#pragma once
#include <imf_framebuffer_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_ImageLevel_s Imf_2_5_ImageLevel;
typedef struct Imf_2_5_FlatImageLevel_s Imf_2_5_FlatImageLevel;
typedef struct Imath_2_5_half_s Imath_2_5_half;
typedef struct Imf_2_5_FlatImageChannel_s {
    char data[48];
} __attribute__((aligned(8))) Imf_2_5_FlatImageChannel;
typedef struct Imf_2_5_FlatHalfChannel_s {
    char data[64];
} __attribute__((aligned(8))) Imf_2_5_FlatHalfChannel;
typedef struct Imf_2_5_FlatFloatChannel_s {
    char data[64];
} __attribute__((aligned(8))) Imf_2_5_FlatFloatChannel;
typedef struct Imf_2_5_FlatUIntChannel_s {
    char data[64];
} __attribute__((aligned(8))) Imf_2_5_FlatUIntChannel;


int Imf_2_5_FlatImageChannel_xSampling(
    Imf_2_5_FlatImageChannel const * this_);


int Imf_2_5_FlatImageChannel_ySampling(
    Imf_2_5_FlatImageChannel const * this_);


_Bool Imf_2_5_FlatImageChannel_pLinear(
    Imf_2_5_FlatImageChannel const * this_);


int Imf_2_5_FlatImageChannel_pixelsPerRow(
    Imf_2_5_FlatImageChannel const * this_);


int Imf_2_5_FlatImageChannel_pixelsPerColumn(
    Imf_2_5_FlatImageChannel const * this_);


unsigned long Imf_2_5_FlatImageChannel_numPixels(
    Imf_2_5_FlatImageChannel const * this_);


Imf_2_5_ImageLevel * Imf_2_5_FlatImageChannel_level(
    Imf_2_5_FlatImageChannel * this_);


Imf_2_5_ImageLevel const * Imf_2_5_FlatImageChannel_level_1(
    Imf_2_5_FlatImageChannel const * this_);


Imf_2_5_Slice Imf_2_5_FlatImageChannel_slice(
    Imf_2_5_FlatImageChannel const * this_);


Imf_2_5_FlatImageLevel * Imf_2_5_FlatImageChannel_flatLevel(
    Imf_2_5_FlatImageChannel * this_);


Imf_2_5_FlatImageLevel const * Imf_2_5_FlatImageChannel_flatLevel_1(
    Imf_2_5_FlatImageChannel const * this_);










int Imf_2_5_FlatHalfChannel_xSampling(
    Imf_2_5_FlatHalfChannel const * this_);


int Imf_2_5_FlatHalfChannel_ySampling(
    Imf_2_5_FlatHalfChannel const * this_);


_Bool Imf_2_5_FlatHalfChannel_pLinear(
    Imf_2_5_FlatHalfChannel const * this_);


int Imf_2_5_FlatHalfChannel_pixelsPerRow(
    Imf_2_5_FlatHalfChannel const * this_);


int Imf_2_5_FlatHalfChannel_pixelsPerColumn(
    Imf_2_5_FlatHalfChannel const * this_);


unsigned long Imf_2_5_FlatHalfChannel_numPixels(
    Imf_2_5_FlatHalfChannel const * this_);


Imf_2_5_ImageLevel * Imf_2_5_FlatHalfChannel_level(
    Imf_2_5_FlatHalfChannel * this_);


Imf_2_5_ImageLevel const * Imf_2_5_FlatHalfChannel_level_1(
    Imf_2_5_FlatHalfChannel const * this_);


Imf_2_5_Slice Imf_2_5_FlatHalfChannel_slice(
    Imf_2_5_FlatHalfChannel const * this_);


Imf_2_5_FlatImageLevel * Imf_2_5_FlatHalfChannel_flatLevel(
    Imf_2_5_FlatHalfChannel * this_);


Imf_2_5_FlatImageLevel const * Imf_2_5_FlatHalfChannel_flatLevel_1(
    Imf_2_5_FlatHalfChannel const * this_);


Imath_2_5_half * Imf_2_5_FlatHalfChannel_operator()(
    Imf_2_5_FlatHalfChannel * this_
    , int x
    , int y);


Imath_2_5_half const * Imf_2_5_FlatHalfChannel_operator()_1(
    Imf_2_5_FlatHalfChannel const * this_
    , int x
    , int y);


Imath_2_5_half * Imf_2_5_FlatHalfChannel_at(
    Imf_2_5_FlatHalfChannel * this_
    , int x
    , int y);


Imath_2_5_half const * Imf_2_5_FlatHalfChannel_at_1(
    Imf_2_5_FlatHalfChannel const * this_
    , int x
    , int y);


Imath_2_5_half * Imf_2_5_FlatHalfChannel_row(
    Imf_2_5_FlatHalfChannel * this_
    , int r);


Imath_2_5_half const * Imf_2_5_FlatHalfChannel_row_1(
    Imf_2_5_FlatHalfChannel const * this_
    , int r);










int Imf_2_5_FlatFloatChannel_xSampling(
    Imf_2_5_FlatFloatChannel const * this_);


int Imf_2_5_FlatFloatChannel_ySampling(
    Imf_2_5_FlatFloatChannel const * this_);


_Bool Imf_2_5_FlatFloatChannel_pLinear(
    Imf_2_5_FlatFloatChannel const * this_);


int Imf_2_5_FlatFloatChannel_pixelsPerRow(
    Imf_2_5_FlatFloatChannel const * this_);


int Imf_2_5_FlatFloatChannel_pixelsPerColumn(
    Imf_2_5_FlatFloatChannel const * this_);


unsigned long Imf_2_5_FlatFloatChannel_numPixels(
    Imf_2_5_FlatFloatChannel const * this_);


Imf_2_5_ImageLevel * Imf_2_5_FlatFloatChannel_level(
    Imf_2_5_FlatFloatChannel * this_);


Imf_2_5_ImageLevel const * Imf_2_5_FlatFloatChannel_level_1(
    Imf_2_5_FlatFloatChannel const * this_);


Imf_2_5_Slice Imf_2_5_FlatFloatChannel_slice(
    Imf_2_5_FlatFloatChannel const * this_);


Imf_2_5_FlatImageLevel * Imf_2_5_FlatFloatChannel_flatLevel(
    Imf_2_5_FlatFloatChannel * this_);


Imf_2_5_FlatImageLevel const * Imf_2_5_FlatFloatChannel_flatLevel_1(
    Imf_2_5_FlatFloatChannel const * this_);


float * Imf_2_5_FlatFloatChannel_operator()(
    Imf_2_5_FlatFloatChannel * this_
    , int x
    , int y);


float const * Imf_2_5_FlatFloatChannel_operator()_1(
    Imf_2_5_FlatFloatChannel const * this_
    , int x
    , int y);


float * Imf_2_5_FlatFloatChannel_at(
    Imf_2_5_FlatFloatChannel * this_
    , int x
    , int y);


float const * Imf_2_5_FlatFloatChannel_at_1(
    Imf_2_5_FlatFloatChannel const * this_
    , int x
    , int y);


float * Imf_2_5_FlatFloatChannel_row(
    Imf_2_5_FlatFloatChannel * this_
    , int r);


float const * Imf_2_5_FlatFloatChannel_row_1(
    Imf_2_5_FlatFloatChannel const * this_
    , int r);










int Imf_2_5_FlatUIntChannel_xSampling(
    Imf_2_5_FlatUIntChannel const * this_);


int Imf_2_5_FlatUIntChannel_ySampling(
    Imf_2_5_FlatUIntChannel const * this_);


_Bool Imf_2_5_FlatUIntChannel_pLinear(
    Imf_2_5_FlatUIntChannel const * this_);


int Imf_2_5_FlatUIntChannel_pixelsPerRow(
    Imf_2_5_FlatUIntChannel const * this_);


int Imf_2_5_FlatUIntChannel_pixelsPerColumn(
    Imf_2_5_FlatUIntChannel const * this_);


unsigned long Imf_2_5_FlatUIntChannel_numPixels(
    Imf_2_5_FlatUIntChannel const * this_);


Imf_2_5_ImageLevel * Imf_2_5_FlatUIntChannel_level(
    Imf_2_5_FlatUIntChannel * this_);


Imf_2_5_ImageLevel const * Imf_2_5_FlatUIntChannel_level_1(
    Imf_2_5_FlatUIntChannel const * this_);


Imf_2_5_Slice Imf_2_5_FlatUIntChannel_slice(
    Imf_2_5_FlatUIntChannel const * this_);


Imf_2_5_FlatImageLevel * Imf_2_5_FlatUIntChannel_flatLevel(
    Imf_2_5_FlatUIntChannel * this_);


Imf_2_5_FlatImageLevel const * Imf_2_5_FlatUIntChannel_flatLevel_1(
    Imf_2_5_FlatUIntChannel const * this_);


unsigned int * Imf_2_5_FlatUIntChannel_operator()(
    Imf_2_5_FlatUIntChannel * this_
    , int x
    , int y);


unsigned int const * Imf_2_5_FlatUIntChannel_operator()_1(
    Imf_2_5_FlatUIntChannel const * this_
    , int x
    , int y);


unsigned int * Imf_2_5_FlatUIntChannel_at(
    Imf_2_5_FlatUIntChannel * this_
    , int x
    , int y);


unsigned int const * Imf_2_5_FlatUIntChannel_at_1(
    Imf_2_5_FlatUIntChannel const * this_
    , int x
    , int y);


unsigned int * Imf_2_5_FlatUIntChannel_row(
    Imf_2_5_FlatUIntChannel * this_
    , int r);


unsigned int const * Imf_2_5_FlatUIntChannel_row_1(
    Imf_2_5_FlatUIntChannel const * this_
    , int r);








#ifdef __cplusplus
}
#endif
