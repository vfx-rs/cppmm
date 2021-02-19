#include <c-imageio.h>

#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>
#include <cppmm_bind.hpp>
#include <c-typedesc_private.h>
#include <c-imageio_private.h>


void OpenImageIO_v2_2_ROI_ROI(
    OpenImageIO_v2_2_ROI * self)
{
    new (self) ROI();
}

_Bool OpenImageIO_v2_2_ROI_defined(
    OpenImageIO_v2_2_ROI const * self)
{
    return (to_cpp(self)) -> defined();
}

int OpenImageIO_v2_2_ROI_width(
    OpenImageIO_v2_2_ROI const * self)
{
    return (to_cpp(self)) -> width();
}

int OpenImageIO_v2_2_ROI_height(
    OpenImageIO_v2_2_ROI const * self)
{
    return (to_cpp(self)) -> height();
}

int OpenImageIO_v2_2_ROI_depth(
    OpenImageIO_v2_2_ROI const * self)
{
    return (to_cpp(self)) -> depth();
}

int OpenImageIO_v2_2_ROI_nchannels(
    OpenImageIO_v2_2_ROI const * self)
{
    return (to_cpp(self)) -> nchannels();
}

unsigned long OpenImageIO_v2_2_ROI_npixels(
    OpenImageIO_v2_2_ROI const * self)
{
    return (to_cpp(self)) -> npixels();
}

OpenImageIO_v2_2_ROI OpenImageIO_v2_2_ROI_All(
    OpenImageIO_v2_2_ROI * self)
{
    return to_c_copy((to_cpp(self)) -> All());
}

void OpenImageIO_v2_2_ImageSpec_ImageSpec(
    OpenImageIO_v2_2_ImageSpec * self
    , OpenImageIO_v2_2_TypeDesc format)
{
    new (self) ImageSpec(to_cpp_ref(&(format)));
}

void OpenImageIO_v2_2_ImageSpec_ImageSpec(
    OpenImageIO_v2_2_ImageSpec * self
    , int xres
    , int yres
    , int nchans
    , OpenImageIO_v2_2_TypeDesc fmt)
{
    new (self) ImageSpec(xres, yres, nchans, to_cpp_ref(&(fmt)));
}

void OpenImageIO_v2_2_ImageSpec_set_format(
    OpenImageIO_v2_2_ImageSpec * self
    , OpenImageIO_v2_2_TypeDesc fmt)
{
    (to_cpp(self)) -> set_format(to_cpp_ref(&(fmt)));
}

void OpenImageIO_v2_2_ImageSpec_default_channel_names(
    OpenImageIO_v2_2_ImageSpec * self)
{
    (to_cpp(self)) -> default_channel_names();
}

unsigned long OpenImageIO_v2_2_ImageSpec_channel_bytes(
    OpenImageIO_v2_2_ImageSpec const * self)
{
    return (to_cpp(self)) -> channel_bytes();
}

unsigned long OpenImageIO_v2_2_ImageSpec_channel_bytes(
    OpenImageIO_v2_2_ImageSpec const * self
    , int chan
    , _Bool native)
{
    return (to_cpp(self)) -> channel_bytes(chan, native);
}

unsigned long OpenImageIO_v2_2_ImageSpec_scanline_bytes(
    OpenImageIO_v2_2_ImageSpec const * self
    , _Bool native)
{
    return (to_cpp(self)) -> scanline_bytes(native);
}

void OpenImageIO_v2_2_ImageSpec_auto_stride(
    OpenImageIO_v2_2_ImageSpec * self
    , long * xstride
    , long * ystride
    , long * zstride
    , long channelsize
    , int nchannels
    , int width
    , int height)
{
    (to_cpp(self)) -> auto_stride(to_cpp_ref(xstride), to_cpp_ref(ystride), to_cpp_ref(zstride), channelsize, nchannels, width, height);
}

void OpenImageIO_v2_2_ImageSpec_ImageSpec(
    OpenImageIO_v2_2_ImageSpec * self
    , OpenImageIO_v2_2_ImageSpec const * other)
{
    new (self) ImageSpec(to_cpp_ref(other));
}

OpenImageIO_v2_2_ImageSpec * OpenImageIO_v2_2_ImageSpec_operator=(
    OpenImageIO_v2_2_ImageSpec * self
    , OpenImageIO_v2_2_ImageSpec const * other)
{
    return to_c((to_cpp(self)) -> operator=(to_cpp_ref(other)));
}

char * OpenImageIO_v2_2_ImageInput_format_name(
    OpenImageIO_v2_2_ImageInput const * self)
{
    return to_c((to_cpp(self)) -> format_name());
}
