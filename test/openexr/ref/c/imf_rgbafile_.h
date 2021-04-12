#pragma once
#include <imath_vec_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Rgba_s Imf_2_5_Rgba;
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imath_2_5_Box2i_s Imath_2_5_Box2i;
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imf_2_5_RgbaOutputFile_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_RgbaOutputFile;
typedef struct Imf_2_5_RgbaInputFile_s {
    char data[56];
} __attribute__((aligned(8))) Imf_2_5_RgbaInputFile;


void Imf_2_5_RgbaOutputFile_dtor(
    Imf_2_5_RgbaOutputFile * this_);


void Imf_2_5_RgbaOutputFile_setFrameBuffer(
    Imf_2_5_RgbaOutputFile * this_
    , Imf_2_5_Rgba const * base
    , unsigned long xStride
    , unsigned long yStride);


void Imf_2_5_RgbaOutputFile_writePixels(
    Imf_2_5_RgbaOutputFile * this_
    , int numScanLines);


int Imf_2_5_RgbaOutputFile_currentScanLine(
    Imf_2_5_RgbaOutputFile const * this_);


Imf_2_5_Header const * Imf_2_5_RgbaOutputFile_header(
    Imf_2_5_RgbaOutputFile const * this_);


Imf_2_5_FrameBuffer const * Imf_2_5_RgbaOutputFile_frameBuffer(
    Imf_2_5_RgbaOutputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_RgbaOutputFile_displayWindow(
    Imf_2_5_RgbaOutputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_RgbaOutputFile_dataWindow(
    Imf_2_5_RgbaOutputFile const * this_);


float Imf_2_5_RgbaOutputFile_pixelAspectRatio(
    Imf_2_5_RgbaOutputFile const * this_);


Imath_2_5_V2f const Imf_2_5_RgbaOutputFile_screenWindowCenter(
    Imf_2_5_RgbaOutputFile const * this_);


float Imf_2_5_RgbaOutputFile_screenWindowWidth(
    Imf_2_5_RgbaOutputFile const * this_);


void Imf_2_5_RgbaOutputFile_updatePreviewImage(
    Imf_2_5_RgbaOutputFile * this_
    , Imf_2_5_PreviewRgba const * preview);


void Imf_2_5_RgbaOutputFile_setYCRounding(
    Imf_2_5_RgbaOutputFile * this_
    , unsigned int roundY
    , unsigned int roundC);


void Imf_2_5_RgbaOutputFile_breakScanLine(
    Imf_2_5_RgbaOutputFile * this_
    , int y
    , int offset
    , int length
    , char c);










void Imf_2_5_RgbaInputFile_RgbaInputFile(
    Imf_2_5_RgbaInputFile * this_
    , char const * name
    , int numThreads);


void Imf_2_5_RgbaInputFile_RgbaInputFile_1(
    Imf_2_5_RgbaInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads);


void Imf_2_5_RgbaInputFile_dtor(
    Imf_2_5_RgbaInputFile * this_);


void Imf_2_5_RgbaInputFile_setFrameBuffer(
    Imf_2_5_RgbaInputFile * this_
    , Imf_2_5_Rgba * base
    , unsigned long xStride
    , unsigned long yStride);


void Imf_2_5_RgbaInputFile_readPixels(
    Imf_2_5_RgbaInputFile * this_
    , int scanLine1
    , int scanLine2);


void Imf_2_5_RgbaInputFile_readPixels_1(
    Imf_2_5_RgbaInputFile * this_
    , int scanLine);


Imf_2_5_Header const * Imf_2_5_RgbaInputFile_header(
    Imf_2_5_RgbaInputFile const * this_);


Imf_2_5_FrameBuffer const * Imf_2_5_RgbaInputFile_frameBuffer(
    Imf_2_5_RgbaInputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_RgbaInputFile_displayWindow(
    Imf_2_5_RgbaInputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_RgbaInputFile_dataWindow(
    Imf_2_5_RgbaInputFile const * this_);


float Imf_2_5_RgbaInputFile_pixelAspectRatio(
    Imf_2_5_RgbaInputFile const * this_);


Imath_2_5_V2f const Imf_2_5_RgbaInputFile_screenWindowCenter(
    Imf_2_5_RgbaInputFile const * this_);


float Imf_2_5_RgbaInputFile_screenWindowWidth(
    Imf_2_5_RgbaInputFile const * this_);


char const * Imf_2_5_RgbaInputFile_fileName(
    Imf_2_5_RgbaInputFile const * this_);


_Bool Imf_2_5_RgbaInputFile_isComplete(
    Imf_2_5_RgbaInputFile const * this_);


int Imf_2_5_RgbaInputFile_version(
    Imf_2_5_RgbaInputFile const * this_);








#ifdef __cplusplus
}
#endif
