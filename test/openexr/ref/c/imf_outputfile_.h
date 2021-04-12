#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_InputPart_s Imf_2_5_InputPart;
typedef struct Imf_2_5_InputFile_s Imf_2_5_InputFile;
typedef struct Imf_2_5_OutputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_OutputFile;


void Imf_2_5_OutputFile_OutputFile(
    Imf_2_5_OutputFile * this_
    , char const * fileName
    , Imf_2_5_Header const * header
    , int numThreads);


void Imf_2_5_OutputFile_OutputFile_1(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_OStream * os
    , Imf_2_5_Header const * header
    , int numThreads);


void Imf_2_5_OutputFile_dtor(
    Imf_2_5_OutputFile * this_);


char const * Imf_2_5_OutputFile_fileName(
    Imf_2_5_OutputFile const * this_);


Imf_2_5_Header const * Imf_2_5_OutputFile_header(
    Imf_2_5_OutputFile const * this_);


void Imf_2_5_OutputFile_setFrameBuffer(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_FrameBuffer const * frameBuffer);


Imf_2_5_FrameBuffer const * Imf_2_5_OutputFile_frameBuffer(
    Imf_2_5_OutputFile const * this_);


void Imf_2_5_OutputFile_writePixels(
    Imf_2_5_OutputFile * this_
    , int numScanLines);


int Imf_2_5_OutputFile_currentScanLine(
    Imf_2_5_OutputFile const * this_);


void Imf_2_5_OutputFile_copyPixels(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_InputFile * in);


void Imf_2_5_OutputFile_copyPixels_1(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_InputPart * in);


void Imf_2_5_OutputFile_updatePreviewImage(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels);


void Imf_2_5_OutputFile_breakScanLine(
    Imf_2_5_OutputFile * this_
    , int y
    , int offset
    , int length
    , char c);








#ifdef __cplusplus
}
#endif
