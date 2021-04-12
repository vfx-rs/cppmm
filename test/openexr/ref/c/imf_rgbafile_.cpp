#include <imf_rgbafile_private_.h>

#include <imath_box_private_.h>
#include <imath_vec_private_.h>
#include <imf_framebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <imf_previewimage_private_.h>
#include <imf_rgba_private_.h>
#include <new>


void Imf_2_5_RgbaOutputFile_dtor(
    Imf_2_5_RgbaOutputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::RgbaOutputFile::~RgbaOutputFile();
}

void Imf_2_5_RgbaOutputFile_setFrameBuffer(
    Imf_2_5_RgbaOutputFile * this_
    , Imf_2_5_Rgba const * base
    , unsigned long xStride
    , unsigned long yStride)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp(base), xStride, yStride);
}

void Imf_2_5_RgbaOutputFile_writePixels(
    Imf_2_5_RgbaOutputFile * this_
    , int numScanLines)
{
    (to_cpp(this_)) -> writePixels(numScanLines);
}

int Imf_2_5_RgbaOutputFile_currentScanLine(
    Imf_2_5_RgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> currentScanLine();
}

Imf_2_5_Header const * Imf_2_5_RgbaOutputFile_header(
    Imf_2_5_RgbaOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

Imf_2_5_FrameBuffer const * Imf_2_5_RgbaOutputFile_frameBuffer(
    Imf_2_5_RgbaOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

Imath_2_5_Box2i const * Imf_2_5_RgbaOutputFile_displayWindow(
    Imf_2_5_RgbaOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> displayWindow());
}

Imath_2_5_Box2i const * Imf_2_5_RgbaOutputFile_dataWindow(
    Imf_2_5_RgbaOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

float Imf_2_5_RgbaOutputFile_pixelAspectRatio(
    Imf_2_5_RgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> pixelAspectRatio();
}

Imath_2_5_V2f const Imf_2_5_RgbaOutputFile_screenWindowCenter(
    Imf_2_5_RgbaOutputFile const * this_)
{
    return to_c_copy((to_cpp(this_)) -> screenWindowCenter());
}

float Imf_2_5_RgbaOutputFile_screenWindowWidth(
    Imf_2_5_RgbaOutputFile const * this_)
{
    return (to_cpp(this_)) -> screenWindowWidth();
}

void Imf_2_5_RgbaOutputFile_updatePreviewImage(
    Imf_2_5_RgbaOutputFile * this_
    , Imf_2_5_PreviewRgba const * preview)
{
    (to_cpp(this_)) -> updatePreviewImage(to_cpp(preview));
}

void Imf_2_5_RgbaOutputFile_setYCRounding(
    Imf_2_5_RgbaOutputFile * this_
    , unsigned int roundY
    , unsigned int roundC)
{
    (to_cpp(this_)) -> setYCRounding(roundY, roundC);
}

void Imf_2_5_RgbaOutputFile_breakScanLine(
    Imf_2_5_RgbaOutputFile * this_
    , int y
    , int offset
    , int length
    , char c)
{
    (to_cpp(this_)) -> breakScanLine(y, offset, length, c);
}

void Imf_2_5_RgbaInputFile_RgbaInputFile(
    Imf_2_5_RgbaInputFile * this_
    , char const * name
    , int numThreads)
{
    new (this_) Imf_2_5::RgbaInputFile(name, numThreads);
}

void Imf_2_5_RgbaInputFile_RgbaInputFile_1(
    Imf_2_5_RgbaInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads)
{
    new (this_) Imf_2_5::RgbaInputFile(to_cpp_ref(is), numThreads);
}

void Imf_2_5_RgbaInputFile_dtor(
    Imf_2_5_RgbaInputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::RgbaInputFile::~RgbaInputFile();
}

void Imf_2_5_RgbaInputFile_setFrameBuffer(
    Imf_2_5_RgbaInputFile * this_
    , Imf_2_5_Rgba * base
    , unsigned long xStride
    , unsigned long yStride)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp(base), xStride, yStride);
}

void Imf_2_5_RgbaInputFile_readPixels(
    Imf_2_5_RgbaInputFile * this_
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixels(scanLine1, scanLine2);
}

void Imf_2_5_RgbaInputFile_readPixels_1(
    Imf_2_5_RgbaInputFile * this_
    , int scanLine)
{
    (to_cpp(this_)) -> readPixels(scanLine);
}

Imf_2_5_Header const * Imf_2_5_RgbaInputFile_header(
    Imf_2_5_RgbaInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

Imf_2_5_FrameBuffer const * Imf_2_5_RgbaInputFile_frameBuffer(
    Imf_2_5_RgbaInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

Imath_2_5_Box2i const * Imf_2_5_RgbaInputFile_displayWindow(
    Imf_2_5_RgbaInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> displayWindow());
}

Imath_2_5_Box2i const * Imf_2_5_RgbaInputFile_dataWindow(
    Imf_2_5_RgbaInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

float Imf_2_5_RgbaInputFile_pixelAspectRatio(
    Imf_2_5_RgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> pixelAspectRatio();
}

Imath_2_5_V2f const Imf_2_5_RgbaInputFile_screenWindowCenter(
    Imf_2_5_RgbaInputFile const * this_)
{
    return to_c_copy((to_cpp(this_)) -> screenWindowCenter());
}

float Imf_2_5_RgbaInputFile_screenWindowWidth(
    Imf_2_5_RgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> screenWindowWidth();
}

char const * Imf_2_5_RgbaInputFile_fileName(
    Imf_2_5_RgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

_Bool Imf_2_5_RgbaInputFile_isComplete(
    Imf_2_5_RgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

int Imf_2_5_RgbaInputFile_version(
    Imf_2_5_RgbaInputFile const * this_)
{
    return (to_cpp(this_)) -> version();
}
