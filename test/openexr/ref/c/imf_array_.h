#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_ArrayFloat_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_ArrayFloat;
typedef struct Imf_2_5_Array2DFloat_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_Array2DFloat;


void Imf_2_5_ArrayFloat_Array(
    Imf_2_5_ArrayFloat * this_);


void Imf_2_5_ArrayFloat_Array_1(
    Imf_2_5_ArrayFloat * this_
    , long size);


void Imf_2_5_ArrayFloat_dtor(
    Imf_2_5_ArrayFloat * this_);


float * Imf_2_5_ArrayFloat_operatorfloat_(
    Imf_2_5_ArrayFloat * this_);


float const * Imf_2_5_ArrayFloat_operatorconstfloat_(
    Imf_2_5_ArrayFloat const * this_);


void Imf_2_5_ArrayFloat_resizeErase(
    Imf_2_5_ArrayFloat * this_
    , long size);


void Imf_2_5_ArrayFloat_resizeEraseUnsafe(
    Imf_2_5_ArrayFloat * this_
    , long size);


long Imf_2_5_ArrayFloat_size(
    Imf_2_5_ArrayFloat const * this_);










void Imf_2_5_Array2DFloat_Array2D(
    Imf_2_5_Array2DFloat * this_);


void Imf_2_5_Array2DFloat_Array2D_1(
    Imf_2_5_Array2DFloat * this_
    , long sizeX
    , long sizeY);


void Imf_2_5_Array2DFloat_dtor(
    Imf_2_5_Array2DFloat * this_);


float * Imf_2_5_Array2DFloat__index(
    Imf_2_5_Array2DFloat * this_
    , long x);


float const * Imf_2_5_Array2DFloat__index_1(
    Imf_2_5_Array2DFloat const * this_
    , long x);


void Imf_2_5_Array2DFloat_resizeErase(
    Imf_2_5_Array2DFloat * this_
    , long sizeX
    , long sizeY);


void Imf_2_5_Array2DFloat_resizeEraseUnsafe(
    Imf_2_5_Array2DFloat * this_
    , long sizeX
    , long sizeY);


long Imf_2_5_Array2DFloat_height(
    Imf_2_5_Array2DFloat const * this_);


long Imf_2_5_Array2DFloat_width(
    Imf_2_5_Array2DFloat const * this_);








#ifdef __cplusplus
}
#endif
