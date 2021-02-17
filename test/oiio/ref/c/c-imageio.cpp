#include <c-imageio.h>

#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>
#include <cppmm_bind.hpp>

void OpenImageIO_v2_2_ROI_ROI(
    OpenImageIO_v2_2_ROI *self)
{
    new (self) ROI();
}
_Bool OpenImageIO_v2_2_ROI_defined(
    OpenImageIO_v2_2_ROI const *self)
{
    return (reinterpret_cast<OpenImageIO_v2_2::ROI const *>(self)) -> 
        defined();
}
int OpenImageIO_v2_2_ROI_width(
    OpenImageIO_v2_2_ROI const *self)
{
    return (reinterpret_cast<OpenImageIO_v2_2::ROI const *>(self)) -> 
        width();
}
int OpenImageIO_v2_2_ROI_height(
    OpenImageIO_v2_2_ROI const *self)
{
    return (reinterpret_cast<OpenImageIO_v2_2::ROI const *>(self)) -> 
        height();
}
int OpenImageIO_v2_2_ROI_depth(
    OpenImageIO_v2_2_ROI const *self)
{
    return (reinterpret_cast<OpenImageIO_v2_2::ROI const *>(self)) -> 
        depth();
}
int OpenImageIO_v2_2_ROI_nchannels(
    OpenImageIO_v2_2_ROI const *self)
{
    return (reinterpret_cast<OpenImageIO_v2_2::ROI const *>(self)) -> 
        nchannels();
}
unsigned long OpenImageIO_v2_2_ROI_npixels(
    OpenImageIO_v2_2_ROI const *self)
{
    return (reinterpret_cast<OpenImageIO_v2_2::ROI const *>(self)) -> 
        npixels();
}
OpenImageIO_v2_2_ROI OpenImageIO_v2_2_ROI_All(
    OpenImageIO_v2_2_ROI *self)
{
    return *(reinterpret_cast<OpenImageIO_v2_2_ROI *>(&((reinterpret_cast<OpenImageIO_v2_2::ROI *>(self)) -> 
        All())));
}
void OpenImageIO_v2_2_ImageSpec_default_channel_names(
    OpenImageIO_v2_2_ImageSpec *self)
{
    (reinterpret_cast<OpenImageIO_v2_2::ImageSpec *>(self)) -> 
        default_channel_names();
}
unsigned long OpenImageIO_v2_2_ImageSpec_channel_bytes(
    OpenImageIO_v2_2_ImageSpec const *self)
{
    return (reinterpret_cast<OpenImageIO_v2_2::ImageSpec const *>(self)) -> 
        channel_bytes();
}
unsigned long OpenImageIO_v2_2_ImageSpec_channel_bytes(
    OpenImageIO_v2_2_ImageSpec const *self
    , int chan
    , _Bool native)
{
    return (reinterpret_cast<OpenImageIO_v2_2::ImageSpec const *>(self)) -> 
        channel_bytes(
             chan
            ,native
            );
}
unsigned long OpenImageIO_v2_2_ImageSpec_scanline_bytes(
    OpenImageIO_v2_2_ImageSpec const *self
    , _Bool native)
{
    return (reinterpret_cast<OpenImageIO_v2_2::ImageSpec const *>(self)) -> 
        scanline_bytes(
             native
            );
}
void OpenImageIO_v2_2_ImageSpec_auto_stride(
    OpenImageIO_v2_2_ImageSpec *self
    , long *xstride
    , long *ystride
    , long *zstride
    , long channelsize
    , int nchannels
    , int width
    , int height)
{
    (reinterpret_cast<OpenImageIO_v2_2::ImageSpec *>(self)) -> 
        auto_stride(
             *(reinterpret_cast<long *>(xstride))
            ,*(reinterpret_cast<long *>(ystride))
            ,*(reinterpret_cast<long *>(zstride))
            ,channelsize
            ,nchannels
            ,width
            ,height
            );
}
void OpenImageIO_v2_2_ImageSpec_ImageSpec(
    OpenImageIO_v2_2_ImageSpec *self
    , OpenImageIO_v2_2_ImageSpec const *other)
{
    new (self) ImageSpec(
             *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec const *>(other))
            );
}
OpenImageIO_v2_2_ImageSpec *OpenImageIO_v2_2_ImageSpec_operator=(
    OpenImageIO_v2_2_ImageSpec *self
    , OpenImageIO_v2_2_ImageSpec const *other)
{
    return reinterpret_cast<OpenImageIO_v2_2_ImageSpec *>((reinterpret_cast<OpenImageIO_v2_2::ImageSpec *>(self)) -> 
        operator=(
             *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec const *>(other))
            ));
}
char *OpenImageIO_v2_2_ImageInput_format_name(
    OpenImageIO_v2_2_ImageInput const *self)
{
    return reinterpret_cast<char *>((reinterpret_cast<OpenImageIO_v2_2::ImageInput const *>(self)) -> 
        format_name());
}
