#pragma once
#include <imf_channellist_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_ImageLevel_s Imf_2_5_ImageLevel;
typedef struct Imf_2_5_ImageChannel_s {
    char data[48];
} __attribute__((aligned(8))) Imf_2_5_ImageChannel;


Imf_2_5_Channel Imf_2_5_ImageChannel_channel(
    Imf_2_5_ImageChannel const * this_);


int Imf_2_5_ImageChannel_xSampling(
    Imf_2_5_ImageChannel const * this_);


int Imf_2_5_ImageChannel_ySampling(
    Imf_2_5_ImageChannel const * this_);


_Bool Imf_2_5_ImageChannel_pLinear(
    Imf_2_5_ImageChannel const * this_);


int Imf_2_5_ImageChannel_pixelsPerRow(
    Imf_2_5_ImageChannel const * this_);


int Imf_2_5_ImageChannel_pixelsPerColumn(
    Imf_2_5_ImageChannel const * this_);


unsigned long Imf_2_5_ImageChannel_numPixels(
    Imf_2_5_ImageChannel const * this_);


Imf_2_5_ImageLevel * Imf_2_5_ImageChannel_level(
    Imf_2_5_ImageChannel * this_);


Imf_2_5_ImageLevel const * Imf_2_5_ImageChannel_level_1(
    Imf_2_5_ImageChannel const * this_);








#ifdef __cplusplus
}
#endif
