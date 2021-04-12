#include <imf_lut_private_.h>

#include <half_private_.h>
#include <imath_box_private_.h>
#include <imf_framebuffer_private_.h>
#include <imf_rgba_private_.h>


void Imf_2_5_HalfLut_apply(
    Imf_2_5_HalfLut const * this_
    , Imath_2_5_half * data
    , int nData
    , int stride)
{
    (to_cpp(this_)) -> apply(to_cpp(data), nData, stride);
}

void Imf_2_5_HalfLut_apply_1(
    Imf_2_5_HalfLut const * this_
    , Imf_2_5_Slice const * data
    , Imath_2_5_Box2i const * dataWindow)
{
    (to_cpp(this_)) -> apply(to_cpp_ref(data), to_cpp_ref(dataWindow));
}

void Imf_2_5_RgbaLut_apply(
    Imf_2_5_RgbaLut const * this_
    , Imf_2_5_Rgba * data
    , int nData
    , int stride)
{
    (to_cpp(this_)) -> apply(to_cpp(data), nData, stride);
}

void Imf_2_5_RgbaLut_apply_1(
    Imf_2_5_RgbaLut const * this_
    , Imf_2_5_Rgba * base
    , int xStride
    , int yStride
    , Imath_2_5_Box2i const * dataWindow)
{
    (to_cpp(this_)) -> apply(to_cpp(base), xStride, yStride, to_cpp_ref(dataWindow));
}
