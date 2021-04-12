#include <imf_deepscanlineoutputfile_private_.h>

#include <imf_deepframebuffer_private_.h>
#include <imf_deepscanlineinputfile_private_.h>
#include <imf_deepscanlineinputpart_private_.h>
#include <imf_header_private_.h>
#include <imf_io_private_.h>
#include <imf_previewimage_private_.h>
#include <new>


void Imf_2_5_DeepScanLineOutputFile_DeepScanLineOutputFile(
    Imf_2_5_DeepScanLineOutputFile * this_
    , char const * fileName
    , Imf_2_5_Header const * header
    , int numThreads)
{
    new (this_) Imf_2_5::DeepScanLineOutputFile(fileName, to_cpp_ref(header), numThreads);
}

void Imf_2_5_DeepScanLineOutputFile_DeepScanLineOutputFile_1(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_OStream * os
    , Imf_2_5_Header const * header
    , int numThreads)
{
    new (this_) Imf_2_5::DeepScanLineOutputFile(to_cpp_ref(os), to_cpp_ref(header), numThreads);
}

void Imf_2_5_DeepScanLineOutputFile_dtor(
    Imf_2_5_DeepScanLineOutputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::DeepScanLineOutputFile::~DeepScanLineOutputFile();
}

char const * Imf_2_5_DeepScanLineOutputFile_fileName(
    Imf_2_5_DeepScanLineOutputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_DeepScanLineOutputFile_header(
    Imf_2_5_DeepScanLineOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

void Imf_2_5_DeepScanLineOutputFile_setFrameBuffer(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepScanLineOutputFile_frameBuffer(
    Imf_2_5_DeepScanLineOutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

void Imf_2_5_DeepScanLineOutputFile_writePixels(
    Imf_2_5_DeepScanLineOutputFile * this_
    , int numScanLines)
{
    (to_cpp(this_)) -> writePixels(numScanLines);
}

int Imf_2_5_DeepScanLineOutputFile_currentScanLine(
    Imf_2_5_DeepScanLineOutputFile const * this_)
{
    return (to_cpp(this_)) -> currentScanLine();
}

void Imf_2_5_DeepScanLineOutputFile_copyPixels(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_DeepScanLineInputFile * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_DeepScanLineOutputFile_copyPixels_1(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_DeepScanLineInputPart * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_DeepScanLineOutputFile_updatePreviewImage(
    Imf_2_5_DeepScanLineOutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels)
{
    (to_cpp(this_)) -> updatePreviewImage(to_cpp(newPixels));
}
