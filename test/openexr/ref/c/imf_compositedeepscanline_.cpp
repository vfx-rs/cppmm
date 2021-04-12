#include <imf_compositedeepscanline_private_.h>

#include <imath_box_private_.h>
#include <imf_deepcompositing_private_.h>
#include <imf_deepscanlineinputfile_private_.h>
#include <imf_deepscanlineinputpart_private_.h>
#include <imf_framebuffer_private_.h>
#include <new>


void Imf_2_5_CompositeDeepScanLine_CompositeDeepScanLine(
    Imf_2_5_CompositeDeepScanLine * this_)
{
    new (this_) Imf_2_5::CompositeDeepScanLine();
}

void Imf_2_5_CompositeDeepScanLine_dtor(
    Imf_2_5_CompositeDeepScanLine * this_)
{
    (to_cpp(this_)) -> Imf_2_5::CompositeDeepScanLine::~CompositeDeepScanLine();
}

void Imf_2_5_CompositeDeepScanLine_addSource(
    Imf_2_5_CompositeDeepScanLine * this_
    , Imf_2_5_DeepScanLineInputPart * part)
{
    (to_cpp(this_)) -> addSource(to_cpp(part));
}

void Imf_2_5_CompositeDeepScanLine_addSource_1(
    Imf_2_5_CompositeDeepScanLine * this_
    , Imf_2_5_DeepScanLineInputFile * file)
{
    (to_cpp(this_)) -> addSource(to_cpp(file));
}

void Imf_2_5_CompositeDeepScanLine_setFrameBuffer(
    Imf_2_5_CompositeDeepScanLine * this_
    , Imf_2_5_FrameBuffer const * fr)
{
    (to_cpp(this_)) -> setFrameBuffer(to_cpp_ref(fr));
}

Imf_2_5_FrameBuffer const * Imf_2_5_CompositeDeepScanLine_frameBuffer(
    Imf_2_5_CompositeDeepScanLine const * this_)
{
    return to_c((to_cpp(this_)) -> frameBuffer());
}

void Imf_2_5_CompositeDeepScanLine_readPixels(
    Imf_2_5_CompositeDeepScanLine * this_
    , int start
    , int end)
{
    (to_cpp(this_)) -> readPixels(start, end);
}

int Imf_2_5_CompositeDeepScanLine_sources(
    Imf_2_5_CompositeDeepScanLine const * this_)
{
    return (to_cpp(this_)) -> sources();
}

Imath_2_5_Box2i const * Imf_2_5_CompositeDeepScanLine_dataWindow(
    Imf_2_5_CompositeDeepScanLine const * this_)
{
    return to_c((to_cpp(this_)) -> dataWindow());
}

void Imf_2_5_CompositeDeepScanLine_setCompositing(
    Imf_2_5_CompositeDeepScanLine * this_
    , Imf_2_5_DeepCompositing * compositing)
{
    (to_cpp(this_)) -> setCompositing(to_cpp(compositing));
}
