#pragma once
#include <imath_box_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_IStream_s Imf_2_5_IStream;
typedef struct Imf_2_5_TiledInputFile_s {
    char data[16];
} __attribute__((aligned(8))) Imf_2_5_TiledInputFile;


void Imf_2_5_TiledInputFile_TiledInputFile(
    Imf_2_5_TiledInputFile * this_
    , char const * fileName
    , int numThreads);


void Imf_2_5_TiledInputFile_TiledInputFile_1(
    Imf_2_5_TiledInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads);


void Imf_2_5_TiledInputFile_dtor(
    Imf_2_5_TiledInputFile * this_);


char const * Imf_2_5_TiledInputFile_fileName(
    Imf_2_5_TiledInputFile const * this_);


Imf_2_5_Header const * Imf_2_5_TiledInputFile_header(
    Imf_2_5_TiledInputFile const * this_);


int Imf_2_5_TiledInputFile_version(
    Imf_2_5_TiledInputFile const * this_);


void Imf_2_5_TiledInputFile_setFrameBuffer(
    Imf_2_5_TiledInputFile * this_
    , Imf_2_5_FrameBuffer const * frameBuffer);


Imf_2_5_FrameBuffer const * Imf_2_5_TiledInputFile_frameBuffer(
    Imf_2_5_TiledInputFile const * this_);


_Bool Imf_2_5_TiledInputFile_isComplete(
    Imf_2_5_TiledInputFile const * this_);


unsigned int Imf_2_5_TiledInputFile_tileXSize(
    Imf_2_5_TiledInputFile const * this_);


unsigned int Imf_2_5_TiledInputFile_tileYSize(
    Imf_2_5_TiledInputFile const * this_);


int Imf_2_5_TiledInputFile_numLevels(
    Imf_2_5_TiledInputFile const * this_);


int Imf_2_5_TiledInputFile_numXLevels(
    Imf_2_5_TiledInputFile const * this_);


int Imf_2_5_TiledInputFile_numYLevels(
    Imf_2_5_TiledInputFile const * this_);


_Bool Imf_2_5_TiledInputFile_isValidLevel(
    Imf_2_5_TiledInputFile const * this_
    , int lx
    , int ly);


int Imf_2_5_TiledInputFile_levelWidth(
    Imf_2_5_TiledInputFile const * this_
    , int lx);


int Imf_2_5_TiledInputFile_levelHeight(
    Imf_2_5_TiledInputFile const * this_
    , int ly);


int Imf_2_5_TiledInputFile_numXTiles(
    Imf_2_5_TiledInputFile const * this_
    , int lx);


int Imf_2_5_TiledInputFile_numYTiles(
    Imf_2_5_TiledInputFile const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledInputFile_dataWindowForLevel(
    Imf_2_5_TiledInputFile const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledInputFile_dataWindowForLevel_1(
    Imf_2_5_TiledInputFile const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledInputFile_dataWindowForTile(
    Imf_2_5_TiledInputFile const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledInputFile_dataWindowForTile_1(
    Imf_2_5_TiledInputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledInputFile_readTile(
    Imf_2_5_TiledInputFile * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_TiledInputFile_readTile_1(
    Imf_2_5_TiledInputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledInputFile_readTiles(
    Imf_2_5_TiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_TiledInputFile_readTiles_1(
    Imf_2_5_TiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);


void Imf_2_5_TiledInputFile_rawTileData(
    Imf_2_5_TiledInputFile * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char const * * pixelData
    , int * pixelDataSize);








#ifdef __cplusplus
}
#endif
