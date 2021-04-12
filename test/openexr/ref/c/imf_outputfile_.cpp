#include <imf_outputfile_private_.h>

#include <imf_framebuffer_private_.h>
#include <imf_header_private_.h>
#include <imf_inputfile_private_.h>
#include <imf_inputpart_private_.h>
#include <imf_io_private_.h>
#include <imf_previewimage_private_.h>
#include <new>


void Imf_2_5_OutputFile_OutputFile(
    Imf_2_5_OutputFile * this_
    , char const * fileName
    , Imf_2_5_Header const * header
    , int numThreads)
{
    new (this_) Imf_2_5::OutputFile(fileName, to_cpp_ref(header), numThreads);
}

void Imf_2_5_OutputFile_OutputFile_1(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_OStream * os
    , Imf_2_5_Header const * header
    , int numThreads)
{
    new (this_) Imf_2_5::OutputFile(to_cpp_ref(os), to_cpp_ref(header), numThreads);
}

void Imf_2_5_OutputFile_dtor(
    Imf_2_5_OutputFile * this_)
{
    (to_cpp(this_)) -> Imf_2_5::OutputFile::~OutputFile();
}

char const * Imf_2_5_OutputFile_fileName(
    Imf_2_5_OutputFile const * this_)
{
    return (to_cpp(this_)) -> fileName();
}

Imf_2_5_Header const * Imf_2_5_OutputFile_header(
    Imf_2_5_OutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> header());
}

void Imf_2_5_OutputFile_setFrameBuffer(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_FrameBuffer const * frameBuffer)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(frameBuffer));
}

Imf_2_5_FrameBuffer const * Imf_2_5_OutputFile_frameBuffer(
    Imf_2_5_OutputFile const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

void Imf_2_5_OutputFile_writePixels(
    Imf_2_5_OutputFile * this_
    , int numScanLines)
{
    (to_cpp(this_)) -> writePixels(numScanLines);
}

int Imf_2_5_OutputFile_currentScanLine(
    Imf_2_5_OutputFile const * this_)
{
    return (to_cpp(this_)) -> currentScanLine();
}

void Imf_2_5_OutputFile_copyPixels(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_InputFile * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_OutputFile_copyPixels_1(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_InputPart * in)
{
    (to_cpp(this_)) -> copyPixels(to_cpp_ref(in));
}

void Imf_2_5_OutputFile_updatePreviewImage(
    Imf_2_5_OutputFile * this_
    , Imf_2_5_PreviewRgba const * newPixels)
{
    (to_cpp(this_)) -> updatePreviewImage(to_cpp(newPixels));
}

void Imf_2_5_OutputFile_breakScanLine(
    Imf_2_5_OutputFile * this_
    , int y
    , int offset
    , int length
    , char c)
{
    (to_cpp(this_)) -> breakScanLine(y, offset, length, c);
}
