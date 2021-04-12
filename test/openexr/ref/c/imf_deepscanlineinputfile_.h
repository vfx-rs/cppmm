#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imf_2_5_DeepFrameBuffer_s Imf_2_5_DeepFrameBuffer;
typedef struct Imf_2_5_DeepScanLineInputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_DeepScanLineInputFile;


void Imf_2_5_DeepScanLineInputFile_DeepScanLineInputFile(
    Imf_2_5_DeepScanLineInputFile * this_
    , char const * fileName
    , int numThreads);


void Imf_2_5_DeepScanLineInputFile_DeepScanLineInputFile_1(
    Imf_2_5_DeepScanLineInputFile * this_
    , Imf_2_5_Header const * header
    , Imf_2_5_IStream * is
    , int version
    , int numThreads);


void Imf_2_5_DeepScanLineInputFile_dtor(
    Imf_2_5_DeepScanLineInputFile * this_);


char const * Imf_2_5_DeepScanLineInputFile_fileName(
    Imf_2_5_DeepScanLineInputFile const * this_);


Imf_2_5_Header const * Imf_2_5_DeepScanLineInputFile_header(
    Imf_2_5_DeepScanLineInputFile const * this_);


int Imf_2_5_DeepScanLineInputFile_version(
    Imf_2_5_DeepScanLineInputFile const * this_);


void Imf_2_5_DeepScanLineInputFile_setFrameBuffer(
    Imf_2_5_DeepScanLineInputFile * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer);


Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepScanLineInputFile_frameBuffer(
    Imf_2_5_DeepScanLineInputFile const * this_);


_Bool Imf_2_5_DeepScanLineInputFile_isComplete(
    Imf_2_5_DeepScanLineInputFile const * this_);


void Imf_2_5_DeepScanLineInputFile_readPixels(
    Imf_2_5_DeepScanLineInputFile * this_
    , int scanLine1
    , int scanLine2);


void Imf_2_5_DeepScanLineInputFile_readPixels_1(
    Imf_2_5_DeepScanLineInputFile * this_
    , int scanLine);


void Imf_2_5_DeepScanLineInputFile_readPixels_2(
    Imf_2_5_DeepScanLineInputFile const * this_
    , char const * rawPixelData
    , Imf_2_5_DeepFrameBuffer const * frameBuffer
    , int scanLine1
    , int scanLine2);


void Imf_2_5_DeepScanLineInputFile_rawPixelData(
    Imf_2_5_DeepScanLineInputFile * this_
    , int firstScanLine
    , char * pixelData
    , unsigned long * pixelDataSize);


int Imf_2_5_DeepScanLineInputFile_firstScanLineInChunk(
    Imf_2_5_DeepScanLineInputFile const * this_
    , int y);


int Imf_2_5_DeepScanLineInputFile_lastScanLineInChunk(
    Imf_2_5_DeepScanLineInputFile const * this_
    , int y);


void Imf_2_5_DeepScanLineInputFile_readPixelSampleCounts(
    Imf_2_5_DeepScanLineInputFile * this_
    , int scanline1
    , int scanline2);


void Imf_2_5_DeepScanLineInputFile_readPixelSampleCounts_1(
    Imf_2_5_DeepScanLineInputFile * this_
    , int scanline);


void Imf_2_5_DeepScanLineInputFile_readPixelSampleCounts_2(
    Imf_2_5_DeepScanLineInputFile const * this_
    , char const * rawdata
    , Imf_2_5_DeepFrameBuffer const * frameBuffer
    , int scanLine1
    , int scanLine2);








#ifdef __cplusplus
}
#endif
