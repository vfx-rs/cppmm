#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_MultiPartOutputFile_s Imf_2_5_MultiPartOutputFile;
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_DeepScanLineInputPart_s Imf_2_5_DeepScanLineInputPart;
typedef struct Imf_2_5_DeepScanLineInputFile_s Imf_2_5_DeepScanLineInputFile;
typedef struct Imf_2_5_DeepFrameBuffer_s Imf_2_5_DeepFrameBuffer;
typedef struct Imf_2_5_DeepScanLineOutputPart_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_DeepScanLineOutputPart;


void Imf_2_5_DeepScanLineOutputPart_DeepScanLineOutputPart(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_MultiPartOutputFile * multiPartFile
    , int partNumber);


char const * Imf_2_5_DeepScanLineOutputPart_fileName(
    Imf_2_5_DeepScanLineOutputPart const * this_);


Imf_2_5_Header const * Imf_2_5_DeepScanLineOutputPart_header(
    Imf_2_5_DeepScanLineOutputPart const * this_);


void Imf_2_5_DeepScanLineOutputPart_setFrameBuffer(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer);


Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepScanLineOutputPart_frameBuffer(
    Imf_2_5_DeepScanLineOutputPart const * this_);


void Imf_2_5_DeepScanLineOutputPart_writePixels(
    Imf_2_5_DeepScanLineOutputPart * this_
    , int numScanLines);


int Imf_2_5_DeepScanLineOutputPart_currentScanLine(
    Imf_2_5_DeepScanLineOutputPart const * this_);


void Imf_2_5_DeepScanLineOutputPart_copyPixels(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_DeepScanLineInputFile * in);


void Imf_2_5_DeepScanLineOutputPart_copyPixels_1(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_DeepScanLineInputPart * in);


void Imf_2_5_DeepScanLineOutputPart_updatePreviewImage(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_PreviewRgba const * newPixels);








#ifdef __cplusplus
}
#endif
