#pragma once
#include <imath_box_.h>
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
typedef struct Imf_2_5_TiledRgbaOutputFile_s {
    char data[24];
} __attribute__((aligned(8))) Imf_2_5_TiledRgbaOutputFile;
typedef struct Imf_2_5_TiledRgbaInputFile_s {
    char data[56];
} __attribute__((aligned(8))) Imf_2_5_TiledRgbaInputFile;


void Imf_2_5_TiledRgbaOutputFile_dtor(
    Imf_2_5_TiledRgbaOutputFile * this_);


void Imf_2_5_TiledRgbaOutputFile_setFrameBuffer(
    Imf_2_5_TiledRgbaOutputFile * this_
    , Imf_2_5_Rgba const * base
    , unsigned long xStride
    , unsigned long yStride);


Imf_2_5_Header const * Imf_2_5_TiledRgbaOutputFile_header(
    Imf_2_5_TiledRgbaOutputFile const * this_);


Imf_2_5_FrameBuffer const * Imf_2_5_TiledRgbaOutputFile_frameBuffer(
    Imf_2_5_TiledRgbaOutputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_TiledRgbaOutputFile_displayWindow(
    Imf_2_5_TiledRgbaOutputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_TiledRgbaOutputFile_dataWindow(
    Imf_2_5_TiledRgbaOutputFile const * this_);


float Imf_2_5_TiledRgbaOutputFile_pixelAspectRatio(
    Imf_2_5_TiledRgbaOutputFile const * this_);


Imath_2_5_V2f const Imf_2_5_TiledRgbaOutputFile_screenWindowCenter(
    Imf_2_5_TiledRgbaOutputFile const * this_);


float Imf_2_5_TiledRgbaOutputFile_screenWindowWidth(
    Imf_2_5_TiledRgbaOutputFile const * this_);


unsigned int Imf_2_5_TiledRgbaOutputFile_tileXSize(
    Imf_2_5_TiledRgbaOutputFile const * this_);


unsigned int Imf_2_5_TiledRgbaOutputFile_tileYSize(
    Imf_2_5_TiledRgbaOutputFile const * this_);


int Imf_2_5_TiledRgbaOutputFile_numLevels(
    Imf_2_5_TiledRgbaOutputFile const * this_);


int Imf_2_5_TiledRgbaOutputFile_numXLevels(
    Imf_2_5_TiledRgbaOutputFile const * this_);


int Imf_2_5_TiledRgbaOutputFile_numYLevels(
    Imf_2_5_TiledRgbaOutputFile const * this_);


_Bool Imf_2_5_TiledRgbaOutputFile_isValidLevel(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int lx
    , int ly);


int Imf_2_5_TiledRgbaOutputFile_levelWidth(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int lx);


int Imf_2_5_TiledRgbaOutputFile_levelHeight(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int ly);


int Imf_2_5_TiledRgbaOutputFile_numXTiles(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int lx);


int Imf_2_5_TiledRgbaOutputFile_numYTiles(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledRgbaOutputFile_dataWindowForLevel(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledRgbaOutputFile_dataWindowForLevel_1(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledRgbaOutputFile_dataWindowForTile(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledRgbaOutputFile_dataWindowForTile_1(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledRgbaOutputFile_writeTile(
    Imf_2_5_TiledRgbaOutputFile * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_TiledRgbaOutputFile_writeTile_1(
    Imf_2_5_TiledRgbaOutputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledRgbaOutputFile_writeTiles(
    Imf_2_5_TiledRgbaOutputFile * this_
    , int dxMin
    , int dxMax
    , int dyMin
    , int dyMax
    , int lx
    , int ly);


void Imf_2_5_TiledRgbaOutputFile_writeTiles_1(
    Imf_2_5_TiledRgbaOutputFile * this_
    , int dxMin
    , int dxMax
    , int dyMin
    , int dyMax
    , int l);


void Imf_2_5_TiledRgbaOutputFile_updatePreviewImage(
    Imf_2_5_TiledRgbaOutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels);


void Imf_2_5_TiledRgbaOutputFile_breakTile(
    Imf_2_5_TiledRgbaOutputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly
    , int offset
    , int length
    , char c);










void Imf_2_5_TiledRgbaInputFile_TiledRgbaInputFile(
    Imf_2_5_TiledRgbaInputFile * this_
    , char const * name
    , int numThreads);


void Imf_2_5_TiledRgbaInputFile_TiledRgbaInputFile_1(
    Imf_2_5_TiledRgbaInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads);


void Imf_2_5_TiledRgbaInputFile_dtor(
    Imf_2_5_TiledRgbaInputFile * this_);


void Imf_2_5_TiledRgbaInputFile_setFrameBuffer(
    Imf_2_5_TiledRgbaInputFile * this_
    , Imf_2_5_Rgba * base
    , unsigned long xStride
    , unsigned long yStride);


Imf_2_5_Header const * Imf_2_5_TiledRgbaInputFile_header(
    Imf_2_5_TiledRgbaInputFile const * this_);


Imf_2_5_FrameBuffer const * Imf_2_5_TiledRgbaInputFile_frameBuffer(
    Imf_2_5_TiledRgbaInputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_TiledRgbaInputFile_displayWindow(
    Imf_2_5_TiledRgbaInputFile const * this_);


Imath_2_5_Box2i const * Imf_2_5_TiledRgbaInputFile_dataWindow(
    Imf_2_5_TiledRgbaInputFile const * this_);


float Imf_2_5_TiledRgbaInputFile_pixelAspectRatio(
    Imf_2_5_TiledRgbaInputFile const * this_);


Imath_2_5_V2f const Imf_2_5_TiledRgbaInputFile_screenWindowCenter(
    Imf_2_5_TiledRgbaInputFile const * this_);


float Imf_2_5_TiledRgbaInputFile_screenWindowWidth(
    Imf_2_5_TiledRgbaInputFile const * this_);


char const * Imf_2_5_TiledRgbaInputFile_fileName(
    Imf_2_5_TiledRgbaInputFile const * this_);


_Bool Imf_2_5_TiledRgbaInputFile_isComplete(
    Imf_2_5_TiledRgbaInputFile const * this_);


int Imf_2_5_TiledRgbaInputFile_version(
    Imf_2_5_TiledRgbaInputFile const * this_);


unsigned int Imf_2_5_TiledRgbaInputFile_tileXSize(
    Imf_2_5_TiledRgbaInputFile const * this_);


unsigned int Imf_2_5_TiledRgbaInputFile_tileYSize(
    Imf_2_5_TiledRgbaInputFile const * this_);


int Imf_2_5_TiledRgbaInputFile_numLevels(
    Imf_2_5_TiledRgbaInputFile const * this_);


int Imf_2_5_TiledRgbaInputFile_numXLevels(
    Imf_2_5_TiledRgbaInputFile const * this_);


int Imf_2_5_TiledRgbaInputFile_numYLevels(
    Imf_2_5_TiledRgbaInputFile const * this_);


_Bool Imf_2_5_TiledRgbaInputFile_isValidLevel(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int lx
    , int ly);


int Imf_2_5_TiledRgbaInputFile_levelWidth(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int lx);


int Imf_2_5_TiledRgbaInputFile_levelHeight(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int ly);


int Imf_2_5_TiledRgbaInputFile_numXTiles(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int lx);


int Imf_2_5_TiledRgbaInputFile_numYTiles(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledRgbaInputFile_dataWindowForLevel(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledRgbaInputFile_dataWindowForLevel_1(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledRgbaInputFile_dataWindowForTile(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledRgbaInputFile_dataWindowForTile_1(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledRgbaInputFile_readTile(
    Imf_2_5_TiledRgbaInputFile * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_TiledRgbaInputFile_readTile_1(
    Imf_2_5_TiledRgbaInputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledRgbaInputFile_readTiles(
    Imf_2_5_TiledRgbaInputFile * this_
    , int dxMin
    , int dxMax
    , int dyMin
    , int dyMax
    , int lx
    , int ly);


void Imf_2_5_TiledRgbaInputFile_readTiles_1(
    Imf_2_5_TiledRgbaInputFile * this_
    , int dxMin
    , int dxMax
    , int dyMin
    , int dyMax
    , int l);








#ifdef __cplusplus
}
#endif
