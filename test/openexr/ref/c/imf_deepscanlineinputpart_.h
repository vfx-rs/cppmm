#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_MultiPartInputFile_s Imf_2_5_MultiPartInputFile;
typedef struct Imf_2_5_DeepFrameBuffer_s Imf_2_5_DeepFrameBuffer;
typedef struct Imf_2_5_DeepScanLineInputPart_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_DeepScanLineInputPart;


void Imf_2_5_DeepScanLineInputPart_DeepScanLineInputPart(
    Imf_2_5_DeepScanLineInputPart * this_
    , Imf_2_5_MultiPartInputFile * file
    , int partNumber);


char const * Imf_2_5_DeepScanLineInputPart_fileName(
    Imf_2_5_DeepScanLineInputPart const * this_);


Imf_2_5_Header const * Imf_2_5_DeepScanLineInputPart_header(
    Imf_2_5_DeepScanLineInputPart const * this_);


int Imf_2_5_DeepScanLineInputPart_version(
    Imf_2_5_DeepScanLineInputPart const * this_);


void Imf_2_5_DeepScanLineInputPart_setFrameBuffer(
    Imf_2_5_DeepScanLineInputPart * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer);


Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepScanLineInputPart_frameBuffer(
    Imf_2_5_DeepScanLineInputPart const * this_);


_Bool Imf_2_5_DeepScanLineInputPart_isComplete(
    Imf_2_5_DeepScanLineInputPart const * this_);


void Imf_2_5_DeepScanLineInputPart_readPixels(
    Imf_2_5_DeepScanLineInputPart * this_
    , int scanLine1
    , int scanLine2);


void Imf_2_5_DeepScanLineInputPart_readPixels_1(
    Imf_2_5_DeepScanLineInputPart * this_
    , int scanLine);


void Imf_2_5_DeepScanLineInputPart_readPixels_2(
    Imf_2_5_DeepScanLineInputPart const * this_
    , char const * rawPixelData
    , Imf_2_5_DeepFrameBuffer const * frameBuffer
    , int scanLine1
    , int scanLine2);


void Imf_2_5_DeepScanLineInputPart_rawPixelData(
    Imf_2_5_DeepScanLineInputPart * this_
    , int firstScanLine
    , char * pixelData
    , unsigned long * pixelDataSize);


void Imf_2_5_DeepScanLineInputPart_readPixelSampleCounts(
    Imf_2_5_DeepScanLineInputPart * this_
    , int scanline1
    , int scanline2);


void Imf_2_5_DeepScanLineInputPart_readPixelSampleCounts_1(
    Imf_2_5_DeepScanLineInputPart * this_
    , int scanline);


void Imf_2_5_DeepScanLineInputPart_readPixelSampleCounts_2(
    Imf_2_5_DeepScanLineInputPart const * this_
    , char const * rawdata
    , Imf_2_5_DeepFrameBuffer const * frameBuffer
    , int scanLine1
    , int scanLine2);


int Imf_2_5_DeepScanLineInputPart_firstScanLineInChunk(
    Imf_2_5_DeepScanLineInputPart const * this_
    , int y);


int Imf_2_5_DeepScanLineInputPart_lastScanLineInChunk(
    Imf_2_5_DeepScanLineInputPart const * this_
    , int y);








#ifdef __cplusplus
}
#endif
