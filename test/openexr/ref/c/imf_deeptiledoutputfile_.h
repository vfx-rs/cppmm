#pragma once
#include <imath_box_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_DeepTiledInputFile_s Imf_2_5_DeepTiledInputFile;
typedef struct Imf_2_5_OStream_s Imf_2_5_OStream;
typedef struct Imf_2_5_DeepTiledInputPart_s Imf_2_5_DeepTiledInputPart;
typedef struct Imf_2_5_DeepFrameBuffer_s Imf_2_5_DeepFrameBuffer;
typedef struct Imf_2_5_DeepTiledOutputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_DeepTiledOutputFile;


void Imf_2_5_DeepTiledOutputFile_DeepTiledOutputFile(
    Imf_2_5_DeepTiledOutputFile * this_
    , char const * fileName
    , Imf_2_5_Header const * header
    , int numThreads);


void Imf_2_5_DeepTiledOutputFile_DeepTiledOutputFile_1(
    Imf_2_5_DeepTiledOutputFile * this_
    , Imf_2_5_OStream * os
    , Imf_2_5_Header const * header
    , int numThreads);


void Imf_2_5_DeepTiledOutputFile_dtor(
    Imf_2_5_DeepTiledOutputFile * this_);


char const * Imf_2_5_DeepTiledOutputFile_fileName(
    Imf_2_5_DeepTiledOutputFile const * this_);


Imf_2_5_Header const * Imf_2_5_DeepTiledOutputFile_header(
    Imf_2_5_DeepTiledOutputFile const * this_);


void Imf_2_5_DeepTiledOutputFile_setFrameBuffer(
    Imf_2_5_DeepTiledOutputFile * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer);


Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepTiledOutputFile_frameBuffer(
    Imf_2_5_DeepTiledOutputFile const * this_);


unsigned int Imf_2_5_DeepTiledOutputFile_tileXSize(
    Imf_2_5_DeepTiledOutputFile const * this_);


unsigned int Imf_2_5_DeepTiledOutputFile_tileYSize(
    Imf_2_5_DeepTiledOutputFile const * this_);


int Imf_2_5_DeepTiledOutputFile_numLevels(
    Imf_2_5_DeepTiledOutputFile const * this_);


int Imf_2_5_DeepTiledOutputFile_numXLevels(
    Imf_2_5_DeepTiledOutputFile const * this_);


int Imf_2_5_DeepTiledOutputFile_numYLevels(
    Imf_2_5_DeepTiledOutputFile const * this_);


_Bool Imf_2_5_DeepTiledOutputFile_isValidLevel(
    Imf_2_5_DeepTiledOutputFile const * this_
    , int lx
    , int ly);


int Imf_2_5_DeepTiledOutputFile_levelWidth(
    Imf_2_5_DeepTiledOutputFile const * this_
    , int lx);


int Imf_2_5_DeepTiledOutputFile_levelHeight(
    Imf_2_5_DeepTiledOutputFile const * this_
    , int ly);


int Imf_2_5_DeepTiledOutputFile_numXTiles(
    Imf_2_5_DeepTiledOutputFile const * this_
    , int lx);


int Imf_2_5_DeepTiledOutputFile_numYTiles(
    Imf_2_5_DeepTiledOutputFile const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_DeepTiledOutputFile_dataWindowForLevel(
    Imf_2_5_DeepTiledOutputFile const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_DeepTiledOutputFile_dataWindowForLevel_1(
    Imf_2_5_DeepTiledOutputFile const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_DeepTiledOutputFile_dataWindowForTile(
    Imf_2_5_DeepTiledOutputFile const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_DeepTiledOutputFile_dataWindowForTile_1(
    Imf_2_5_DeepTiledOutputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledOutputFile_writeTile(
    Imf_2_5_DeepTiledOutputFile * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_DeepTiledOutputFile_writeTile_1(
    Imf_2_5_DeepTiledOutputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledOutputFile_writeTiles(
    Imf_2_5_DeepTiledOutputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_DeepTiledOutputFile_writeTiles_1(
    Imf_2_5_DeepTiledOutputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);


void Imf_2_5_DeepTiledOutputFile_copyPixels(
    Imf_2_5_DeepTiledOutputFile * this_
    , Imf_2_5_DeepTiledInputFile * in);


void Imf_2_5_DeepTiledOutputFile_copyPixels_1(
    Imf_2_5_DeepTiledOutputFile * this_
    , Imf_2_5_DeepTiledInputPart * in);


void Imf_2_5_DeepTiledOutputFile_updatePreviewImage(
    Imf_2_5_DeepTiledOutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels);


void Imf_2_5_DeepTiledOutputFile_breakTile(
    Imf_2_5_DeepTiledOutputFile * this_
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
