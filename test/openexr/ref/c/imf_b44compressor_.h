#pragma once
#include <imath_box_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_B44Compressor_s {
    char data[88];
} __attribute__((aligned(8))) Imf_2_5_B44Compressor;


int Imf_2_5_B44Compressor_numScanLines(
    Imf_2_5_B44Compressor const * this_);


int Imf_2_5_B44Compressor_compress(
    Imf_2_5_B44Compressor * this_
    , char const * inPtr
    , int inSize
    , int minY
    , char const * * outPtr);


int Imf_2_5_B44Compressor_compressTile(
    Imf_2_5_B44Compressor * this_
    , char const * inPtr
    , int inSize
    , Imath_2_5_Box2i range
    , char const * * outPtr);


int Imf_2_5_B44Compressor_uncompress(
    Imf_2_5_B44Compressor * this_
    , char const * inPtr
    , int inSize
    , int minY
    , char const * * outPtr);


int Imf_2_5_B44Compressor_uncompressTile(
    Imf_2_5_B44Compressor * this_
    , char const * inPtr
    , int inSize
    , Imath_2_5_Box2i range
    , char const * * outPtr);


void Imf_2_5_B44Compressor_B44Compressor(
    Imf_2_5_B44Compressor * this_
    , Imf_2_5_Header const * hdr
    , unsigned long maxScanLineSize
    , unsigned long numScanLines
    , _Bool optFlatFields);


void Imf_2_5_B44Compressor_dtor(
    Imf_2_5_B44Compressor * this_);








#ifdef __cplusplus
}
#endif
