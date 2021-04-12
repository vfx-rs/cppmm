#pragma once
#include <imf_channellist_.h>
#include <imf_deepframebuffer_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_SampleCountChannel_s Imf_2_5_SampleCountChannel;
typedef struct Imf_2_5_DeepImageLevel_s Imf_2_5_DeepImageLevel;
typedef struct Imath_2_5_half_s Imath_2_5_half;
typedef struct Imf_2_5_DeepImageChannel_s {
    char data[48];
} __attribute__((aligned(8))) Imf_2_5_DeepImageChannel;
typedef struct Imf_2_5_DeepHalfChannel_s {
    char data[72];
} __attribute__((aligned(8))) Imf_2_5_DeepHalfChannel;
typedef struct Imf_2_5_DeepFloatChannel_s {
    char data[72];
} __attribute__((aligned(8))) Imf_2_5_DeepFloatChannel;
typedef struct Imf_2_5_DeepUIntChannel_s {
    char data[72];
} __attribute__((aligned(8))) Imf_2_5_DeepUIntChannel;


Imf_2_5_Channel Imf_2_5_DeepImageChannel_channel(
    Imf_2_5_DeepImageChannel const * this_);


int Imf_2_5_DeepImageChannel_xSampling(
    Imf_2_5_DeepImageChannel const * this_);


int Imf_2_5_DeepImageChannel_ySampling(
    Imf_2_5_DeepImageChannel const * this_);


_Bool Imf_2_5_DeepImageChannel_pLinear(
    Imf_2_5_DeepImageChannel const * this_);


int Imf_2_5_DeepImageChannel_pixelsPerRow(
    Imf_2_5_DeepImageChannel const * this_);


int Imf_2_5_DeepImageChannel_pixelsPerColumn(
    Imf_2_5_DeepImageChannel const * this_);


unsigned long Imf_2_5_DeepImageChannel_numPixels(
    Imf_2_5_DeepImageChannel const * this_);


Imf_2_5_DeepSlice Imf_2_5_DeepImageChannel_slice(
    Imf_2_5_DeepImageChannel const * this_);


Imf_2_5_DeepImageLevel * Imf_2_5_DeepImageChannel_deepLevel(
    Imf_2_5_DeepImageChannel * this_);


Imf_2_5_DeepImageLevel const * Imf_2_5_DeepImageChannel_deepLevel_1(
    Imf_2_5_DeepImageChannel const * this_);


Imf_2_5_SampleCountChannel * Imf_2_5_DeepImageChannel_sampleCounts(
    Imf_2_5_DeepImageChannel * this_);


Imf_2_5_SampleCountChannel const * Imf_2_5_DeepImageChannel_sampleCounts_1(
    Imf_2_5_DeepImageChannel const * this_);










Imf_2_5_Channel Imf_2_5_DeepHalfChannel_channel(
    Imf_2_5_DeepHalfChannel const * this_);


int Imf_2_5_DeepHalfChannel_xSampling(
    Imf_2_5_DeepHalfChannel const * this_);


int Imf_2_5_DeepHalfChannel_ySampling(
    Imf_2_5_DeepHalfChannel const * this_);


_Bool Imf_2_5_DeepHalfChannel_pLinear(
    Imf_2_5_DeepHalfChannel const * this_);


int Imf_2_5_DeepHalfChannel_pixelsPerRow(
    Imf_2_5_DeepHalfChannel const * this_);


int Imf_2_5_DeepHalfChannel_pixelsPerColumn(
    Imf_2_5_DeepHalfChannel const * this_);


unsigned long Imf_2_5_DeepHalfChannel_numPixels(
    Imf_2_5_DeepHalfChannel const * this_);


Imf_2_5_DeepSlice Imf_2_5_DeepHalfChannel_slice(
    Imf_2_5_DeepHalfChannel const * this_);


Imath_2_5_half * Imf_2_5_DeepHalfChannel_operator()(
    Imf_2_5_DeepHalfChannel * this_
    , int x
    , int y);


Imath_2_5_half const * Imf_2_5_DeepHalfChannel_operator()_1(
    Imf_2_5_DeepHalfChannel const * this_
    , int x
    , int y);


Imath_2_5_half * Imf_2_5_DeepHalfChannel_at(
    Imf_2_5_DeepHalfChannel * this_
    , int x
    , int y);


Imath_2_5_half const * Imf_2_5_DeepHalfChannel_at_1(
    Imf_2_5_DeepHalfChannel const * this_
    , int x
    , int y);


Imath_2_5_half * * Imf_2_5_DeepHalfChannel_row(
    Imf_2_5_DeepHalfChannel * this_
    , int r);


Imath_2_5_half const * * Imf_2_5_DeepHalfChannel_row_1(
    Imf_2_5_DeepHalfChannel const * this_
    , int r);










Imf_2_5_Channel Imf_2_5_DeepFloatChannel_channel(
    Imf_2_5_DeepFloatChannel const * this_);


int Imf_2_5_DeepFloatChannel_xSampling(
    Imf_2_5_DeepFloatChannel const * this_);


int Imf_2_5_DeepFloatChannel_ySampling(
    Imf_2_5_DeepFloatChannel const * this_);


_Bool Imf_2_5_DeepFloatChannel_pLinear(
    Imf_2_5_DeepFloatChannel const * this_);


int Imf_2_5_DeepFloatChannel_pixelsPerRow(
    Imf_2_5_DeepFloatChannel const * this_);


int Imf_2_5_DeepFloatChannel_pixelsPerColumn(
    Imf_2_5_DeepFloatChannel const * this_);


unsigned long Imf_2_5_DeepFloatChannel_numPixels(
    Imf_2_5_DeepFloatChannel const * this_);


Imf_2_5_DeepSlice Imf_2_5_DeepFloatChannel_slice(
    Imf_2_5_DeepFloatChannel const * this_);


float * Imf_2_5_DeepFloatChannel_operator()(
    Imf_2_5_DeepFloatChannel * this_
    , int x
    , int y);


float const * Imf_2_5_DeepFloatChannel_operator()_1(
    Imf_2_5_DeepFloatChannel const * this_
    , int x
    , int y);


float * Imf_2_5_DeepFloatChannel_at(
    Imf_2_5_DeepFloatChannel * this_
    , int x
    , int y);


float const * Imf_2_5_DeepFloatChannel_at_1(
    Imf_2_5_DeepFloatChannel const * this_
    , int x
    , int y);


float * * Imf_2_5_DeepFloatChannel_row(
    Imf_2_5_DeepFloatChannel * this_
    , int r);


float const * * Imf_2_5_DeepFloatChannel_row_1(
    Imf_2_5_DeepFloatChannel const * this_
    , int r);










Imf_2_5_Channel Imf_2_5_DeepUIntChannel_channel(
    Imf_2_5_DeepUIntChannel const * this_);


int Imf_2_5_DeepUIntChannel_xSampling(
    Imf_2_5_DeepUIntChannel const * this_);


int Imf_2_5_DeepUIntChannel_ySampling(
    Imf_2_5_DeepUIntChannel const * this_);


_Bool Imf_2_5_DeepUIntChannel_pLinear(
    Imf_2_5_DeepUIntChannel const * this_);


int Imf_2_5_DeepUIntChannel_pixelsPerRow(
    Imf_2_5_DeepUIntChannel const * this_);


int Imf_2_5_DeepUIntChannel_pixelsPerColumn(
    Imf_2_5_DeepUIntChannel const * this_);


unsigned long Imf_2_5_DeepUIntChannel_numPixels(
    Imf_2_5_DeepUIntChannel const * this_);


Imf_2_5_DeepSlice Imf_2_5_DeepUIntChannel_slice(
    Imf_2_5_DeepUIntChannel const * this_);


unsigned int * Imf_2_5_DeepUIntChannel_operator()(
    Imf_2_5_DeepUIntChannel * this_
    , int x
    , int y);


unsigned int const * Imf_2_5_DeepUIntChannel_operator()_1(
    Imf_2_5_DeepUIntChannel const * this_
    , int x
    , int y);


unsigned int * Imf_2_5_DeepUIntChannel_at(
    Imf_2_5_DeepUIntChannel * this_
    , int x
    , int y);


unsigned int const * Imf_2_5_DeepUIntChannel_at_1(
    Imf_2_5_DeepUIntChannel const * this_
    , int x
    , int y);


unsigned int * * Imf_2_5_DeepUIntChannel_row(
    Imf_2_5_DeepUIntChannel * this_
    , int r);


unsigned int const * * Imf_2_5_DeepUIntChannel_row_1(
    Imf_2_5_DeepUIntChannel const * this_
    , int r);








#ifdef __cplusplus
}
#endif
