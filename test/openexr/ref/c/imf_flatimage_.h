#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FlatImageLevel_s Imf_2_5_FlatImageLevel;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imf_2_5_FlatImage_s {
    char data[104];
} __attribute__((aligned(8))) Imf_2_5_FlatImage;


int Imf_2_5_FlatImage_numLevels(
    Imf_2_5_FlatImage const * this_);


int Imf_2_5_FlatImage_numXLevels(
    Imf_2_5_FlatImage const * this_);


int Imf_2_5_FlatImage_numYLevels(
    Imf_2_5_FlatImage const * this_);


Imath_2_5_Box2i const * Imf_2_5_FlatImage_dataWindow(
    Imf_2_5_FlatImage const * this_);


Imath_2_5_Box2i const * Imf_2_5_FlatImage_dataWindowForLevel(
    Imf_2_5_FlatImage const * this_
    , int l);


Imath_2_5_Box2i const * Imf_2_5_FlatImage_dataWindowForLevel_1(
    Imf_2_5_FlatImage const * this_
    , int lx
    , int ly);


int Imf_2_5_FlatImage_levelWidth(
    Imf_2_5_FlatImage const * this_
    , int lx);


int Imf_2_5_FlatImage_levelHeight(
    Imf_2_5_FlatImage const * this_
    , int ly);


void Imf_2_5_FlatImage_resize(
    Imf_2_5_FlatImage * this_
    , Imath_2_5_Box2i const * dataWindow);


void Imf_2_5_FlatImage_shiftPixels(
    Imf_2_5_FlatImage * this_
    , int dx
    , int dy);


void Imf_2_5_FlatImage_clearChannels(
    Imf_2_5_FlatImage * this_);


void Imf_2_5_FlatImage_FlatImage(
    Imf_2_5_FlatImage * this_);


void Imf_2_5_FlatImage_dtor(
    Imf_2_5_FlatImage * this_);


Imf_2_5_FlatImageLevel * Imf_2_5_FlatImage_level(
    Imf_2_5_FlatImage * this_
    , int l);


Imf_2_5_FlatImageLevel const * Imf_2_5_FlatImage_level_1(
    Imf_2_5_FlatImage const * this_
    , int l);


Imf_2_5_FlatImageLevel * Imf_2_5_FlatImage_level_2(
    Imf_2_5_FlatImage * this_
    , int lx
    , int ly);


Imf_2_5_FlatImageLevel const * Imf_2_5_FlatImage_level_3(
    Imf_2_5_FlatImage const * this_
    , int lx
    , int ly);








#ifdef __cplusplus
}
#endif
