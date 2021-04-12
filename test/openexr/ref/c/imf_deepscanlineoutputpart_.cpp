#include <imf_deepscanlineoutputpart_private_.h>

#include <imf_deepframebuffer_private_.h>
#include <imf_deepscanlineinputfile_private_.h>
#include <imf_deepscanlineinputpart_private_.h>
#include <imf_header_private_.h>
#include <imf_multipartoutputfile_private_.h>
#include <imf_previewimage_private_.h>
#include <new>


void Imf_2_5_DeepScanLineOutputPart_DeepScanLineOutputPart(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_MultiPartOutputFile * multiPartFile
    , int partNumber)
{
    new (this_) Imf_2_5::DeepScanLineOutputPart(to_cpp_ref(multiPartFile), partNumber);
}

char const * Imf_2_5_DeepScanLineOutputPart_fileName(
    Imf_2_5_DeepScanLineOutputPart const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_DeepScanLineOutputPart_header(
    Imf_2_5_DeepScanLineOutputPart const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

void Imf_2_5_DeepScanLineOutputPart_setFrameBuffer(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_DeepFrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_DeepFrameBuffer const * Imf_2_5_DeepScanLineOutputPart_frameBuffer(
    Imf_2_5_DeepScanLineOutputPart const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

void Imf_2_5_DeepScanLineOutputPart_writePixels(
    Imf_2_5_DeepScanLineOutputPart * this_
    , int numScanLines)
{
    (to_cpp(this_)) -> writePixels(numScanLines);
}

int Imf_2_5_DeepScanLineOutputPart_currentScanLine(
    Imf_2_5_DeepScanLineOutputPart const * this_)
{
    return (to_cpp(this_)) -> currentScanLine();
}

void Imf_2_5_DeepScanLineOutputPart_copyPixels(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_DeepScanLineInputFile * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_DeepScanLineOutputPart_copyPixels_1(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_DeepScanLineInputPart * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_DeepScanLineOutputPart_updatePreviewImage(
    Imf_2_5_DeepScanLineOutputPart * this_
    , Imf_2_5_PreviewRgba const * newPixels)
{
    (to_cpp(this_)) -> updatePreviewImage(to_cpp(newPixels));
}
