#include <c-typedesc.h>

typedef struct {
    char data[32];
} __attribute__((aligned(4))) OpenImageIO_v2_2_ROI;
typedef struct {
    char data[160];
} __attribute__((aligned(8))) OpenImageIO_v2_2_ImageSpec;
typedef struct {
    char data[248];
} __attribute__((aligned(8))) OpenImageIO_v2_2_ImageInput;


void OpenImageIO_v2_2_ROI_default(
    OpenImageIO_v2_2_ROI * self);


_Bool OpenImageIO_v2_2_ROI_defined(
    OpenImageIO_v2_2_ROI const * self);


int OpenImageIO_v2_2_ROI_width(
    OpenImageIO_v2_2_ROI const * self);


int OpenImageIO_v2_2_ROI_height(
    OpenImageIO_v2_2_ROI const * self);


int OpenImageIO_v2_2_ROI_depth(
    OpenImageIO_v2_2_ROI const * self);


int OpenImageIO_v2_2_ROI_nchannels(
    OpenImageIO_v2_2_ROI const * self);


unsigned long OpenImageIO_v2_2_ROI_npixels(
    OpenImageIO_v2_2_ROI const * self);


OpenImageIO_v2_2_ROI OpenImageIO_v2_2_ROI_All(
    OpenImageIO_v2_2_ROI * self);










void OpenImageIO_v2_2_ImageSpec_ImageSpec(
    OpenImageIO_v2_2_ImageSpec * self
    , OpenImageIO_v2_2_TypeDesc format);


void OpenImageIO_v2_2_ImageSpec_new_with_dimensions(
    OpenImageIO_v2_2_ImageSpec * self
    , int xres
    , int yres
    , int nchans
    , OpenImageIO_v2_2_TypeDesc fmt);


void OpenImageIO_v2_2_ImageSpec_set_format(
    OpenImageIO_v2_2_ImageSpec * self
    , OpenImageIO_v2_2_TypeDesc fmt);


void OpenImageIO_v2_2_ImageSpec_default_channel_names(
    OpenImageIO_v2_2_ImageSpec * self);


unsigned long OpenImageIO_v2_2_ImageSpec_channel_bytes(
    OpenImageIO_v2_2_ImageSpec const * self);


unsigned long OpenImageIO_v2_2_ImageSpec_channel_bytes_for(
    OpenImageIO_v2_2_ImageSpec const * self
    , int chan
    , _Bool native);


unsigned long OpenImageIO_v2_2_ImageSpec_scanline_bytes(
    OpenImageIO_v2_2_ImageSpec const * self
    , _Bool native);


void OpenImageIO_v2_2_ImageSpec_auto_stride(
    OpenImageIO_v2_2_ImageSpec * self
    , long * xstride
    , long * ystride
    , long * zstride
    , long channelsize
    , int nchannels
    , int width
    , int height);


void OpenImageIO_v2_2_ImageSpec_copy(
    OpenImageIO_v2_2_ImageSpec * self
    , OpenImageIO_v2_2_ImageSpec const * other);


OpenImageIO_v2_2_ImageSpec * OpenImageIO_v2_2_ImageSpec_assign(
    OpenImageIO_v2_2_ImageSpec * self
    , OpenImageIO_v2_2_ImageSpec const * other);











char * OpenImageIO_v2_2_ImageInput_format_name(
    OpenImageIO_v2_2_ImageInput const * self);








