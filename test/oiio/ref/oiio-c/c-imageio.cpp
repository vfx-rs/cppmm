#include <c-imageio_private.h>

#include <c-typedesc_private.h>
#include <new>
#include <std_string_private.h>


void OpenImageIO_v2_2__ROI_default(
    OIIO_ROI_t * this_)
{
    new (this_) OpenImageIO_v2_2::ROI();
}

_Bool OpenImageIO_v2_2__ROI_defined(
    OIIO_ROI_t const * this_)
{
    return (to_cpp(this_)) -> defined();
}

int OpenImageIO_v2_2__ROI_width(
    OIIO_ROI_t const * this_)
{
    return (to_cpp(this_)) -> width();
}

int OpenImageIO_v2_2__ROI_height(
    OIIO_ROI_t const * this_)
{
    return (to_cpp(this_)) -> height();
}

int OpenImageIO_v2_2__ROI_depth(
    OIIO_ROI_t const * this_)
{
    return (to_cpp(this_)) -> depth();
}

int OpenImageIO_v2_2__ROI_nchannels(
    OIIO_ROI_t const * this_)
{
    return (to_cpp(this_)) -> nchannels();
}

unsigned long OpenImageIO_v2_2__ROI_npixels(
    OIIO_ROI_t const * this_)
{
    return (to_cpp(this_)) -> npixels();
}

void OpenImageIO_v2_2__ImageSpec_ImageSpec(
    OIIO_ImageSpec_t * this_
    , OIIO_TypeDesc_t format)
{
    new (this_) OpenImageIO_v2_2::ImageSpec(to_cpp_ref(&(format)));
}

void OpenImageIO_v2_2__ImageSpec_new_with_dimensions(
    OIIO_ImageSpec_t * this_
    , int xres
    , int yres
    , int nchans
    , OIIO_TypeDesc_t fmt)
{
    new (this_) OpenImageIO_v2_2::ImageSpec(xres, yres, nchans, to_cpp_ref(&(fmt)));
}

void OpenImageIO_v2_2__ImageSpec_set_format(
    OIIO_ImageSpec_t * this_
    , OIIO_TypeDesc_t fmt)
{
    (to_cpp(this_)) -> set_format(to_cpp_ref(&(fmt)));
}

void OpenImageIO_v2_2__ImageSpec_default_channel_names(
    OIIO_ImageSpec_t * this_)
{
    (to_cpp(this_)) -> default_channel_names();
}

unsigned long OpenImageIO_v2_2__ImageSpec_channel_bytes(
    OIIO_ImageSpec_t const * this_)
{
    return (to_cpp(this_)) -> channel_bytes();
}

unsigned long OpenImageIO_v2_2__ImageSpec_channel_bytes_for(
    OIIO_ImageSpec_t const * this_
    , int chan
    , _Bool native)
{
    return (to_cpp(this_)) -> channel_bytes(chan, native);
}

unsigned long OpenImageIO_v2_2__ImageSpec_scanline_bytes(
    OIIO_ImageSpec_t const * this_
    , _Bool native)
{
    return (to_cpp(this_)) -> scanline_bytes(native);
}

std___cxx11_string_t OpenImageIO_v2_2__ImageSpec_serialize(
    OIIO_ImageSpec_t const * this_
    , OIIO_ImageSpec_SerialFormat format
    , OIIO_ImageSpec_SerialVerbose verbose)
{
    return to_c_copy((to_cpp(this_)) -> serialize(OIIO_ImageSpec_SerialFormat_to_cpp_ref(&(format)), OIIO_ImageSpec_SerialVerbose_to_cpp_ref(&(verbose))));
}

void OpenImageIO_v2_2__ImageSpec_copy(
    OIIO_ImageSpec_t * this_
    , OIIO_ImageSpec_t const * other)
{
    new (this_) OpenImageIO_v2_2::ImageSpec(to_cpp_ref(other));
}

OIIO_ImageSpec_t * OpenImageIO_v2_2__ImageSpec_assign(
    OIIO_ImageSpec_t * this_
    , OIIO_ImageSpec_t const * other)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(other)));
}

char const * OpenImageIO_v2_2__ImageInput_format_name(
    OIIO_ImageInput_t const * this_)
{
    return (to_cpp(this_)) -> format_name();
}

std___cxx11_string_t OpenImageIO_v2_2__ImageInput_geterror(
    OIIO_ImageInput_t const * this_)
{
    return to_c_copy((to_cpp(this_)) -> geterror());
}

OIIO_ROI_t OpenImageIO_v2_2_roi_union(
    OIIO_ROI_t const * A
    , OIIO_ROI_t const * B)
{
    return to_c_copy(OpenImageIO_v2_2::roi_union(to_cpp_ref(A), to_cpp_ref(B)));
}

OIIO_ROI_t OpenImageIO_v2_2_roi_intersection(
    OIIO_ROI_t const * A
    , OIIO_ROI_t const * B)
{
    return to_c_copy(OpenImageIO_v2_2::roi_intersection(to_cpp_ref(A), to_cpp_ref(B)));
}
