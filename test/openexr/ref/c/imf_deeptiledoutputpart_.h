#pragma once
#include <imath_box_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_MultiPartOutputFile_s Imf_2_5_MultiPartOutputFile;
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_DeepTiledInputFile_s Imf_2_5_DeepTiledInputFile;
typedef struct Imf_2_5_DeepTiledInputPart_s Imf_2_5_DeepTiledInputPart;
typedef struct Imf_2_5_DeepFrameBuffer_s Imf_2_5_DeepFrameBuffer;
typedef struct Imf_2_5_DeepTiledOutputPart_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_DeepTiledOutputPart;


void Imf_2_5_DeepTiledOutputPart_DeepTiledOutputPart(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_MultiPartOutputFile * multiPartFile
    , int partNumber);


char const * Imf_2_5_DeepTiledOutputPart_fileName(
    Imf_2_5_DeepTiledOutputPart const * this_);


Imf_2_5_Header const * Imf_2_5_DeepTiledOutputPart_header(
    Imf_2_5_DeepTiledOutputPart const * this_);


void Imf_2_5_DeepTiledOutputPart_setFrameBuffer(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer);


Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepTiledOutputPart_frameBuffer(
    Imf_2_5_DeepTiledOutputPart const * this_);


unsigned int Imf_2_5_DeepTiledOutputPart_tileXSize(
    Imf_2_5_DeepTiledOutputPart const * this_);


unsigned int Imf_2_5_DeepTiledOutputPart_tileYSize(
    Imf_2_5_DeepTiledOutputPart const * this_);


int Imf_2_5_DeepTiledOutputPart_numLevels(
    Imf_2_5_DeepTiledOutputPart const * this_);


int Imf_2_5_DeepTiledOutputPart_numXLevels(
    Imf_2_5_DeepTiledOutputPart const * this_);


int Imf_2_5_DeepTiledOutputPart_numYLevels(
    Imf_2_5_DeepTiledOutputPart const * this_);


_Bool Imf_2_5_DeepTiledOutputPart_isValidLevel(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int lx
    , int ly);


int Imf_2_5_DeepTiledOutputPart_levelWidth(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int lx);


int Imf_2_5_DeepTiledOutputPart_levelHeight(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int ly);


int Imf_2_5_DeepTiledOutputPart_numXTiles(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int lx);


int Imf_2_5_DeepTiledOutputPart_numYTiles(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_DeepTiledOutputPart_dataWindowForLevel(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_DeepTiledOutputPart_dataWindowForLevel_1(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_DeepTiledOutputPart_dataWindowForTile(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_DeepTiledOutputPart_dataWindowForTile_1(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledOutputPart_writeTile(
    Imf_2_5_DeepTiledOutputPart * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_DeepTiledOutputPart_writeTile_1(
    Imf_2_5_DeepTiledOutputPart * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledOutputPart_writeTiles(
    Imf_2_5_DeepTiledOutputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_DeepTiledOutputPart_writeTiles_1(
    Imf_2_5_DeepTiledOutputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);


void Imf_2_5_DeepTiledOutputPart_copyPixels(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_DeepTiledInputFile * in);


void Imf_2_5_DeepTiledOutputPart_copyPixels_1(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_DeepTiledInputPart * in);


void Imf_2_5_DeepTiledOutputPart_updatePreviewImage(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_PreviewRgba const * newPixels);


void Imf_2_5_DeepTiledOutputPart_breakTile(
    Imf_2_5_DeepTiledOutputPart * this_
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
