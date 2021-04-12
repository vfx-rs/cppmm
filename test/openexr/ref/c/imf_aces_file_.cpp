#include <imf_aces_file_private_.h>

#include <imath_box_private_.h>
#include <imath_vec_private_.h>
#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <imf_previewimage_private_.h>
#include <imf_rgba_private_.h>
#include <new>


void Imf_2_5_AcesOutputFile_dtor(
    Imf_2_5_AcesOutputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::AcesOutputFile::~AcesOutputFile();
}

void Imf_2_5_AcesOutputFile_setFrameBuffer(
    Imf_2_5_AcesOutputFile * this_
    , Imf_2_5_Rgba const * base
    , unsigned long xStride
    , unsigned long yStride)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp(base), xStride, yStride);
}

void Imf_2_5_AcesOutputFile_writePixels(
    Imf_2_5_AcesOutputFile * this_
    , int numScanLines)
{
    (to_cpp(this_)) -> writePixels(numScanLines);
}

int Imf_2_5_AcesOutputFile_currentScanLine(
    Imf_2_5_AcesOutputFile const * this_)
{
    return (to_cpp(this_)) -> currentScanLine();
}

Imf_2_5_Header const * Imf_2_5_AcesOutputFile_header(
    Imf_2_5_AcesOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

Imath_2_5_Box2i const * Imf_2_5_AcesOutputFile_displayWindow(
    Imf_2_5_AcesOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> displayWindow());
}

Imath_2_5_Box2i const * Imf_2_5_AcesOutputFile_dataWindow(
    Imf_2_5_AcesOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

float Imf_2_5_AcesOutputFile_pixelAspectRatio(
    Imf_2_5_AcesOutputFile const * this_)
{
    return (to_cpp(this_)) -> pixelAspectRatio();
}

Imath_2_5_V2f const Imf_2_5_AcesOutputFile_screenWindowCenter(
    Imf_2_5_AcesOutputFile const * this_)
{
    return to_c_copy((to_cpp(this_)) -> screenWindowCenter());
}

float Imf_2_5_AcesOutputFile_screenWindowWidth(
    Imf_2_5_AcesOutputFile const * this_)
{
    return (to_cpp(this_)) -> screenWindowWidth();
}

void Imf_2_5_AcesOutputFile_updatePreviewImage(
    Imf_2_5_AcesOutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels)
{
    (to_cpp(this_)) -> updatePreviewImage(to_cpp(newPixels));
}

void Imf_2_5_AcesInputFile_AcesInputFile(
    Imf_2_5_AcesInputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads)
{
    new (this_) Imf_2_5::AcesInputFile(to_cpp_ref(is), numThreads);
}

void Imf_2_5_AcesInputFile_dtor(
    Imf_2_5_AcesInputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::AcesInputFile::~AcesInputFile();
}

void Imf_2_5_AcesInputFile_setFrameBuffer(
    Imf_2_5_AcesInputFile * this_
    , Imf_2_5_Rgba * base
    , unsigned long xStride
    , unsigned long yStride)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp(base), xStride, yStride);
}

void Imf_2_5_AcesInputFile_readPixels(
    Imf_2_5_AcesInputFile * this_
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixels(scanLine1, scanLine2);
}

void Imf_2_5_AcesInputFile_readPixels_1(
    Imf_2_5_AcesInputFile * this_
    , int scanLine)
{
    (to_cpp(this_)) -> readPixels(scanLine);
}

Imf_2_5_Header const * Imf_2_5_AcesInputFile_header(
    Imf_2_5_AcesInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

Imath_2_5_Box2i const * Imf_2_5_AcesInputFile_displayWindow(
    Imf_2_5_AcesInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> displayWindow());
}

Imath_2_5_Box2i const * Imf_2_5_AcesInputFile_dataWindow(
    Imf_2_5_AcesInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

float Imf_2_5_AcesInputFile_pixelAspectRatio(
    Imf_2_5_AcesInputFile const * this_)
{
    return (to_cpp(this_)) -> pixelAspectRatio();
}

Imath_2_5_V2f const Imf_2_5_AcesInputFile_screenWindowCenter(
    Imf_2_5_AcesInputFile const * this_)
{
    return to_c_copy((to_cpp(this_)) -> screenWindowCenter());
}

float Imf_2_5_AcesInputFile_screenWindowWidth(
    Imf_2_5_AcesInputFile const * this_)
{
    return (to_cpp(this_)) -> screenWindowWidth();
}

char const * Imf_2_5_AcesInputFile_fileName(
    Imf_2_5_AcesInputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

_Bool Imf_2_5_AcesInputFile_isComplete(
    Imf_2_5_AcesInputFile const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

int Imf_2_5_AcesInputFile_version(
    Imf_2_5_AcesInputFile const * this_)
{
    return (to_cpp(this_)) -> version();
}
