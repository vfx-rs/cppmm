#include <imf_tiledinputfile_private_.h>

#include <imath_box_private_.h>
#include <imf_framebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <new>


void Imf_2_5_TiledInputFile_TiledInputFile(
    Imf_2_5_TiledInputFile * this_
    , char const * fileName
    , int numThreads)
{
    new (this_) Imf_2_5::TiledInputFile(fileName, numThreads);
}

void Imf_2_5_TiledInputFile_TiledInputFile_1(
    Imf_2_5_TiledInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads)
{
    new (this_) Imf_2_5::TiledInputFile(to_cpp_ref(is), numThreads);
}

void Imf_2_5_TiledInputFile_dtor(
    Imf_2_5_TiledInputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TiledInputFile::~TiledInputFile();
}

char const * Imf_2_5_TiledInputFile_fileName(
    Imf_2_5_TiledInputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_TiledInputFile_header(
    Imf_2_5_TiledInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

int Imf_2_5_TiledInputFile_version(
    Imf_2_5_TiledInputFile const * this_)
{
    return (to_cpp(this_)) -> version();
}

void Imf_2_5_TiledInputFile_setFrameBuffer(
    Imf_2_5_TiledInputFile * this_
    , Imf_2_5_FrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_FrameBuffer const * Imf_2_5_TiledInputFile_frameBuffer(
    Imf_2_5_TiledInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

_Bool Imf_2_5_TiledInputFile_isComplete(
    Imf_2_5_TiledInputFile const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

unsigned int Imf_2_5_TiledInputFile_tileXSize(
    Imf_2_5_TiledInputFile const * this_)
{
    return (to_cpp(this_)) -> tileXSize();
}

unsigned int Imf_2_5_TiledInputFile_tileYSize(
    Imf_2_5_TiledInputFile const * this_)
{
    return (to_cpp(this_)) -> tileYSize();
}

int Imf_2_5_TiledInputFile_numLevels(
    Imf_2_5_TiledInputFile const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_TiledInputFile_numXLevels(
    Imf_2_5_TiledInputFile const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_TiledInputFile_numYLevels(
    Imf_2_5_TiledInputFile const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

_Bool Imf_2_5_TiledInputFile_isValidLevel(
    Imf_2_5_TiledInputFile const * this_
    , int lx
    , int ly)
{
    return (to_cpp(this_)) -> isValidLevel(lx, ly);
}

int Imf_2_5_TiledInputFile_levelWidth(
    Imf_2_5_TiledInputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_TiledInputFile_levelHeight(
    Imf_2_5_TiledInputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

int Imf_2_5_TiledInputFile_numXTiles(
    Imf_2_5_TiledInputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> numXTiles(lx);
}

int Imf_2_5_TiledInputFile_numYTiles(
    Imf_2_5_TiledInputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> numYTiles(ly);
}

Imath_2_5_Box2i Imf_2_5_TiledInputFile_dataWindowForLevel(
    Imf_2_5_TiledInputFile const * this_
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i Imf_2_5_TiledInputFile_dataWindowForLevel_1(
    Imf_2_5_TiledInputFile const * this_
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

Imath_2_5_Box2i Imf_2_5_TiledInputFile_dataWindowForTile(
    Imf_2_5_TiledInputFile const * this_
    , int dx
    , int dy
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, l));
}

Imath_2_5_Box2i Imf_2_5_TiledInputFile_dataWindowForTile_1(
    Imf_2_5_TiledInputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, lx, ly));
}

void Imf_2_5_TiledInputFile_readTile(
    Imf_2_5_TiledInputFile * this_
    , int dx
    , int dy
    , int l)
{
    (to_cpp(this_)) -> readTile(dx, dy, l);
}

void Imf_2_5_TiledInputFile_readTile_1(
    Imf_2_5_TiledInputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readTile(dx, dy, lx, ly);
}

void Imf_2_5_TiledInputFile_readTiles(
    Imf_2_5_TiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readTiles(dx1, dx2, dy1, dy2, lx, ly);
}

void Imf_2_5_TiledInputFile_readTiles_1(
    Imf_2_5_TiledInputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l)
{
    (to_cpp(this_)) -> readTiles(dx1, dx2, dy1, dy2, l);
}

void Imf_2_5_TiledInputFile_rawTileData(
    Imf_2_5_TiledInputFile * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char const * * pixelData
    , int * pixelDataSize)
{
    (to_cpp(this_)) -> rawTileData(*(dx), *(dy), *(lx), *(ly), *(pixelData), *(pixelDataSize));
}
