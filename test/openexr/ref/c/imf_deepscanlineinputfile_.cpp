#include <imf_deepscanlineinputfile_private_.h>

#include <imf_deepframebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <new>


void Imf_2_5_DeepScanLineInputFile_DeepScanLineInputFile(
    Imf_2_5_DeepScanLineInputFile * this_
    , char const * fileName
    , int numThreads)
{
    new (this_) Imf_2_5::DeepScanLineInputFile(fileName, numThreads);
}

void Imf_2_5_DeepScanLineInputFile_DeepScanLineInputFile_1(
    Imf_2_5_DeepScanLineInputFile * this_
    , Imf_2_5_Header const * header
    , Imf_2_5_IStream * is
    , int version
    , int numThreads)
{
    new (this_) Imf_2_5::DeepScanLineInputFile(to_cpp_ref(header), to_cpp(is), version, numThreads);
}

void Imf_2_5_DeepScanLineInputFile_dtor(
    Imf_2_5_DeepScanLineInputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::DeepScanLineInputFile::~DeepScanLineInputFile();
}

char const * Imf_2_5_DeepScanLineInputFile_fileName(
    Imf_2_5_DeepScanLineInputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_DeepScanLineInputFile_header(
    Imf_2_5_DeepScanLineInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

int Imf_2_5_DeepScanLineInputFile_version(
    Imf_2_5_DeepScanLineInputFile const * this_)
{
    return (to_cpp(this_)) -> version();
}

void Imf_2_5_DeepScanLineInputFile_setFrameBuffer(
    Imf_2_5_DeepScanLineInputFile * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepScanLineInputFile_frameBuffer(
    Imf_2_5_DeepScanLineInputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

_Bool Imf_2_5_DeepScanLineInputFile_isComplete(
    Imf_2_5_DeepScanLineInputFile const * this_)
{
    return (to_cpp(this_)) -> isComplete();
}

void Imf_2_5_DeepScanLineInputFile_readPixels(
    Imf_2_5_DeepScanLineInputFile * this_
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixels(scanLine1, scanLine2);
}

void Imf_2_5_DeepScanLineInputFile_readPixels_1(
    Imf_2_5_DeepScanLineInputFile * this_
    , int scanLine)
{
    (to_cpp(this_)) -> readPixels(scanLine);
}

void Imf_2_5_DeepScanLineInputFile_readPixels_2(
    Imf_2_5_DeepScanLineInputFile const * this_
    , char const * rawPixelData
    , Imf_2_5_DeepFrameBuffer const * frameBuffer
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixels(rawPixelData, to_cpp_ref(frameBuffer), scanLine1, scanLine2);
}

void Imf_2_5_DeepScanLineInputFile_rawPixelData(
    Imf_2_5_DeepScanLineInputFile * this_
    , int firstScanLine
    , char * pixelData
    , unsigned long * pixelDataSize)
{
    (to_cpp(this_)) -> rawPixelData(firstScanLine, pixelData, *(pixelDataSize));
}

int Imf_2_5_DeepScanLineInputFile_firstScanLineInChunk(
    Imf_2_5_DeepScanLineInputFile const * this_
    , int y)
{
    return (to_cpp(this_)) -> firstScanLineInChunk(y);
}

int Imf_2_5_DeepScanLineInputFile_lastScanLineInChunk(
    Imf_2_5_DeepScanLineInputFile const * this_
    , int y)
{
    return (to_cpp(this_)) -> lastScanLineInChunk(y);
}

void Imf_2_5_DeepScanLineInputFile_readPixelSampleCounts(
    Imf_2_5_DeepScanLineInputFile * this_
    , int scanline1
    , int scanline2)
{
    (to_cpp(this_)) -> readPixelSampleCounts(scanline1, scanline2);
}

void Imf_2_5_DeepScanLineInputFile_readPixelSampleCounts_1(
    Imf_2_5_DeepScanLineInputFile * this_
    , int scanline)
{
    (to_cpp(this_)) -> readPixelSampleCounts(scanline);
}

void Imf_2_5_DeepScanLineInputFile_readPixelSampleCounts_2(
    Imf_2_5_DeepScanLineInputFile const * this_
    , char const * rawdata
    , Imf_2_5_DeepFrameBuffer const * frameBuffer
    , int scanLine1
    , int scanLine2)
{
    (to_cpp(this_)) -> readPixelSampleCounts(rawdata, to_cpp_ref(frameBuffer), scanLine1, scanLine2);
}
