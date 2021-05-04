#include <c-imageio_private.h>

#include <c-typedesc_private.h>
#include <new>
#include <std_string_private.h>

unsigned int OpenImageIO_v2_2__ROI_default(
    OIIO_ROI_t * this_)
{
    try {
        new (this_) OpenImageIO_v2_2::ROI();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ROI_defined(
    OIIO_ROI_t const * this_
    , _Bool * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> defined();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ROI_width(
    OIIO_ROI_t const * this_
    , int * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> width();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ROI_height(
    OIIO_ROI_t const * this_
    , int * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> height();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ROI_depth(
    OIIO_ROI_t const * this_
    , int * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> depth();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ROI_nchannels(
    OIIO_ROI_t const * this_
    , int * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> nchannels();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ROI_npixels(
    OIIO_ROI_t const * this_
    , unsigned long * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> npixels();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_ImageSpec(
    OIIO_ImageSpec_t * * this_
    , OIIO_TypeDesc_t format)
{
    try {
        to_c(this_, new OpenImageIO_v2_2::ImageSpec(to_cpp_ref(&(format))));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_new_with_dimensions(
    OIIO_ImageSpec_t * * this_
    , int xres
    , int yres
    , int nchans
    , OIIO_TypeDesc_t fmt)
{
    try {
        to_c(this_, new OpenImageIO_v2_2::ImageSpec(xres, yres, nchans, to_cpp_ref(&(fmt))));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_set_format(
    OIIO_ImageSpec_t * this_
    , OIIO_TypeDesc_t fmt)
{
    try {
        (to_cpp(this_)) -> set_format(to_cpp_ref(&(fmt)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_default_channel_names(
    OIIO_ImageSpec_t * this_)
{
    try {
        (to_cpp(this_)) -> default_channel_names();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_channel_bytes(
    OIIO_ImageSpec_t const * this_
    , unsigned long * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> channel_bytes();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_channel_bytes_for(
    OIIO_ImageSpec_t const * this_
    , unsigned long * return_
    , int chan
    , _Bool native)
{
    try {
        *(return_) = (to_cpp(this_)) -> channel_bytes(chan, native);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_scanline_bytes(
    OIIO_ImageSpec_t const * this_
    , unsigned long * return_
    , _Bool native)
{
    try {
        *(return_) = (to_cpp(this_)) -> scanline_bytes(native);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_serialize(
    OIIO_ImageSpec_t const * this_
    , std___cxx11_string_t * * return_
    , OIIO_ImageSpec_SerialFormat format
    , OIIO_ImageSpec_SerialVerbose verbose)
{
    try {
        to_c_copy(return_, (to_cpp(this_)) -> serialize(OIIO_ImageSpec_SerialFormat_to_cpp_ref(&(format)), OIIO_ImageSpec_SerialVerbose_to_cpp_ref(&(verbose))));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_copy(
    OIIO_ImageSpec_t * * this_
    , OIIO_ImageSpec_t const * other)
{
    try {
        to_c(this_, new OpenImageIO_v2_2::ImageSpec(to_cpp_ref(other)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageSpec_assign(
    OIIO_ImageSpec_t * this_
    , OIIO_ImageSpec_t * * return_
    , OIIO_ImageSpec_t const * other)
{
    try {
        to_c(return_, (to_cpp(this_)) -> operator=(to_cpp_ref(other)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageInput_format_name(
    OIIO_ImageInput_t const * this_
    , char const * * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> format_name();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2__ImageInput_geterror(
    OIIO_ImageInput_t const * this_
    , std___cxx11_string_t * * return_)
{
    try {
        to_c_copy(return_, (to_cpp(this_)) -> geterror());
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2_roi_union(
    OIIO_ROI_t * return_
    , OIIO_ROI_t const * A
    , OIIO_ROI_t const * B)
{
    try {
        to_c_copy(return_, OpenImageIO_v2_2::roi_union(to_cpp_ref(A), to_cpp_ref(B)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int OpenImageIO_v2_2_roi_intersection(
    OIIO_ROI_t * return_
    , OIIO_ROI_t const * A
    , OIIO_ROI_t const * B)
{
    try {
        to_c_copy(return_, OpenImageIO_v2_2::roi_intersection(to_cpp_ref(A), to_cpp_ref(B)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
