#include <imf_deeptiledinputpart_private_.h>

#include <imath_box_private_.h>
#include <imf_deepframebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_multipartinputfile_private_.h>
#include <new>


void Imf_2_5_DeepTiledInputPart_DeepTiledInputPart(
    Imf_2_5_DeepTiledInputPart * this_
    , Imf_2_5_MultiPartInputFile * multiPartFile
    , int partNumber)
{
    new (this_) Imf_2_5::DeepTiledInputPart(to_cpp_ref(multiPartFile), partNumber);
}

char const * Imf_2_5_DeepTiledInputPart_fileName(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_DeepTiledInputPart_header(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

int Imf_2_5_DeepTiledInputPart_version(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return (to_cpp(this_)) -> version();
}

void Imf_2_5_DeepTiledInputPart_setFrameBuffer(
    Imf_2_5_DeepTiledInputPart * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepTiledInputPart_frameBuffer(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

_Bool Imf_2_5_DeepTiledInputPart_isComplete(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

unsigned int Imf_2_5_DeepTiledInputPart_tileXSize(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return (to_cpp(this_)) -> tileXSize();
}

unsigned int Imf_2_5_DeepTiledInputPart_tileYSize(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return (to_cpp(this_)) -> tileYSize();
}

int Imf_2_5_DeepTiledInputPart_numLevels(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_DeepTiledInputPart_numXLevels(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_DeepTiledInputPart_numYLevels(
    Imf_2_5_DeepTiledInputPart const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

_Bool Imf_2_5_DeepTiledInputPart_isValidLevel(
    Imf_2_5_DeepTiledInputPart const * this_
    , int lx
    , int ly)
{
    return (to_cpp(this_)) -> isValidLevel(lx, ly);
}

int Imf_2_5_DeepTiledInputPart_levelWidth(
    Imf_2_5_DeepTiledInputPart const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_DeepTiledInputPart_levelHeight(
    Imf_2_5_DeepTiledInputPart const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

int Imf_2_5_DeepTiledInputPart_numXTiles(
    Imf_2_5_DeepTiledInputPart const * this_
    , int lx)
{
    return (to_cpp(this_)) -> numXTiles(lx);
}

int Imf_2_5_DeepTiledInputPart_numYTiles(
    Imf_2_5_DeepTiledInputPart const * this_
    , int ly)
{
    return (to_cpp(this_)) -> numYTiles(ly);
}

Imath_2_5_Box2i Imf_2_5_DeepTiledInputPart_dataWindowForLevel(
    Imf_2_5_DeepTiledInputPart const * this_
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i Imf_2_5_DeepTiledInputPart_dataWindowForLevel_1(
    Imf_2_5_DeepTiledInputPart const * this_
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

Imath_2_5_Box2i Imf_2_5_DeepTiledInputPart_dataWindowForTile(
    Imf_2_5_DeepTiledInputPart const * this_
    , int dx
    , int dy
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, l));
}

Imath_2_5_Box2i Imf_2_5_DeepTiledInputPart_dataWindowForTile_1(
    Imf_2_5_DeepTiledInputPart const * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, lx, ly));
}

void Imf_2_5_DeepTiledInputPart_readTile(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx
    , int dy
    , int l)
{
    (to_cpp(this_)) -> readTile(dx, dy, l);
}

void Imf_2_5_DeepTiledInputPart_readTile_1(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readTile(dx, dy, lx, ly);
}

void Imf_2_5_DeepTiledInputPart_readTiles(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readTiles(dx1, dx2, dy1, dy2, lx, ly);
}

void Imf_2_5_DeepTiledInputPart_readTiles_1(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l)
{
    (to_cpp(this_)) -> readTiles(dx1, dx2, dy1, dy2, l);
}

void Imf_2_5_DeepTiledInputPart_rawTileData(
    Imf_2_5_DeepTiledInputPart const * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char * data
    , unsigned long * dataSize)
{
    (to_cpp(this_)) -> rawTileData(*(dx), *(dy), *(lx), *(ly), data, *(dataSize));
}

void Imf_2_5_DeepTiledInputPart_readPixelSampleCount(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx
    , int dy
    , int l)
{
    (to_cpp(this_)) -> readPixelSampleCount(dx, dy, l);
}

void Imf_2_5_DeepTiledInputPart_readPixelSampleCount_1(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readPixelSampleCount(dx, dy, lx, ly);
}

void Imf_2_5_DeepTiledInputPart_readPixelSampleCounts(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readPixelSampleCounts(dx1, dx2, dy1, dy2, lx, ly);
}

void Imf_2_5_DeepTiledInputPart_readPixelSampleCounts_1(
    Imf_2_5_DeepTiledInputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l)
{
    (to_cpp(this_)) -> readPixelSampleCounts(dx1, dx2, dy1, dy2, l);
}
