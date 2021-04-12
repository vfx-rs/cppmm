#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_DeepImageLevel_s Imf_2_5_DeepImageLevel;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imf_2_5_DeepImage_s {
    char data[104];
} __attribute__((aligned(8))) Imf_2_5_DeepImage;


int Imf_2_5_DeepImage_numLevels(
    Imf_2_5_DeepImage const * this_);


int Imf_2_5_DeepImage_numXLevels(
    Imf_2_5_DeepImage const * this_);


int Imf_2_5_DeepImage_numYLevels(
    Imf_2_5_DeepImage const * this_);


Imath_2_5_Box2i const * Imf_2_5_DeepImage_dataWindow(
    Imf_2_5_DeepImage const * this_);


Imath_2_5_Box2i const * Imf_2_5_DeepImage_dataWindowForLevel(
    Imf_2_5_DeepImage const * this_
    , int l);


Imath_2_5_Box2i const * Imf_2_5_DeepImage_dataWindowForLevel_1(
    Imf_2_5_DeepImage const * this_
    , int lx
    , int ly);


int Imf_2_5_DeepImage_levelWidth(
    Imf_2_5_DeepImage const * this_
    , int lx);


int Imf_2_5_DeepImage_levelHeight(
    Imf_2_5_DeepImage const * this_
    , int ly);


void Imf_2_5_DeepImage_resize(
    Imf_2_5_DeepImage * this_
    , Imath_2_5_Box2i const * dataWindow);


void Imf_2_5_DeepImage_shiftPixels(
    Imf_2_5_DeepImage * this_
    , int dx
    , int dy);


void Imf_2_5_DeepImage_clearChannels(
    Imf_2_5_DeepImage * this_);


void Imf_2_5_DeepImage_DeepImage(
    Imf_2_5_DeepImage * this_);


void Imf_2_5_DeepImage_dtor(
    Imf_2_5_DeepImage * this_);


Imf_2_5_DeepImageLevel * Imf_2_5_DeepImage_level(
    Imf_2_5_DeepImage * this_
    , int l);


Imf_2_5_DeepImageLevel const * Imf_2_5_DeepImage_level_1(
    Imf_2_5_DeepImage const * this_
    , int l);


Imf_2_5_DeepImageLevel * Imf_2_5_DeepImage_level_2(
    Imf_2_5_DeepImage * this_
    , int lx
    , int ly);


Imf_2_5_DeepImageLevel const * Imf_2_5_DeepImage_level_3(
    Imf_2_5_DeepImage const * this_
    , int lx
    , int ly);








#ifdef __cplusplus
}
#endif
