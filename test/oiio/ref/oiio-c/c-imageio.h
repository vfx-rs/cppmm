#pragma once
#include <c-typedesc.h>
#include <std_string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum OpenImageIO_v2_2__ImageSpec__SerialFormat_e {
    OIIO_ImageSpec_SerialFormat_SerialText = 0,
    OIIO_ImageSpec_SerialFormat_SerialXML = 1,
};
typedef unsigned int OIIO_ImageSpec_SerialFormat;
enum OpenImageIO_v2_2__ImageSpec__SerialVerbose_e {
    OIIO_ImageSpec_SerialVerbose_SerialBrief = 0,
    OIIO_ImageSpec_SerialVerbose_SerialDetailed = 1,
    OIIO_ImageSpec_SerialVerbose_SerialDetailedHuman = 2,
};
typedef unsigned int OIIO_ImageSpec_SerialVerbose;

typedef struct OpenImageIO_v2_2__ROI_t_s {
    char data[32];
} __attribute__((aligned(4))) OpenImageIO_v2_2__ROI_t;
typedef OpenImageIO_v2_2__ROI_t OIIO_ROI_t;

typedef struct OpenImageIO_v2_2__ImageSpec_t_s {
    char data[160];
} __attribute__((aligned(8))) OpenImageIO_v2_2__ImageSpec_t;
typedef OpenImageIO_v2_2__ImageSpec_t OIIO_ImageSpec_t;

typedef struct OpenImageIO_v2_2__ImageInput_t_s {
    char data[248];
} __attribute__((aligned(8))) OpenImageIO_v2_2__ImageInput_t;
typedef OpenImageIO_v2_2__ImageInput_t OIIO_ImageInput_t;






















void OpenImageIO_v2_2__ROI_default(
    OIIO_ROI_t * this_);

#define OIIO_ROI_default OpenImageIO_v2_2__ROI_default



_Bool OpenImageIO_v2_2__ROI_defined(
    OIIO_ROI_t const * this_);

#define OIIO_ROI_defined OpenImageIO_v2_2__ROI_defined



int OpenImageIO_v2_2__ROI_width(
    OIIO_ROI_t const * this_);

#define OIIO_ROI_width OpenImageIO_v2_2__ROI_width



int OpenImageIO_v2_2__ROI_height(
    OIIO_ROI_t const * this_);

#define OIIO_ROI_height OpenImageIO_v2_2__ROI_height



int OpenImageIO_v2_2__ROI_depth(
    OIIO_ROI_t const * this_);

#define OIIO_ROI_depth OpenImageIO_v2_2__ROI_depth



int OpenImageIO_v2_2__ROI_nchannels(
    OIIO_ROI_t const * this_);

#define OIIO_ROI_nchannels OpenImageIO_v2_2__ROI_nchannels



unsigned long OpenImageIO_v2_2__ROI_npixels(
    OIIO_ROI_t const * this_);

#define OIIO_ROI_npixels OpenImageIO_v2_2__ROI_npixels












void OpenImageIO_v2_2__ImageSpec_ImageSpec(
    OIIO_ImageSpec_t * this_
    , OIIO_TypeDesc_t format);

#define OIIO_ImageSpec_ImageSpec OpenImageIO_v2_2__ImageSpec_ImageSpec



void OpenImageIO_v2_2__ImageSpec_new_with_dimensions(
    OIIO_ImageSpec_t * this_
    , int xres
    , int yres
    , int nchans
    , OIIO_TypeDesc_t fmt);

#define OIIO_ImageSpec_new_with_dimensions OpenImageIO_v2_2__ImageSpec_new_with_dimensions



void OpenImageIO_v2_2__ImageSpec_set_format(
    OIIO_ImageSpec_t * this_
    , OIIO_TypeDesc_t fmt);

#define OIIO_ImageSpec_set_format OpenImageIO_v2_2__ImageSpec_set_format



void OpenImageIO_v2_2__ImageSpec_default_channel_names(
    OIIO_ImageSpec_t * this_);

#define OIIO_ImageSpec_default_channel_names OpenImageIO_v2_2__ImageSpec_default_channel_names



unsigned long OpenImageIO_v2_2__ImageSpec_channel_bytes(
    OIIO_ImageSpec_t const * this_);

#define OIIO_ImageSpec_channel_bytes OpenImageIO_v2_2__ImageSpec_channel_bytes



unsigned long OpenImageIO_v2_2__ImageSpec_channel_bytes_for(
    OIIO_ImageSpec_t const * this_
    , int chan
    , _Bool native);

#define OIIO_ImageSpec_channel_bytes_for OpenImageIO_v2_2__ImageSpec_channel_bytes_for



unsigned long OpenImageIO_v2_2__ImageSpec_scanline_bytes(
    OIIO_ImageSpec_t const * this_
    , _Bool native);

#define OIIO_ImageSpec_scanline_bytes OpenImageIO_v2_2__ImageSpec_scanline_bytes



std___cxx11_string_t OpenImageIO_v2_2__ImageSpec_serialize(
    OIIO_ImageSpec_t const * this_
    , OIIO_ImageSpec_SerialFormat format
    , OIIO_ImageSpec_SerialVerbose verbose);

#define OIIO_ImageSpec_serialize OpenImageIO_v2_2__ImageSpec_serialize



void OpenImageIO_v2_2__ImageSpec_copy(
    OIIO_ImageSpec_t * this_
    , OIIO_ImageSpec_t const * other);

#define OIIO_ImageSpec_copy OpenImageIO_v2_2__ImageSpec_copy



OIIO_ImageSpec_t * OpenImageIO_v2_2__ImageSpec_assign(
    OIIO_ImageSpec_t * this_
    , OIIO_ImageSpec_t const * other);

#define OIIO_ImageSpec_assign OpenImageIO_v2_2__ImageSpec_assign












char const * OpenImageIO_v2_2__ImageInput_format_name(
    OIIO_ImageInput_t const * this_);

#define OIIO_ImageInput_format_name OpenImageIO_v2_2__ImageInput_format_name



std___cxx11_string_t OpenImageIO_v2_2__ImageInput_geterror(
    OIIO_ImageInput_t const * this_);

#define OIIO_ImageInput_geterror OpenImageIO_v2_2__ImageInput_geterror











OIIO_ROI_t OpenImageIO_v2_2_roi_union(
    OIIO_ROI_t const * A
    , OIIO_ROI_t const * B);

#define OIIO_roi_union OpenImageIO_v2_2_roi_union



OIIO_ROI_t OpenImageIO_v2_2_roi_intersection(
    OIIO_ROI_t const * A
    , OIIO_ROI_t const * B);

#define OIIO_roi_intersection OpenImageIO_v2_2_roi_intersection

#ifdef __cplusplus
}
#endif
