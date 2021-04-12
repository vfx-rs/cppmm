#include <imf_deeptiledoutputpart_private_.h>

#include <imath_box_private_.h>
#include <imf_deepframebuffer_private_.h>
#include <imf_deeptiledinputfile_private_.h>
#include <imf_deeptiledinputpart_private_.h>
#include <imf_header_private_.h>
#include <imf_multipartoutputfile_private_.h>
#include <imf_previewimage_private_.h>
#include <new>


void Imf_2_5_DeepTiledOutputPart_DeepTiledOutputPart(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_MultiPartOutputFile * multiPartFile
    , int partNumber)
{
    new (this_) Imf_2_5::DeepTiledOutputPart(to_cpp_ref(multiPartFile), partNumber);
}

char const * Imf_2_5_DeepTiledOutputPart_fileName(
    Imf_2_5_DeepTiledOutputPart const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_DeepTiledOutputPart_header(
    Imf_2_5_DeepTiledOutputPart const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

void Imf_2_5_DeepTiledOutputPart_setFrameBuffer(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepTiledOutputPart_frameBuffer(
    Imf_2_5_DeepTiledOutputPart const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

unsigned int Imf_2_5_DeepTiledOutputPart_tileXSize(
    Imf_2_5_DeepTiledOutputPart const * this_)
{
    return (to_cpp(this_)) -> tileXSize();
}

unsigned int Imf_2_5_DeepTiledOutputPart_tileYSize(
    Imf_2_5_DeepTiledOutputPart const * this_)
{
    return (to_cpp(this_)) -> tileYSize();
}

int Imf_2_5_DeepTiledOutputPart_numLevels(
    Imf_2_5_DeepTiledOutputPart const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_DeepTiledOutputPart_numXLevels(
    Imf_2_5_DeepTiledOutputPart const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_DeepTiledOutputPart_numYLevels(
    Imf_2_5_DeepTiledOutputPart const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

_Bool Imf_2_5_DeepTiledOutputPart_isValidLevel(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int lx
    , int ly)
{
    return (to_cpp(this_)) -> isValidLevel(lx, ly);
}

int Imf_2_5_DeepTiledOutputPart_levelWidth(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_DeepTiledOutputPart_levelHeight(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

int Imf_2_5_DeepTiledOutputPart_numXTiles(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int lx)
{
    return (to_cpp(this_)) -> numXTiles(lx);
}

int Imf_2_5_DeepTiledOutputPart_numYTiles(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int ly)
{
    return (to_cpp(this_)) -> numYTiles(ly);
}

Imath_2_5_Box2i Imf_2_5_DeepTiledOutputPart_dataWindowForLevel(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i Imf_2_5_DeepTiledOutputPart_dataWindowForLevel_1(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

Imath_2_5_Box2i Imf_2_5_DeepTiledOutputPart_dataWindowForTile(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int dx
    , int dy
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, l));
}

Imath_2_5_Box2i Imf_2_5_DeepTiledOutputPart_dataWindowForTile_1(
    Imf_2_5_DeepTiledOutputPart const * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, lx, ly));
}

void Imf_2_5_DeepTiledOutputPart_writeTile(
    Imf_2_5_DeepTiledOutputPart * this_
    , int dx
    , int dy
    , int l)
{
    (to_cpp(this_)) -> writeTile(dx, dy, l);
}

void Imf_2_5_DeepTiledOutputPart_writeTile_1(
    Imf_2_5_DeepTiledOutputPart * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> writeTile(dx, dy, lx, ly);
}

void Imf_2_5_DeepTiledOutputPart_writeTiles(
    Imf_2_5_DeepTiledOutputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> writeTiles(dx1, dx2, dy1, dy2, lx, ly);
}

void Imf_2_5_DeepTiledOutputPart_writeTiles_1(
    Imf_2_5_DeepTiledOutputPart * this_
    , int dx1
    , int dx2
    , int dy1
    , int dy2
    , int l)
{
    (to_cpp(this_)) -> writeTiles(dx1, dx2, dy1, dy2, l);
}

void Imf_2_5_DeepTiledOutputPart_copyPixels(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_DeepTiledInputFile * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_DeepTiledOutputPart_copyPixels_1(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_DeepTiledInputPart * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_DeepTiledOutputPart_updatePreviewImage(
    Imf_2_5_DeepTiledOutputPart * this_
    , Imf_2_5_PreviewRgba const * newPixels)
{
    (to_cpp(this_)) -> updatePreviewImage(to_cpp(newPixels));
}

void Imf_2_5_DeepTiledOutputPart_breakTile(
    Imf_2_5_DeepTiledOutputPart * this_
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
