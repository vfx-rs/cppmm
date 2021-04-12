#pragma once
#include <imath_box_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_TiledInputPart_s Imf_2_5_TiledInputPart;
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_TiledInputFile_s Imf_2_5_TiledInputFile;
typedef struct Imf_2_5_InputPart_s Imf_2_5_InputPart;
typedef struct Imf_2_5_InputFile_s Imf_2_5_InputFile;
typedef struct Imf_2_5_TiledOutputFile_s {
    char data[32];
} __attribute__((aligned(8))) Imf_2_5_TiledOutputFile;


void Imf_2_5_TiledOutputFile_TiledOutputFile(
    Imf_2_5_TiledOutputFile * this_
    , char const * fileName
    , Imf_2_5_Header const * header
    , int numThreads);


void Imf_2_5_TiledOutputFile_TiledOutputFile_1(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_OStream * os
    , Imf_2_5_Header const * header
    , int numThreads);


void Imf_2_5_TiledOutputFile_dtor(
    Imf_2_5_TiledOutputFile * this_);


char const * Imf_2_5_TiledOutputFile_fileName(
    Imf_2_5_TiledOutputFile const * this_);


Imf_2_5_Header const * Imf_2_5_TiledOutputFile_header(
    Imf_2_5_TiledOutputFile const * this_);


void Imf_2_5_TiledOutputFile_setFrameBuffer(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_FrameBuffer const * frameBuffer);


unsigned int Imf_2_5_TiledOutputFile_tileXSize(
    Imf_2_5_TiledOutputFile const * this_);


unsigned int Imf_2_5_TiledOutputFile_tileYSize(
    Imf_2_5_TiledOutputFile const * this_);


int Imf_2_5_TiledOutputFile_numLevels(
    Imf_2_5_TiledOutputFile const * this_);


int Imf_2_5_TiledOutputFile_numXLevels(
    Imf_2_5_TiledOutputFile const * this_);


int Imf_2_5_TiledOutputFile_numYLevels(
    Imf_2_5_TiledOutputFile const * this_);


_Bool Imf_2_5_TiledOutputFile_isValidLevel(
    Imf_2_5_TiledOutputFile const * this_
    , int lx
    , int ly);


int Imf_2_5_TiledOutputFile_levelWidth(
    Imf_2_5_TiledOutputFile const * this_
    , int lx);


int Imf_2_5_TiledOutputFile_levelHeight(
    Imf_2_5_TiledOutputFile const * this_
    , int ly);


int Imf_2_5_TiledOutputFile_numXTiles(
    Imf_2_5_TiledOutputFile const * this_
    , int lx);


int Imf_2_5_TiledOutputFile_numYTiles(
    Imf_2_5_TiledOutputFile const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledOutputFile_dataWindowForLevel(
    Imf_2_5_TiledOutputFile const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledOutputFile_dataWindowForLevel_1(
    Imf_2_5_TiledOutputFile const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledOutputFile_dataWindowForTile(
    Imf_2_5_TiledOutputFile const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledOutputFile_dataWindowForTile_1(
    Imf_2_5_TiledOutputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledOutputFile_writeTile(
    Imf_2_5_TiledOutputFile * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_TiledOutputFile_writeTile_1(
    Imf_2_5_TiledOutputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledOutputFile_writeTiles(
    Imf_2_5_TiledOutputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_TiledOutputFile_writeTiles_1(
    Imf_2_5_TiledOutputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);


void Imf_2_5_TiledOutputFile_copyPixels(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_TiledInputFile * in);


void Imf_2_5_TiledOutputFile_copyPixels_1(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_TiledInputPart * in);


void Imf_2_5_TiledOutputFile_copyPixels_2(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_InputFile * in);


void Imf_2_5_TiledOutputFile_copyPixels_3(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_InputPart * in);


void Imf_2_5_TiledOutputFile_updatePreviewImage(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels);


void Imf_2_5_TiledOutputFile_breakTile(
    Imf_2_5_TiledOutputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly
    , int offset
    , int length
    , char c);








#ifdef __cplusplus
}
#endif
