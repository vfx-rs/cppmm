#pragma once
#include <imath_vec_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Rgba_s Imf_2_5_Rgba;
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imf_2_5_AcesOutputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_AcesOutputFile;
typedef struct Imf_2_5_AcesInputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_AcesInputFile;


void Imf_2_5_AcesOutputFile_dtor(
    Imf_2_5_AcesOutputFile * this_);


void Imf_2_5_AcesOutputFile_setFrameBuffer(
    Imf_2_5_AcesOutputFile * this_
    , Imf_2_5_Rgba const * base
    , unsigned long xStride
    , unsigned long yStride);


void Imf_2_5_AcesOutputFile_writePixels(
    Imf_2_5_AcesOutputFile * this_
    , int numScanLines);


int Imf_2_5_AcesOutputFile_currentScanLine(
    Imf_2_5_AcesOutputFile const * this_);


Imf_2_5_Header const * Imf_2_5_AcesOutputFile_header(
    Imf_2_5_AcesOutputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_AcesOutputFile_displayWindow(
    Imf_2_5_AcesOutputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_AcesOutputFile_dataWindow(
    Imf_2_5_AcesOutputFile const * this_);


float Imf_2_5_AcesOutputFile_pixelAspectRatio(
    Imf_2_5_AcesOutputFile const * this_);


Imath_2_5_V2f const Imf_2_5_AcesOutputFile_screenWindowCenter(
    Imf_2_5_AcesOutputFile const * this_);


float Imf_2_5_AcesOutputFile_screenWindowWidth(
    Imf_2_5_AcesOutputFile const * this_);


void Imf_2_5_AcesOutputFile_updatePreviewImage(
    Imf_2_5_AcesOutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels);










void Imf_2_5_AcesInputFile_AcesInputFile(
    Imf_2_5_AcesInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads);


void Imf_2_5_AcesInputFile_dtor(
    Imf_2_5_AcesInputFile * this_);


void Imf_2_5_AcesInputFile_setFrameBuffer(
    Imf_2_5_AcesInputFile * this_
    , Imf_2_5_Rgba * base
    , unsigned long xStride
    , unsigned long yStride);


void Imf_2_5_AcesInputFile_readPixels(
    Imf_2_5_AcesInputFile * this_
    , int scanLine1
    , int scanLine2);


void Imf_2_5_AcesInputFile_readPixels_1(
    Imf_2_5_AcesInputFile * this_
    , int scanLine);


Imf_2_5_Header const * Imf_2_5_AcesInputFile_header(
    Imf_2_5_AcesInputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_AcesInputFile_displayWindow(
    Imf_2_5_AcesInputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_AcesInputFile_dataWindow(
    Imf_2_5_AcesInputFile const * this_);


float Imf_2_5_AcesInputFile_pixelAspectRatio(
    Imf_2_5_AcesInputFile const * this_);


Imath_2_5_V2f const Imf_2_5_AcesInputFile_screenWindowCenter(
    Imf_2_5_AcesInputFile const * this_);


float Imf_2_5_AcesInputFile_screenWindowWidth(
    Imf_2_5_AcesInputFile const * this_);


char const * Imf_2_5_AcesInputFile_fileName(
    Imf_2_5_AcesInputFile const * this_);


_Bool Imf_2_5_AcesInputFile_isComplete(
    Imf_2_5_AcesInputFile const * this_);


int Imf_2_5_AcesInputFile_version(
    Imf_2_5_AcesInputFile const * this_);








#ifdef __cplusplus
}
#endif
