#pragma once
#include <imath_box_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_MultiPartInputFile_s Imf_2_5_MultiPartInputFile;
typedef struct Imf_2_5_TiledInputPart_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_TiledInputPart;


void Imf_2_5_TiledInputPart_TiledInputPart(
    Imf_2_5_TiledInputPart * this_
    , Imf_2_5_MultiPartInputFile * multiPartFile
    , int partNumber);


char const * Imf_2_5_TiledInputPart_fileName(
    Imf_2_5_TiledInputPart const * this_);


Imf_2_5_Header const * Imf_2_5_TiledInputPart_header(
    Imf_2_5_TiledInputPart const * this_);


int Imf_2_5_TiledInputPart_version(
    Imf_2_5_TiledInputPart const * this_);


void Imf_2_5_TiledInputPart_setFrameBuffer(
    Imf_2_5_TiledInputPart * this_
    , Imf_2_5_FrameBuffer const * frameBuffer);


Imf_2_5_FrameBuffer const * Imf_2_5_TiledInputPart_frameBuffer(
    Imf_2_5_TiledInputPart const * this_);


_Bool Imf_2_5_TiledInputPart_isComplete(
    Imf_2_5_TiledInputPart const * this_);


unsigned int Imf_2_5_TiledInputPart_tileXSize(
    Imf_2_5_TiledInputPart const * this_);


unsigned int Imf_2_5_TiledInputPart_tileYSize(
    Imf_2_5_TiledInputPart const * this_);


int Imf_2_5_TiledInputPart_numLevels(
    Imf_2_5_TiledInputPart const * this_);


int Imf_2_5_TiledInputPart_numXLevels(
    Imf_2_5_TiledInputPart const * this_);


int Imf_2_5_TiledInputPart_numYLevels(
    Imf_2_5_TiledInputPart const * this_);


_Bool Imf_2_5_TiledInputPart_isValidLevel(
    Imf_2_5_TiledInputPart const * this_
    , int lx
    , int ly);


int Imf_2_5_TiledInputPart_levelWidth(
    Imf_2_5_TiledInputPart const * this_
    , int lx);


int Imf_2_5_TiledInputPart_levelHeight(
    Imf_2_5_TiledInputPart const * this_
    , int ly);


int Imf_2_5_TiledInputPart_numXTiles(
    Imf_2_5_TiledInputPart const * this_
    , int lx);


int Imf_2_5_TiledInputPart_numYTiles(
    Imf_2_5_TiledInputPart const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledInputPart_dataWindowForLevel(
    Imf_2_5_TiledInputPart const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledInputPart_dataWindowForLevel_1(
    Imf_2_5_TiledInputPart const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledInputPart_dataWindowForTile(
    Imf_2_5_TiledInputPart const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledInputPart_dataWindowForTile_1(
    Imf_2_5_TiledInputPart const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledInputPart_readTile(
    Imf_2_5_TiledInputPart * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_TiledInputPart_readTile_1(
    Imf_2_5_TiledInputPart * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledInputPart_readTiles(
    Imf_2_5_TiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_TiledInputPart_readTiles_1(
    Imf_2_5_TiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);


void Imf_2_5_TiledInputPart_rawTileData(
    Imf_2_5_TiledInputPart * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char const * * pixelData
    , int * pixelDataSize);








#ifdef __cplusplus
}
#endif
