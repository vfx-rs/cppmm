#include <imf_deeptiledinputfile_private_.h>

#include <imath_box_private_.h>
#include <imf_deepframebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <new>


void Imf_2_5_DeepTiledInputFile_DeepTiledInputFile(
    Imf_2_5_DeepTiledInputFile * this_
    , char const * fileName
    , int numThreads)
{
    new (this_) Imf_2_5::DeepTiledInputFile(fileName, numThreads);
}

void Imf_2_5_DeepTiledInputFile_DeepTiledInputFile_1(
    Imf_2_5_DeepTiledInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads)
{
    new (this_) Imf_2_5::DeepTiledInputFile(to_cpp_ref(is), numThreads);
}

void Imf_2_5_DeepTiledInputFile_dtor(
    Imf_2_5_DeepTiledInputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::DeepTiledInputFile::~DeepTiledInputFile();
}

char const * Imf_2_5_DeepTiledInputFile_fileName(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_DeepTiledInputFile_header(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

int Imf_2_5_DeepTiledInputFile_version(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return (to_cpp(this_)) -> version();
}

void Imf_2_5_DeepTiledInputFile_setFrameBuffer(
    Imf_2_5_DeepTiledInputFile * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepTiledInputFile_frameBuffer(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

_Bool Imf_2_5_DeepTiledInputFile_isComplete(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

unsigned int Imf_2_5_DeepTiledInputFile_tileXSize(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return (to_cpp(this_)) -> tileXSize();
}

unsigned int Imf_2_5_DeepTiledInputFile_tileYSize(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return (to_cpp(this_)) -> tileYSize();
}

int Imf_2_5_DeepTiledInputFile_numLevels(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_DeepTiledInputFile_numXLevels(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_DeepTiledInputFile_numYLevels(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

_Bool Imf_2_5_DeepTiledInputFile_isValidLevel(
    Imf_2_5_DeepTiledInputFile const * this_
    , int lx
    , int ly)
{
    return (to_cpp(this_)) -> isValidLevel(lx, ly);
}

unsigned long Imf_2_5_DeepTiledInputFile_totalTiles(
    Imf_2_5_DeepTiledInputFile const * this_)
{
    return (to_cpp(this_)) -> totalTiles();
}

int Imf_2_5_DeepTiledInputFile_levelWidth(
    Imf_2_5_DeepTiledInputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_DeepTiledInputFile_levelHeight(
    Imf_2_5_DeepTiledInputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

int Imf_2_5_DeepTiledInputFile_numXTiles(
    Imf_2_5_DeepTiledInputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> numXTiles(lx);
}

int Imf_2_5_DeepTiledInputFile_numYTiles(
    Imf_2_5_DeepTiledInputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> numYTiles(ly);
}

Imath_2_5_Box2i Imf_2_5_DeepTiledInputFile_dataWindowForLevel(
    Imf_2_5_DeepTiledInputFile const * this_
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i Imf_2_5_DeepTiledInputFile_dataWindowForLevel_1(
    Imf_2_5_DeepTiledInputFile const * this_
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

Imath_2_5_Box2i Imf_2_5_DeepTiledInputFile_dataWindowForTile(
    Imf_2_5_DeepTiledInputFile const * this_
    , int dx
    , int dy
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, l));
}

Imath_2_5_Box2i Imf_2_5_DeepTiledInputFile_dataWindowForTile_1(
    Imf_2_5_DeepTiledInputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, lx, ly));
}

void Imf_2_5_DeepTiledInputFile_readTile(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx
    , int dy
    , int l)
{
    (to_cpp(this_)) -> readTile(dx, dy, l);
}

void Imf_2_5_DeepTiledInputFile_readTile_1(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readTile(dx, dy, lx, ly);
}

void Imf_2_5_DeepTiledInputFile_readTiles(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readTiles(dx1, dx2, dy1, dy2, lx, ly);
}

void Imf_2_5_DeepTiledInputFile_readTiles_1(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l)
{
    (to_cpp(this_)) -> readTiles(dx1, dx2, dy1, dy2, l);
}

void Imf_2_5_DeepTiledInputFile_rawTileData(
    Imf_2_5_DeepTiledInputFile const * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char * pixelData
    , unsigned long * dataSize)
{
    (to_cpp(this_)) -> rawTileData(*(dx), *(dy), *(lx), *(ly), pixelData, *(dataSize));
}

void Imf_2_5_DeepTiledInputFile_readPixelSampleCount(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx
    , int dy
    , int l)
{
    (to_cpp(this_)) -> readPixelSampleCount(dx, dy, l);
}

void Imf_2_5_DeepTiledInputFile_readPixelSampleCount_1(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readPixelSampleCount(dx, dy, lx, ly);
}

void Imf_2_5_DeepTiledInputFile_readPixelSampleCounts(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readPixelSampleCounts(dx1, dx2, dy1, dy2, lx, ly);
}

void Imf_2_5_DeepTiledInputFile_readPixelSampleCounts_1(
    Imf_2_5_DeepTiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l)
{
    (to_cpp(this_)) -> readPixelSampleCounts(dx1, dx2, dy1, dy2, l);
}
