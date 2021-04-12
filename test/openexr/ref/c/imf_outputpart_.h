#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_MultiPartOutputFile_s Imf_2_5_MultiPartOutputFile;
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_InputPart_s Imf_2_5_InputPart;
typedef struct Imf_2_5_InputFile_s Imf_2_5_InputFile;
typedef struct Imf_2_5_OutputPart_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_OutputPart;


void Imf_2_5_OutputPart_OutputPart(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_MultiPartOutputFile * multiPartFile
    , int partNumber);


char const * Imf_2_5_OutputPart_fileName(
    Imf_2_5_OutputPart const * this_);


Imf_2_5_Header const * Imf_2_5_OutputPart_header(
    Imf_2_5_OutputPart const * this_);


void Imf_2_5_OutputPart_setFrameBuffer(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_FrameBuffer const * frameBuffer);


Imf_2_5_FrameBuffer const * Imf_2_5_OutputPart_frameBuffer(
    Imf_2_5_OutputPart const * this_);


void Imf_2_5_OutputPart_writePixels(
    Imf_2_5_OutputPart * this_
    , int numScanLines);


int Imf_2_5_OutputPart_currentScanLine(
    Imf_2_5_OutputPart const * this_);


void Imf_2_5_OutputPart_copyPixels(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_InputFile * in);


void Imf_2_5_OutputPart_copyPixels_1(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_InputPart * in);


void Imf_2_5_OutputPart_updatePreviewImage(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_PreviewRgba const * newPixels);


void Imf_2_5_OutputPart_breakScanLine(
    Imf_2_5_OutputPart * this_
    , int y
    , int offset
    , int length
    , char c);








#ifdef __cplusplus
}
#endif
