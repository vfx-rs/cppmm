#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imf_2_5_InputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_InputFile;


void Imf_2_5_InputFile_InputFile(
    Imf_2_5_InputFile * this_
    , char const * fileName
    , int numThreads);


void Imf_2_5_InputFile_InputFile_1(
    Imf_2_5_InputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads);


void Imf_2_5_InputFile_dtor(
    Imf_2_5_InputFile * this_);


char const * Imf_2_5_InputFile_fileName(
    Imf_2_5_InputFile const * this_);


Imf_2_5_Header const * Imf_2_5_InputFile_header(
    Imf_2_5_InputFile const * this_);


int Imf_2_5_InputFile_version(
    Imf_2_5_InputFile const * this_);


void Imf_2_5_InputFile_setFrameBuffer(
    Imf_2_5_InputFile * this_
    , Imf_2_5_FrameBuffer const * frameBuffer);


Imf_2_5_FrameBuffer const * Imf_2_5_InputFile_frameBuffer(
    Imf_2_5_InputFile const * this_);


_Bool Imf_2_5_InputFile_isComplete(
    Imf_2_5_InputFile const * this_);


_Bool Imf_2_5_InputFile_isOptimizationEnabled(
    Imf_2_5_InputFile const * this_);


void Imf_2_5_InputFile_readPixels(
    Imf_2_5_InputFile * this_
    , int scanLine1
    , int scanLine2);


void Imf_2_5_InputFile_readPixels_1(
    Imf_2_5_InputFile * this_
    , int scanLine);


void Imf_2_5_InputFile_rawPixelData(
    Imf_2_5_InputFile * this_
    , int firstScanLine
    , char const * * pixelData
    , int * pixelDataSize);


void Imf_2_5_InputFile_rawPixelDataToBuffer(
    Imf_2_5_InputFile const * this_
    , int scanLine
    , char * pixelData
    , int * pixelDataSize);


void Imf_2_5_InputFile_rawTileData(
    Imf_2_5_InputFile * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char const * * pixelData
    , int * pixelDataSize);








#ifdef __cplusplus
}
#endif
