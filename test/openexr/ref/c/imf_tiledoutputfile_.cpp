#include <imf_tiledoutputfile_private_.h>

#include <imath_box_private_.h>
#include <imf_framebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_inputfile_private_.h>
#include <imf_inputpart_private_.h>
#include <imf_io_private_.h>
#include <imf_previewimage_private_.h>
#include <imf_tiledinputfile_private_.h>
#include <imf_tiledinputpart_private_.h>
#include <new>


void Imf_2_5_TiledOutputFile_TiledOutputFile(
    Imf_2_5_TiledOutputFile * this_
    , char const * fileName
    , Imf_2_5_Header const * header
    , int numThreads)
{
    new (this_) Imf_2_5::TiledOutputFile(fileName, to_cpp_ref(header), numThreads);
}

void Imf_2_5_TiledOutputFile_TiledOutputFile_1(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_OStream * os
    , Imf_2_5_Header const * header
    , int numThreads)
{
    new (this_) Imf_2_5::TiledOutputFile(to_cpp_ref(os), to_cpp_ref(header), numThreads);
}

void Imf_2_5_TiledOutputFile_dtor(
    Imf_2_5_TiledOutputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TiledOutputFile::~TiledOutputFile();
}

char const * Imf_2_5_TiledOutputFile_fileName(
    Imf_2_5_TiledOutputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_TiledOutputFile_header(
    Imf_2_5_TiledOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

void Imf_2_5_TiledOutputFile_setFrameBuffer(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_FrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

unsigned int Imf_2_5_TiledOutputFile_tileXSize(
    Imf_2_5_TiledOutputFile const * this_)
{
    return (to_cpp(this_)) -> tileXSize();
}

unsigned int Imf_2_5_TiledOutputFile_tileYSize(
    Imf_2_5_TiledOutputFile const * this_)
{
    return (to_cpp(this_)) -> tileYSize();
}

int Imf_2_5_TiledOutputFile_numLevels(
    Imf_2_5_TiledOutputFile const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_TiledOutputFile_numXLevels(
    Imf_2_5_TiledOutputFile const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_TiledOutputFile_numYLevels(
    Imf_2_5_TiledOutputFile const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

_Bool Imf_2_5_TiledOutputFile_isValidLevel(
    Imf_2_5_TiledOutputFile const * this_
    , int lx
    , int ly)
{
    return (to_cpp(this_)) -> isValidLevel(lx, ly);
}

int Imf_2_5_TiledOutputFile_levelWidth(
    Imf_2_5_TiledOutputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_TiledOutputFile_levelHeight(
    Imf_2_5_TiledOutputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

int Imf_2_5_TiledOutputFile_numXTiles(
    Imf_2_5_TiledOutputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> numXTiles(lx);
}

int Imf_2_5_TiledOutputFile_numYTiles(
    Imf_2_5_TiledOutputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> numYTiles(ly);
}

Imath_2_5_Box2i Imf_2_5_TiledOutputFile_dataWindowForLevel(
    Imf_2_5_TiledOutputFile const * this_
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i Imf_2_5_TiledOutputFile_dataWindowForLevel_1(
    Imf_2_5_TiledOutputFile const * this_
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

Imath_2_5_Box2i Imf_2_5_TiledOutputFile_dataWindowForTile(
    Imf_2_5_TiledOutputFile const * this_
    , int dx
    , int dy
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, l));
}

Imath_2_5_Box2i Imf_2_5_TiledOutputFile_dataWindowForTile_1(
    Imf_2_5_TiledOutputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, lx, ly));
}

void Imf_2_5_TiledOutputFile_writeTile(
    Imf_2_5_TiledOutputFile * this_
    , int dx
    , int dy
    , int l)
{
    (to_cpp(this_)) -> writeTile(dx, dy, l);
}

void Imf_2_5_TiledOutputFile_writeTile_1(
    Imf_2_5_TiledOutputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> writeTile(dx, dy, lx, ly);
}

void Imf_2_5_TiledOutputFile_writeTiles(
    Imf_2_5_TiledOutputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> writeTiles(dx1, dx2, dy1, dy2, lx, ly);
}

void Imf_2_5_TiledOutputFile_writeTiles_1(
    Imf_2_5_TiledOutputFile * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l)
{
    (to_cpp(this_)) -> writeTiles(dx1, dx2, dy1, dy2, l);
}

void Imf_2_5_TiledOutputFile_copyPixels(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_TiledInputFile * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_TiledOutputFile_copyPixels_1(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_TiledInputPart * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_TiledOutputFile_copyPixels_2(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_InputFile * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_TiledOutputFile_copyPixels_3(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_InputPart * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_TiledOutputFile_updatePreviewImage(
    Imf_2_5_TiledOutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels)
{
    (to_cpp(this_)) -> updatePreviewImage(to_cpp(newPixels));
}

void Imf_2_5_TiledOutputFile_breakTile(
    Imf_2_5_TiledOutputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly
    , int offset
    , int length
    , char c)
{
    (to_cpp(this_)) -> breakTile(dx, dy, lx, ly, offset, length, c);
}
