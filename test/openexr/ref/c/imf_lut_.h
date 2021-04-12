#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Rgba_s Imf_2_5_Rgba;
typedef struct Imf_2_5_Slice_s Imf_2_5_Slice;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imath_2_5_half_s Imath_2_5_half;
typedef struct Imf_2_5_HalfLut_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_HalfLut;
typedef struct Imf_2_5_RgbaLut_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_RgbaLut;


void Imf_2_5_HalfLut_apply(
    Imf_2_5_HalfLut const * this_
    , Imath_2_5_half * data
    , int nData
    , int stride);


void Imf_2_5_HalfLut_apply_1(
    Imf_2_5_HalfLut const * this_
    , Imf_2_5_Slice const * data
    , Imath_2_5_Box2i const * dataWindow);










void Imf_2_5_RgbaLut_apply(
    Imf_2_5_RgbaLut const * this_
    , Imf_2_5_Rgba * data
    , int nData
    , int stride);


void Imf_2_5_RgbaLut_apply_1(
    Imf_2_5_RgbaLut const * this_
    , Imf_2_5_Rgba * base
    , int xStride
    , int yStride
    , Imath_2_5_Box2i const * dataWindow);








#ifdef __cplusplus
}
#endif
