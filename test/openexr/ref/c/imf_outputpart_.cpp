#include <imf_outputpart_private_.h>

#include <imf_framebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_inputfile_private_.h>
#include <imf_inputpart_private_.h>
#include <imf_multipartoutputfile_private_.h>
#include <imf_previewimage_private_.h>
#include <new>


void Imf_2_5_OutputPart_OutputPart(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_MultiPartOutputFile * multiPartFile
    , int partNumber)
{
    new (this_) Imf_2_5::OutputPart(to_cpp_ref(multiPartFile), partNumber);
}

char const * Imf_2_5_OutputPart_fileName(
    Imf_2_5_OutputPart const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_OutputPart_header(
    Imf_2_5_OutputPart const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

void Imf_2_5_OutputPart_setFrameBuffer(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_FrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_FrameBuffer const * Imf_2_5_OutputPart_frameBuffer(
    Imf_2_5_OutputPart const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

void Imf_2_5_OutputPart_writePixels(
    Imf_2_5_OutputPart * this_
    , int numScanLines)
{
    (to_cpp(this_)) -> writePixels(numScanLines);
}

int Imf_2_5_OutputPart_currentScanLine(
    Imf_2_5_OutputPart const * this_)
{
    return (to_cpp(this_)) -> currentScanLine();
}

void Imf_2_5_OutputPart_copyPixels(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_InputFile * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_OutputPart_copyPixels_1(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_InputPart * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_OutputPart_updatePreviewImage(
    Imf_2_5_OutputPart * this_
    , Imf_2_5_PreviewRgba const * newPixels)
{
    (to_cpp(this_)) -> updatePreviewImage(to_cpp(newPixels));
}

void Imf_2_5_OutputPart_breakScanLine(
    Imf_2_5_OutputPart * this_
    , int y
    , int offset
    , int length
    , char c)
{
    (to_cpp(this_)) -> breakScanLine(y, offset, length, c);
}
