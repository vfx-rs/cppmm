#pragma once
#include <imath_box_.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Compressor_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_Compressor;


void Imf_2_5_Compressor_dtor(
    Imf_2_5_Compressor * this_);


int Imf_2_5_Compressor_numScanLines(
    Imf_2_5_Compressor const * this_);


int Imf_2_5_Compressor_compress(
    Imf_2_5_Compressor * this_
    , char const * inPtr
    , int inSize
    , int minY
    , char const * * outPtr);


int Imf_2_5_Compressor_compressTile(
    Imf_2_5_Compressor * this_
    , char const * inPtr
    , int inSize
    , Imath_2_5_Box2i range
    , char const * * outPtr);


int Imf_2_5_Compressor_uncompress(
    Imf_2_5_Compressor * this_
    , char const * inPtr
    , int inSize
    , int minY
    , char const * * outPtr);


int Imf_2_5_Compressor_uncompressTile(
    Imf_2_5_Compressor * this_
    , char const * inPtr
    , int inSize
    , Imath_2_5_Box2i range
    , char const * * outPtr);








#ifdef __cplusplus
}
#endif
