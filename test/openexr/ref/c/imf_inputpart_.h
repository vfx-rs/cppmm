#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_MultiPartInputFile_s Imf_2_5_MultiPartInputFile;
typedef struct Imf_2_5_InputPart_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_InputPart;


void Imf_2_5_InputPart_InputPart(
    Imf_2_5_InputPart * this_
    , Imf_2_5_MultiPartInputFile * multiPartFile
    , int partNumber);


char const * Imf_2_5_InputPart_fileName(
    Imf_2_5_InputPart const * this_);


Imf_2_5_Header const * Imf_2_5_InputPart_header(
    Imf_2_5_InputPart const * this_);


int Imf_2_5_InputPart_version(
    Imf_2_5_InputPart const * this_);


void Imf_2_5_InputPart_setFrameBuffer(
    Imf_2_5_InputPart * this_
    , Imf_2_5_FrameBuffer const * frameBuffer);


Imf_2_5_FrameBuffer const * Imf_2_5_InputPart_frameBuffer(
    Imf_2_5_InputPart const * this_);


_Bool Imf_2_5_InputPart_isComplete(
    Imf_2_5_InputPart const * this_);


_Bool Imf_2_5_InputPart_isOptimizationEnabled(
    Imf_2_5_InputPart const * this_);


void Imf_2_5_InputPart_readPixels(
    Imf_2_5_InputPart * this_
    , int scanLine1
    , int scanLine2);


void Imf_2_5_InputPart_readPixels_1(
    Imf_2_5_InputPart * this_
    , int scanLine);


void Imf_2_5_InputPart_rawPixelData(
    Imf_2_5_InputPart * this_
    , int firstScanLine
    , char const * * pixelData
    , int * pixelDataSize);


void Imf_2_5_InputPart_rawPixelDataToBuffer(
    Imf_2_5_InputPart const * this_
    , int scanLine
    , char * pixelData
    , int * pixelDataSize);


void Imf_2_5_InputPart_rawTileData(
    Imf_2_5_InputPart * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char const * * pixelData
    , int * pixelDataSize);








#ifdef __cplusplus
}
#endif
