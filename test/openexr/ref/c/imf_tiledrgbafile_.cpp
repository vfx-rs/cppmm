#include <imf_tiledrgbafile_private_.h>

#include <imath_box_private_.h>
#include <imath_vec_private_.h>
#include <imf_framebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <imf_previewimage_private_.h>
#include <imf_rgba_private_.h>
#include <new>


void Imf_2_5_TiledRgbaOutputFile_dtor(
    Imf_2_5_TiledRgbaOutputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TiledRgbaOutputFile::~TiledRgbaOutputFile();
}

void Imf_2_5_TiledRgbaOutputFile_setFrameBuffer(
    Imf_2_5_TiledRgbaOutputFile * this_
    , Imf_2_5_Rgba const * base
    , unsigned long xStride
    , unsigned long yStride)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp(base), xStride, yStride);
}

Imf_2_5_Header const * Imf_2_5_TiledRgbaOutputFile_header(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

Imf_2_5_FrameBuffer const * Imf_2_5_TiledRgbaOutputFile_frameBuffer(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

Imath_2_5_Box2i const * Imf_2_5_TiledRgbaOutputFile_displayWindow(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> displayWindow());
}

Imath_2_5_Box2i const * Imf_2_5_TiledRgbaOutputFile_dataWindow(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

float Imf_2_5_TiledRgbaOutputFile_pixelAspectRatio(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> pixelAspectRatio();
}

Imath_2_5_V2f const Imf_2_5_TiledRgbaOutputFile_screenWindowCenter(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return to_c_copy((to_cpp(this_)) -> screenWindowCenter());
}

float Imf_2_5_TiledRgbaOutputFile_screenWindowWidth(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> screenWindowWidth();
}

unsigned int Imf_2_5_TiledRgbaOutputFile_tileXSize(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> tileXSize();
}

unsigned int Imf_2_5_TiledRgbaOutputFile_tileYSize(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> tileYSize();
}

int Imf_2_5_TiledRgbaOutputFile_numLevels(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_TiledRgbaOutputFile_numXLevels(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_TiledRgbaOutputFile_numYLevels(
    Imf_2_5_TiledRgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

_Bool Imf_2_5_TiledRgbaOutputFile_isValidLevel(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int lx
    , int ly)
{
    return (to_cpp(this_)) -> isValidLevel(lx, ly);
}

int Imf_2_5_TiledRgbaOutputFile_levelWidth(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_TiledRgbaOutputFile_levelHeight(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

int Imf_2_5_TiledRgbaOutputFile_numXTiles(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> numXTiles(lx);
}

int Imf_2_5_TiledRgbaOutputFile_numYTiles(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> numYTiles(ly);
}

Imath_2_5_Box2i Imf_2_5_TiledRgbaOutputFile_dataWindowForLevel(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i Imf_2_5_TiledRgbaOutputFile_dataWindowForLevel_1(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

Imath_2_5_Box2i Imf_2_5_TiledRgbaOutputFile_dataWindowForTile(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int dx
    , int dy
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, l));
}

Imath_2_5_Box2i Imf_2_5_TiledRgbaOutputFile_dataWindowForTile_1(
    Imf_2_5_TiledRgbaOutputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, lx, ly));
}

void Imf_2_5_TiledRgbaOutputFile_writeTile(
    Imf_2_5_TiledRgbaOutputFile * this_
    , int dx
    , int dy
    , int l)
{
    (to_cpp(this_)) -> writeTile(dx, dy, l);
}

void Imf_2_5_TiledRgbaOutputFile_writeTile_1(
    Imf_2_5_TiledRgbaOutputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> writeTile(dx, dy, lx, ly);
}

void Imf_2_5_TiledRgbaOutputFile_writeTiles(
    Imf_2_5_TiledRgbaOutputFile * this_
    , int dxMin
    , int dxMax
    , int dyMin
    , int dyMax
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> writeTiles(dxMin, dxMax, dyMin, dyMax, lx, ly);
}

void Imf_2_5_TiledRgbaOutputFile_writeTiles_1(
    Imf_2_5_TiledRgbaOutputFile * this_
    , int dxMin
    , int dxMax
    , int dyMin
    , int dyMax
    , int l)
{
    (to_cpp(this_)) -> writeTiles(dxMin, dxMax, dyMin, dyMax, l);
}

void Imf_2_5_TiledRgbaOutputFile_updatePreviewImage(
    Imf_2_5_TiledRgbaOutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels)
{
    (to_cpp(this_)) -> updatePreviewImage(to_cpp(newPixels));
}

void Imf_2_5_TiledRgbaOutputFile_breakTile(
    Imf_2_5_TiledRgbaOutputFile * this_
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

void Imf_2_5_TiledRgbaInputFile_TiledRgbaInputFile(
    Imf_2_5_TiledRgbaInputFile * this_
    , char const * name
    , int numThreads)
{
    new (this_) Imf_2_5::TiledRgbaInputFile(name, numThreads);
}

void Imf_2_5_TiledRgbaInputFile_TiledRgbaInputFile_1(
    Imf_2_5_TiledRgbaInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads)
{
    new (this_) Imf_2_5::TiledRgbaInputFile(to_cpp_ref(is), numThreads);
}

void Imf_2_5_TiledRgbaInputFile_dtor(
    Imf_2_5_TiledRgbaInputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::TiledRgbaInputFile::~TiledRgbaInputFile();
}

void Imf_2_5_TiledRgbaInputFile_setFrameBuffer(
    Imf_2_5_TiledRgbaInputFile * this_
    , Imf_2_5_Rgba * base
    , unsigned long xStride
    , unsigned long yStride)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp(base), xStride, yStride);
}

Imf_2_5_Header const * Imf_2_5_TiledRgbaInputFile_header(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

Imf_2_5_FrameBuffer const * Imf_2_5_TiledRgbaInputFile_frameBuffer(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

Imath_2_5_Box2i const * Imf_2_5_TiledRgbaInputFile_displayWindow(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> displayWindow());
}

Imath_2_5_Box2i const * Imf_2_5_TiledRgbaInputFile_dataWindow(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

float Imf_2_5_TiledRgbaInputFile_pixelAspectRatio(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> pixelAspectRatio();
}

Imath_2_5_V2f const Imf_2_5_TiledRgbaInputFile_screenWindowCenter(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return to_c_copy((to_cpp(this_)) -> screenWindowCenter());
}

float Imf_2_5_TiledRgbaInputFile_screenWindowWidth(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> screenWindowWidth();
}

char const * Imf_2_5_TiledRgbaInputFile_fileName(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

_Bool Imf_2_5_TiledRgbaInputFile_isComplete(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

int Imf_2_5_TiledRgbaInputFile_version(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> version();
}

unsigned int Imf_2_5_TiledRgbaInputFile_tileXSize(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> tileXSize();
}

unsigned int Imf_2_5_TiledRgbaInputFile_tileYSize(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> tileYSize();
}

int Imf_2_5_TiledRgbaInputFile_numLevels(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> numLevels();
}

int Imf_2_5_TiledRgbaInputFile_numXLevels(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> numXLevels();
}

int Imf_2_5_TiledRgbaInputFile_numYLevels(
    Imf_2_5_TiledRgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> numYLevels();
}

_Bool Imf_2_5_TiledRgbaInputFile_isValidLevel(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int lx
    , int ly)
{
    return (to_cpp(this_)) -> isValidLevel(lx, ly);
}

int Imf_2_5_TiledRgbaInputFile_levelWidth(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> levelWidth(lx);
}

int Imf_2_5_TiledRgbaInputFile_levelHeight(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> levelHeight(ly);
}

int Imf_2_5_TiledRgbaInputFile_numXTiles(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int lx)
{
    return (to_cpp(this_)) -> numXTiles(lx);
}

int Imf_2_5_TiledRgbaInputFile_numYTiles(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int ly)
{
    return (to_cpp(this_)) -> numYTiles(ly);
}

Imath_2_5_Box2i Imf_2_5_TiledRgbaInputFile_dataWindowForLevel(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(l));
}

Imath_2_5_Box2i Imf_2_5_TiledRgbaInputFile_dataWindowForLevel_1(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForLevel(lx, ly));
}

Imath_2_5_Box2i Imf_2_5_TiledRgbaInputFile_dataWindowForTile(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int dx
    , int dy
    , int l)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, l));
}

Imath_2_5_Box2i Imf_2_5_TiledRgbaInputFile_dataWindowForTile_1(
    Imf_2_5_TiledRgbaInputFile const * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    return to_c_copy((to_cpp(this_)) -> dataWindowForTile(dx, dy, lx, ly));
}

void Imf_2_5_TiledRgbaInputFile_readTile(
    Imf_2_5_TiledRgbaInputFile * this_
    , int dx
    , int dy
    , int l)
{
    (to_cpp(this_)) -> readTile(dx, dy, l);
}

void Imf_2_5_TiledRgbaInputFile_readTile_1(
    Imf_2_5_TiledRgbaInputFile * this_
    , int dx
    , int dy
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readTile(dx, dy, lx, ly);
}

void Imf_2_5_TiledRgbaInputFile_readTiles(
    Imf_2_5_TiledRgbaInputFile * this_
    , int dxMin
    , int dxMax
    , int dyMin
    , int dyMax
    , int lx
    , int ly)
{
    (to_cpp(this_)) -> readTiles(dxMin, dxMax, dyMin, dyMax, lx, ly);
}

void Imf_2_5_TiledRgbaInputFile_readTiles_1(
    Imf_2_5_TiledRgbaInputFile * this_
    , int dxMin
    , int dxMax
    , int dyMin
    , int dyMax
    , int l)
{
    (to_cpp(this_)) -> readTiles(dxMin, dxMax, dyMin, dyMax, l);
}
