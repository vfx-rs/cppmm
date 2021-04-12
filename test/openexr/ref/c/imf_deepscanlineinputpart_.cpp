#include <imf_deepscanlineinputpart_private_.h>

#include <imf_deepframebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_multipartinputfile_private_.h>
#include <new>


void Imf_2_5_DeepScanLineInputPart_DeepScanLineInputPart(
    Imf_2_5_DeepScanLineInputPart * this_
    , Imf_2_5_MultiPartInputFile * file
    , int partNumber)
{
    new (this_) Imf_2_5::DeepScanLineInputPart(to_cpp_ref(file), partNumber);
}

char const * Imf_2_5_DeepScanLineInputPart_fileName(
    Imf_2_5_DeepScanLineInputPart const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_DeepScanLineInputPart_header(
    Imf_2_5_DeepScanLineInputPart const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

int Imf_2_5_DeepScanLineInputPart_version(
    Imf_2_5_DeepScanLineInputPart const * this_)
{
    return (to_cpp(this_)) -> version();
}

void Imf_2_5_DeepScanLineInputPart_setFrameBuffer(
    Imf_2_5_DeepScanLineInputPart * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepScanLineInputPart_frameBuffer(
    Imf_2_5_DeepScanLineInputPart const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

_Bool Imf_2_5_DeepScanLineInputPart_isComplete(
    Imf_2_5_DeepScanLineInputPart const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

void Imf_2_5_DeepScanLineInputPart_readPixels(
    Imf_2_5_DeepScanLineInputPart * this_
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixels(scanLine1, scanLine2);
}

void Imf_2_5_DeepScanLineInputPart_readPixels_1(
    Imf_2_5_DeepScanLineInputPart * this_
    , int scanLine)
{
    (to_cpp(this_)) -> readPixels(scanLine);
}

void Imf_2_5_DeepScanLineInputPart_readPixels_2(
    Imf_2_5_DeepScanLineInputPart const * this_
    , char const * rawPixelData
    , Imf_2_5_DeepFrameBuffer const * frameBuffer
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixels(rawPixelData, to_cpp_ref(frameBuffer), scanLine1, scanLine2);
}

void Imf_2_5_DeepScanLineInputPart_rawPixelData(
    Imf_2_5_DeepScanLineInputPart * this_
    , int firstScanLine
    , char * pixelData
    , unsigned long * pixelDataSize)
{
    (to_cpp(this_)) -> rawPixelData(firstScanLine, pixelData, *(pixelDataSize));
}

void Imf_2_5_DeepScanLineInputPart_readPixelSampleCounts(
    Imf_2_5_DeepScanLineInputPart * this_
    , int scanline1
    , int scanline2)
{
    (to_cpp(this_)) -> readPixelSampleCounts(scanline1, scanline2);
}

void Imf_2_5_DeepScanLineInputPart_readPixelSampleCounts_1(
    Imf_2_5_DeepScanLineInputPart * this_
    , int scanline)
{
    (to_cpp(this_)) -> readPixelSampleCounts(scanline);
}

void Imf_2_5_DeepScanLineInputPart_readPixelSampleCounts_2(
    Imf_2_5_DeepScanLineInputPart const * this_
    , char const * rawdata
    , Imf_2_5_DeepFrameBuffer const * frameBuffer
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixelSampleCounts(rawdata, to_cpp_ref(frameBuffer), scanLine1, scanLine2);
}

int Imf_2_5_DeepScanLineInputPart_firstScanLineInChunk(
    Imf_2_5_DeepScanLineInputPart const * this_
    , int y)
{
    return (to_cpp(this_)) -> firstScanLineInChunk(y);
}

int Imf_2_5_DeepScanLineInputPart_lastScanLineInChunk(
    Imf_2_5_DeepScanLineInputPart const * this_
    , int y)
{
    return (to_cpp(this_)) -> lastScanLineInChunk(y);
}
