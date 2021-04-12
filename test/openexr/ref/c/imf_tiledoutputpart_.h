#pragma once
#include <imath_box_.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Imf_2_5_FrameBuffer_s Imf_2_5_FrameBuffer;
typedef struct Imf_2_5_MultiPartOutputFile_s Imf_2_5_MultiPartOutputFile;
typedef struct Imf_2_5_PreviewRgba_s Imf_2_5_PreviewRgba;
typedef struct Imf_2_5_Header_s Imf_2_5_Header;
typedef struct Imf_2_5_TiledInputPart_s Imf_2_5_TiledInputPart;
typedef struct Imf_2_5_TiledInputFile_s Imf_2_5_TiledInputFile;
typedef struct Imf_2_5_InputPart_s Imf_2_5_InputPart;
typedef struct Imf_2_5_InputFile_s Imf_2_5_InputFile;
typedef struct Imf_2_5_TiledOutputPart_s {
    char data[8];
} __attribute__((aligned(8))) Imf_2_5_TiledOutputPart;


void Imf_2_5_TiledOutputPart_TiledOutputPart(
    Imf_2_5_TiledOutputPart * this_
    , Imf_2_5_MultiPartOutputFile * multiPartFile
    , int partNumber);


char const * Imf_2_5_TiledOutputPart_fileName(
    Imf_2_5_TiledOutputPart const * this_);


Imf_2_5_Header const * Imf_2_5_TiledOutputPart_header(
    Imf_2_5_TiledOutputPart const * this_);


void Imf_2_5_TiledOutputPart_setFrameBuffer(
    Imf_2_5_TiledOutputPart * this_
    , Imf_2_5_FrameBuffer const * frameBuffer);


Imf_2_5_FrameBuffer const * Imf_2_5_TiledOutputPart_frameBuffer(
    Imf_2_5_TiledOutputPart const * this_);


unsigned int Imf_2_5_TiledOutputPart_tileXSize(
    Imf_2_5_TiledOutputPart const * this_);


unsigned int Imf_2_5_TiledOutputPart_tileYSize(
    Imf_2_5_TiledOutputPart const * this_);


int Imf_2_5_TiledOutputPart_numLevels(
    Imf_2_5_TiledOutputPart const * this_);


int Imf_2_5_TiledOutputPart_numXLevels(
    Imf_2_5_TiledOutputPart const * this_);


int Imf_2_5_TiledOutputPart_numYLevels(
    Imf_2_5_TiledOutputPart const * this_);


_Bool Imf_2_5_TiledOutputPart_isValidLevel(
    Imf_2_5_TiledOutputPart const * this_
    , int lx
    , int ly);


int Imf_2_5_TiledOutputPart_levelWidth(
    Imf_2_5_TiledOutputPart const * this_
    , int lx);


int Imf_2_5_TiledOutputPart_levelHeight(
    Imf_2_5_TiledOutputPart const * this_
    , int ly);


int Imf_2_5_TiledOutputPart_numXTiles(
    Imf_2_5_TiledOutputPart const * this_
    , int lx);


int Imf_2_5_TiledOutputPart_numYTiles(
    Imf_2_5_TiledOutputPart const * this_
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledOutputPart_dataWindowForLevel(
    Imf_2_5_TiledOutputPart const * this_
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledOutputPart_dataWindowForLevel_1(
    Imf_2_5_TiledOutputPart const * this_
    , int lx
    , int ly);


Imath_2_5_Box2i Imf_2_5_TiledOutputPart_dataWindowForTile(
    Imf_2_5_TiledOutputPart const * this_
    , int dx
    , int dy
    , int l);


Imath_2_5_Box2i Imf_2_5_TiledOutputPart_dataWindowForTile_1(
    Imf_2_5_TiledOutputPart const * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledOutputPart_writeTile(
    Imf_2_5_TiledOutputPart * this_
    , int dx
    , int dy
    , int l);


void Imf_2_5_TiledOutputPart_writeTile_1(
    Imf_2_5_TiledOutputPart * this_
    , int dx
    , int dy
    , int lx
    , int ly);


void Imf_2_5_TiledOutputPart_writeTiles(
    Imf_2_5_TiledOutputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly);


void Imf_2_5_TiledOutputPart_writeTiles_1(
    Imf_2_5_TiledOutputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l);


void Imf_2_5_TiledOutputPart_copyPixels(
    Imf_2_5_TiledOutputPart * this_
    , Imf_2_5_TiledInputFile * in);


void Imf_2_5_TiledOutputPart_copyPixels_1(
    Imf_2_5_TiledOutputPart * this_
    , Imf_2_5_InputFile * in);


void Imf_2_5_TiledOutputPart_copyPixels_2(
    Imf_2_5_TiledOutputPart * this_
    , Imf_2_5_TiledInputPart * in);


void Imf_2_5_TiledOutputPart_copyPixels_3(
    Imf_2_5_TiledOutputPart * this_
    , Imf_2_5_InputPart * in);


void Imf_2_5_TiledOutputPart_updatePreviewImage(
    Imf_2_5_TiledOutputPart * this_
    , Imf_2_5_PreviewRgba const * newPixels);


void Imf_2_5_TiledOutputPart_breakTile(
    Imf_2_5_TiledOutputPart * this_
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
