#include <imf_inputfile_private_.h>

#include <imf_framebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <new>


void Imf_2_5_InputFile_InputFile(
    Imf_2_5_InputFile * this_
    , char const * fileName
    , int numThreads)
{
    new (this_) Imf_2_5::InputFile(fileName, numThreads);
}

void Imf_2_5_InputFile_InputFile_1(
    Imf_2_5_InputFile * this_
    , Imf_2_5_IStream * is
    , int numThreads)
{
    new (this_) Imf_2_5::InputFile(to_cpp_ref(is), numThreads);
}

void Imf_2_5_InputFile_dtor(
    Imf_2_5_InputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::InputFile::~InputFile();
}

char const * Imf_2_5_InputFile_fileName(
    Imf_2_5_InputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_InputFile_header(
    Imf_2_5_InputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

int Imf_2_5_InputFile_version(
    Imf_2_5_InputFile const * this_)
{
    return (to_cpp(this_)) -> version();
}

void Imf_2_5_InputFile_setFrameBuffer(
    Imf_2_5_InputFile * this_
    , Imf_2_5_FrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_FrameBuffer const * Imf_2_5_InputFile_frameBuffer(
    Imf_2_5_InputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

_Bool Imf_2_5_InputFile_isComplete(
    Imf_2_5_InputFile const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

_Bool Imf_2_5_InputFile_isOptimizationEnabled(
    Imf_2_5_InputFile const * this_)
{
    return (to_cpp(this_)) -> isOptimizationEnabled();
}

void Imf_2_5_InputFile_readPixels(
    Imf_2_5_InputFile * this_
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixels(scanLine1, scanLine2);
}

void Imf_2_5_InputFile_readPixels_1(
    Imf_2_5_InputFile * this_
    , int scanLine)
{
    (to_cpp(this_)) -> readPixels(scanLine);
}

void Imf_2_5_InputFile_rawPixelData(
    Imf_2_5_InputFile * this_
    , int firstScanLine
    , char const * * pixelData
    , int * pixelDataSize)
{
    (to_cpp(this_)) -> rawPixelData(firstScanLine, *(pixelData), *(pixelDataSize));
}

void Imf_2_5_InputFile_rawPixelDataToBuffer(
    Imf_2_5_InputFile const * this_
    , int scanLine
    , char * pixelData
    , int * pixelDataSize)
{
    (to_cpp(this_)) -> rawPixelDataToBuffer(scanLine, pixelData, *(pixelDataSize));
}

void Imf_2_5_InputFile_rawTileData(
    Imf_2_5_InputFile * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char const * * pixelData
    , int * pixelDataSize)
{
    (to_cpp(this_)) -> rawTileData(*(dx), *(dy), *(lx), *(ly), *(pixelData), *(pixelDataSize));
}
