#include <imf_inputpart_private_.h>

#include <imf_framebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_multipartinputfile_private_.h>
#include <new>


void Imf_2_5_InputPart_InputPart(
    Imf_2_5_InputPart * this_
    , Imf_2_5_MultiPartInputFile * multiPartFile
    , int partNumber)
{
    new (this_) Imf_2_5::InputPart(to_cpp_ref(multiPartFile), partNumber);
}

char const * Imf_2_5_InputPart_fileName(
    Imf_2_5_InputPart const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_InputPart_header(
    Imf_2_5_InputPart const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

int Imf_2_5_InputPart_version(
    Imf_2_5_InputPart const * this_)
{
    return (to_cpp(this_)) -> version();
}

void Imf_2_5_InputPart_setFrameBuffer(
    Imf_2_5_InputPart * this_
    , Imf_2_5_FrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_FrameBuffer const * Imf_2_5_InputPart_frameBuffer(
    Imf_2_5_InputPart const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

_Bool Imf_2_5_InputPart_isComplete(
    Imf_2_5_InputPart const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

_Bool Imf_2_5_InputPart_isOptimizationEnabled(
    Imf_2_5_InputPart const * this_)
{
    return (to_cpp(this_)) -> isOptimizationEnabled();
}

void Imf_2_5_InputPart_readPixels(
    Imf_2_5_InputPart * this_
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixels(scanLine1, scanLine2);
}

void Imf_2_5_InputPart_readPixels_1(
    Imf_2_5_InputPart * this_
    , int scanLine)
{
    (to_cpp(this_)) -> readPixels(scanLine);
}

void Imf_2_5_InputPart_rawPixelData(
    Imf_2_5_InputPart * this_
    , int firstScanLine
    , char const * * pixelData
    , int * pixelDataSize)
{
    (to_cpp(this_)) -> rawPixelData(firstScanLine, *(pixelData), *(pixelDataSize));
}

void Imf_2_5_InputPart_rawPixelDataToBuffer(
    Imf_2_5_InputPart const * this_
    , int scanLine
    , char * pixelData
    , int * pixelDataSize)
{
    (to_cpp(this_)) -> rawPixelDataToBuffer(scanLine, pixelData, *(pixelDataSize));
}

void Imf_2_5_InputPart_rawTileData(
    Imf_2_5_InputPart * this_
    , int * dx
    , int * dy
    , int * lx
    , int * ly
    , char const * * pixelData
    , int * pixelDataSize)
{
    (to_cpp(this_)) -> rawTileData(*(dx), *(dy), *(lx), *(ly), *(pixelData), *(pixelDataSize));
}
