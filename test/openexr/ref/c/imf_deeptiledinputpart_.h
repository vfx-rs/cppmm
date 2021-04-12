#pragma once
#include <imath_box_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_MultiPartInputFile_s Imf_2_5_MultiPartInputFile;
typedef struct Imf_2_5_DeepFrameBuffer_s Imf_2_5_DeepFrameBuffer;
typedef struct Imf_2_5_DeepTiledInputPart_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_DeepTiledInputPart;


void Imf_2_5_DeepTiledInputPart_DeepTiledInputPart(
    Imf_2_5_DeepTiledInputPart * this_
    , Imf_2_5_MultiPartInputFile * multiPartFile
    , int partNumber);


char const * Imf_2_5_DeepTiledInputPart_fileName(
    Imf_2_5_DeepTiledInputPart const * this_);


Imf_2_5_Header const * Imf_2_5_DeepTiledInputPart_header(
    Imf_2_5_DeepTiledInputPart const * this_);


int Imf_2_5_DeepTiledInputPart_version(
    Imf_2_5_DeepTiledInputPart const * this_);


void Imf_2_5_DeepTiledInputPart_setFrameBuffer(
    Imf_2_5_DeepTiledInputPart * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer);


Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepTiledInputPart_frameBuffer(
    Imf_2_5_DeepTiledInputPart const * this_);


_Bool Imf_2_5_DeepTiledInputPart_isComplete(
    Imf_2_5_DeepTiledInputPart const * this_);


unsigned int Imf_2_5_DeepTiledInputPart_tileXSize(
    Imf_2_5_DeepTiledInputPart const * this_);


unsigned int Imf_2_5_DeepTiledInputPart_tileYSize(
    Imf_2_5_DeepTiledInputPart const * this_);


int Imf_2_5_DeepTiledInputPart_numLevels(
    Imf_2_5_DeepTiledInputPart const * this_);


int Imf_2_5_DeepTiledInputPart_numXLevels(
    Imf_2_5_DeepTiledInputPart const * this_);


int Imf_2_5_DeepTiledInputPart_numYLevels(
    Imf_2_5_DeepTiledInputPart const * this_);


_Bool Imf_2_5_DeepTiledInputPart_isValidLevel(
    Imf_2_5_DeepTiledInputPart const * this_
    , int lx
    , int ly);


int Imf_2_5_DeepTiledInputPart_levelWidth(
    Imf_2_5_DeepTiledInputPart const * this_
    , int lx);


int Imf_2_5_DeepTiledInputPart_levelHeight(
    Imf_2_5_DeepTiledInputPart const * this_
    , int ly);


int Imf_2_5_DeepTiledInputPart_numXTiles(
    Imf_2_5_DeepTiledInputPart const * this_
    , int lx);


int Imf_2_5_DeepTiledInputPart_numYTiles(
    Imf_2_5_DeepTiledInputPart const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_DeepTiledInputPart_dataWindowForLevel(
    Imf_2_5_DeepTiledInputPart const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_DeepTiledInputPart_dataWindowForLevel_1(
    Imf_2_5_DeepTiledInputPart const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_DeepTiledInputPart_dataWindowForTile(
    Imf_2_5_DeepTiledInputPart const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_DeepTiledInputPart_dataWindowForTile_1(
    Imf_2_5_DeepTiledInputPart const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputPart_readTile(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_DeepTiledInputPart_readTile_1(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputPart_readTiles(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputPart_readTiles_1(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);


void Imf_2_5_DeepTiledInputPart_rawTileData(
    Imf_2_5_DeepTiledInputPart const * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char * data
    , unsigned long * dataSize);


void Imf_2_5_DeepTiledInputPart_readPixelSampleCount(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_DeepTiledInputPart_readPixelSampleCount_1(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputPart_readPixelSampleCounts(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputPart_readPixelSampleCounts_1(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);








#ifdef __cplusplus
}
#endif
