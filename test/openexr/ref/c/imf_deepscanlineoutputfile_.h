#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_DeepScanLineInputPart_s Imf_2_5_DeepScanLineInputPart;
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_DeepScanLineInputFile_s Imf_2_5_DeepScanLineInputFile;
typedef struct Imf_2_5_DeepFrameBuffer_s Imf_2_5_DeepFrameBuffer;
typedef struct Imf_2_5_DeepScanLineOutputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_DeepScanLineOutputFile;


void Imf_2_5_DeepScanLineOutputFile_DeepScanLineOutputFile(
    Imf_2_5_DeepScanLineOutputFile * this_
    , char const * fileName
    , Imf_2_5_Header const * header
    , int numThreads);


void Imf_2_5_DeepScanLineOutputFile_DeepScanLineOutputFile_1(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_OStream * os
    , Imf_2_5_Header const * header
    , int numThreads);


void Imf_2_5_DeepScanLineOutputFile_dtor(
    Imf_2_5_DeepScanLineOutputFile * this_);


char const * Imf_2_5_DeepScanLineOutputFile_fileName(
    Imf_2_5_DeepScanLineOutputFile const * this_);


Imf_2_5_Header const * Imf_2_5_DeepScanLineOutputFile_header(
    Imf_2_5_DeepScanLineOutputFile const * this_);


void Imf_2_5_DeepScanLineOutputFile_setFrameBuffer(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer);


Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepScanLineOutputFile_frameBuffer(
    Imf_2_5_DeepScanLineOutputFile const * this_);


void Imf_2_5_DeepScanLineOutputFile_writePixels(
    Imf_2_5_DeepScanLineOutputFile * this_
    , int numScanLines);


int Imf_2_5_DeepScanLineOutputFile_currentScanLine(
    Imf_2_5_DeepScanLineOutputFile const * this_);


void Imf_2_5_DeepScanLineOutputFile_copyPixels(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_DeepScanLineInputFile * in);


void Imf_2_5_DeepScanLineOutputFile_copyPixels_1(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_DeepScanLineInputPart * in);


void Imf_2_5_DeepScanLineOutputFile_updatePreviewImage(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels);








#ifdef __cplusplus
}
#endif
