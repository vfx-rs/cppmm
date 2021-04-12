#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_PreviewRgba_s {
    char data[4];
} __attribute__((aligned(1))) Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_PreviewImage_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_PreviewImage;


void Imf_2_5_PreviewRgba_PreviewRgba(
    Imf_2_5_PreviewRgba * this_
    , unsigned char r
    , unsigned char g
    , unsigned char b
    , unsigned char a);










void Imf_2_5_PreviewImage_PreviewImage(
    Imf_2_5_PreviewImage * this_
    , unsigned int width
    , unsigned int height
    , Imf_2_5_PreviewRgba const * pixels);


void Imf_2_5_PreviewImage_PreviewImage_1(
    Imf_2_5_PreviewImage * this_
    , Imf_2_5_PreviewImage const * other);


void Imf_2_5_PreviewImage_dtor(
    Imf_2_5_PreviewImage * this_);


Imf_2_5_PreviewImage * Imf_2_5_PreviewImage__assign(
    Imf_2_5_PreviewImage * this_
    , Imf_2_5_PreviewImage const * other);


unsigned int Imf_2_5_PreviewImage_width(
    Imf_2_5_PreviewImage const * this_);


unsigned int Imf_2_5_PreviewImage_height(
    Imf_2_5_PreviewImage const * this_);


Imf_2_5_PreviewRgba * Imf_2_5_PreviewImage_pixels(
    Imf_2_5_PreviewImage * this_);


Imf_2_5_PreviewRgba const * Imf_2_5_PreviewImage_pixels_1(
    Imf_2_5_PreviewImage const * this_);


Imf_2_5_PreviewRgba * Imf_2_5_PreviewImage_pixel(
    Imf_2_5_PreviewImage * this_
    , unsigned int x
    , unsigned int y);


Imf_2_5_PreviewRgba const * Imf_2_5_PreviewImage_pixel_1(
    Imf_2_5_PreviewImage const * this_
    , unsigned int x
    , unsigned int y);









#ifdef __cplusplus
}
#endif
