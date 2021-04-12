#pragma once
#include <imath_box_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imf_2_5_DeepFrameBuffer_s Imf_2_5_DeepFrameBuffer;
typedef struct Imf_2_5_DeepTiledInputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_DeepTiledInputFile;


void Imf_2_5_DeepTiledInputFile_DeepTiledInputFile(
    Imf_2_5_DeepTiledInputFile * this_
    , char const * fileName
    , int numThreads);


void Imf_2_5_DeepTiledInputFile_DeepTiledInputFile_1(
    Imf_2_5_DeepTiledInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads);


void Imf_2_5_DeepTiledInputFile_dtor(
    Imf_2_5_DeepTiledInputFile * this_);


char const * Imf_2_5_DeepTiledInputFile_fileName(
    Imf_2_5_DeepTiledInputFile const * this_);


Imf_2_5_Header const * Imf_2_5_DeepTiledInputFile_header(
    Imf_2_5_DeepTiledInputFile const * this_);


int Imf_2_5_DeepTiledInputFile_version(
    Imf_2_5_DeepTiledInputFile const * this_);


void Imf_2_5_DeepTiledInputFile_setFrameBuffer(
    Imf_2_5_DeepTiledInputFile * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer);


Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepTiledInputFile_frameBuffer(
    Imf_2_5_DeepTiledInputFile const * this_);


_Bool Imf_2_5_DeepTiledInputFile_isComplete(
    Imf_2_5_DeepTiledInputFile const * this_);


unsigned int Imf_2_5_DeepTiledInputFile_tileXSize(
    Imf_2_5_DeepTiledInputFile const * this_);


unsigned int Imf_2_5_DeepTiledInputFile_tileYSize(
    Imf_2_5_DeepTiledInputFile const * this_);


int Imf_2_5_DeepTiledInputFile_numLevels(
    Imf_2_5_DeepTiledInputFile const * this_);


int Imf_2_5_DeepTiledInputFile_numXLevels(
    Imf_2_5_DeepTiledInputFile const * this_);


int Imf_2_5_DeepTiledInputFile_numYLevels(
    Imf_2_5_DeepTiledInputFile const * this_);


_Bool Imf_2_5_DeepTiledInputFile_isValidLevel(
    Imf_2_5_DeepTiledInputFile const * this_
    , int lx
    , int ly);


unsigned long Imf_2_5_DeepTiledInputFile_totalTiles(
    Imf_2_5_DeepTiledInputFile const * this_);


int Imf_2_5_DeepTiledInputFile_levelWidth(
    Imf_2_5_DeepTiledInputFile const * this_
    , int lx);


int Imf_2_5_DeepTiledInputFile_levelHeight(
    Imf_2_5_DeepTiledInputFile const * this_
    , int ly);


int Imf_2_5_DeepTiledInputFile_numXTiles(
    Imf_2_5_DeepTiledInputFile const * this_
    , int lx);


int Imf_2_5_DeepTiledInputFile_numYTiles(
    Imf_2_5_DeepTiledInputFile const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_DeepTiledInputFile_dataWindowForLevel(
    Imf_2_5_DeepTiledInputFile const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_DeepTiledInputFile_dataWindowForLevel_1(
    Imf_2_5_DeepTiledInputFile const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_DeepTiledInputFile_dataWindowForTile(
    Imf_2_5_DeepTiledInputFile const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_DeepTiledInputFile_dataWindowForTile_1(
    Imf_2_5_DeepTiledInputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputFile_readTile(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_DeepTiledInputFile_readTile_1(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputFile_readTiles(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputFile_readTiles_1(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);


void Imf_2_5_DeepTiledInputFile_rawTileData(
    Imf_2_5_DeepTiledInputFile const * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char * pixelData
    , unsigned long * dataSize);


void Imf_2_5_DeepTiledInputFile_readPixelSampleCount(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_DeepTiledInputFile_readPixelSampleCount_1(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputFile_readPixelSampleCounts(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_DeepTiledInputFile_readPixelSampleCounts_1(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);








#ifdef __cplusplus
}
#endif
