#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_ImageLevel_s Imf_2_5_ImageLevel;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imf_2_5_Image_s {
    char data[104];
} __attribute__((aligned(8))) Imf_2_5_Image;


void Imf_2_5_Image_dtor(
    Imf_2_5_Image * this_);


int Imf_2_5_Image_numLevels(
    Imf_2_5_Image const * this_);


int Imf_2_5_Image_numXLevels(
    Imf_2_5_Image const * this_);


int Imf_2_5_Image_numYLevels(
    Imf_2_5_Image const * this_);


Imath_2_5_Box2i const * Imf_2_5_Image_dataWindow(
    Imf_2_5_Image const * this_);


Imath_2_5_Box2i const * Imf_2_5_Image_dataWindowForLevel(
    Imf_2_5_Image const * this_
    , int l);


Imath_2_5_Box2i const * Imf_2_5_Image_dataWindowForLevel_1(
    Imf_2_5_Image const * this_
    , int lx
    , int ly);


int Imf_2_5_Image_levelWidth(
    Imf_2_5_Image const * this_
    , int lx);


int Imf_2_5_Image_levelHeight(
    Imf_2_5_Image const * this_
    , int ly);


void Imf_2_5_Image_resize(
    Imf_2_5_Image * this_
    , Imath_2_5_Box2i const * dataWindow);


void Imf_2_5_Image_shiftPixels(
    Imf_2_5_Image * this_
    , int dx
    , int dy);


void Imf_2_5_Image_clearChannels(
    Imf_2_5_Image * this_);


Imf_2_5_ImageLevel * Imf_2_5_Image_level(
    Imf_2_5_Image * this_
    , int l);


Imf_2_5_ImageLevel const * Imf_2_5_Image_level_1(
    Imf_2_5_Image const * this_
    , int l);


Imf_2_5_ImageLevel * Imf_2_5_Image_level_2(
    Imf_2_5_Image * this_
    , int lx
    , int ly);


Imf_2_5_ImageLevel const * Imf_2_5_Image_level_3(
    Imf_2_5_Image const * this_
    , int lx
    , int ly);








#ifdef __cplusplus
}
#endif
