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

/** ROI is a small helper struct describing a rectangular region of interest
in an image. The region is [xbegin,xend) x [begin,yend) x [zbegin,zend),
with the "end" designators signifying one past the last pixel in each
dimension, a la STL style. */
typedef struct OpenImageIO_v2_2__ROI_t_s {
    int xbegin;
    int xend;
    int ybegin;
    int yend;
    int zbegin;
    int zend;
    int chbegin;
    int chend;
} __attribute__((aligned(4))) OpenImageIO_v2_2__ROI_t;
typedef OpenImageIO_v2_2__ROI_t OIIO_ROI_t;

/** ImageSpec describes the data format of an image -- dimensions, layout,
number and meanings of image channels.

The `width, height, depth` are the size of the data of this image, i.e.,
the number of pixels in each dimension.  A ``depth`` greater than 1
indicates a 3D "volumetric" image. The `x, y, z` fields indicate the
*origin* of the pixel data of the image. These default to (0,0,0), but
setting them differently may indicate that this image is offset from the
usual origin.
Therefore the pixel data are defined over pixel coordinates
   [`x` ... `x+width-1`] horizontally,
   [`y` ... `y+height-1`] vertically,
   and [`z` ... `z+depth-1`] in depth.

The analogous `full_width`, `full_height`, `full_depth` and `full_x`,
`full_y`, `full_z` fields define a "full" or "display" image window over
the region [`full_x` ... `full_x+full_width-1`] horizontally, [`full_y`
... `full_y+full_height-1`] vertically, and [`full_z`...
`full_z+full_depth-1`] in depth.

Having the full display window different from the pixel data window can
be helpful in cases where you want to indicate that your image is a
*crop window* of a larger image (if the pixel data window is a subset of
the full display window), or that the pixels include *overscan* (if the
pixel data is a superset of the full display window), or may simply
indicate how different non-overlapping images piece together.

For tiled images, `tile_width`, `tile_height`, and `tile_depth` specify
that the image is stored in a file organized into rectangular *tiles*
of these dimensions. The default of 0 value for these fields indicates
that the image is stored in scanline order, rather than as tiles. */
typedef struct OpenImageIO_v2_2__ImageSpec_t_s {
    char data[160];
} __attribute__((aligned(8))) OpenImageIO_v2_2__ImageSpec_t;
typedef OpenImageIO_v2_2__ImageSpec_t OIIO_ImageSpec_t;

/** ImageInput abstracts the reading of an image file in a file
format-agnostic manner. */
typedef struct OpenImageIO_v2_2__ImageInput_t_s {
    char data[248];
} __attribute__((aligned(8))) OpenImageIO_v2_2__ImageInput_t;
typedef OpenImageIO_v2_2__ImageInput_t OIIO_ImageInput_t;





















/** Default constructor is an undefined region. Note that this is also
interpreted as All(). */
void OpenImageIO_v2_2__ROI_default(
    OIIO_ROI_t * this_);
#define OIIO_ROI_default OpenImageIO_v2_2__ROI_default


/** Is a region defined? */
_Bool OpenImageIO_v2_2__ROI_defined(
    OIIO_ROI_t const * this_);
#define OIIO_ROI_defined OpenImageIO_v2_2__ROI_defined


/** @{
 @name Spatial size functions.
 The width, height, and depth of the region. */
int OpenImageIO_v2_2__ROI_width(
    OIIO_ROI_t const * this_);
#define OIIO_ROI_width OpenImageIO_v2_2__ROI_width


int OpenImageIO_v2_2__ROI_height(
    OIIO_ROI_t const * this_);
#define OIIO_ROI_height OpenImageIO_v2_2__ROI_height


int OpenImageIO_v2_2__ROI_depth(
    OIIO_ROI_t const * this_);
#define OIIO_ROI_depth OpenImageIO_v2_2__ROI_depth


/** Number of channels in the region.  Beware -- this defaults to a
huge number, and to be meaningful you must consider
std::min (imagebuf.nchannels(), roi.nchannels()). */
int OpenImageIO_v2_2__ROI_nchannels(
    OIIO_ROI_t const * this_);
#define OIIO_ROI_nchannels OpenImageIO_v2_2__ROI_nchannels


/** Total number of pixels in the region. */
unsigned long OpenImageIO_v2_2__ROI_npixels(
    OIIO_ROI_t const * this_);
#define OIIO_ROI_npixels OpenImageIO_v2_2__ROI_npixels











/** Constructor: given just the data format, set all other fields to
something reasonable. */
void OpenImageIO_v2_2__ImageSpec_ImageSpec(
    OIIO_ImageSpec_t * this_
    , OIIO_TypeDesc_t format);
#define OIIO_ImageSpec_ImageSpec OpenImageIO_v2_2__ImageSpec_ImageSpec


/** Constructs an `ImageSpec` with the given x and y resolution, number
of channels, and pixel data format.

All other fields are set to the obvious defaults -- the image is an
ordinary 2D image (not a volume), the image is not offset or a crop
of a bigger image, the image is scanline-oriented (not tiled),
channel names are "R", "G", "B"' and "A" (up to and including 4
channels, beyond that they are named "channel *n*"), the fourth
channel (if it exists) is assumed to be alpha. */
void OpenImageIO_v2_2__ImageSpec_new_with_dimensions(
    OIIO_ImageSpec_t * this_
    , int xres
    , int yres
    , int nchans
    , OIIO_TypeDesc_t fmt);
#define OIIO_ImageSpec_new_with_dimensions OpenImageIO_v2_2__ImageSpec_new_with_dimensions


/** Set the data format, and clear any per-channel format information
in `channelformats`. */
void OpenImageIO_v2_2__ImageSpec_set_format(
    OIIO_ImageSpec_t * this_
    , OIIO_TypeDesc_t fmt);
#define OIIO_ImageSpec_set_format OpenImageIO_v2_2__ImageSpec_set_format


/** Sets the `channelnames` to reasonable defaults for the number of
channels.  Specifically, channel names are set to "R", "G", "B,"
and "A" (up to and including 4 channels, beyond that they are named
"channel*n*". */
void OpenImageIO_v2_2__ImageSpec_default_channel_names(
    OIIO_ImageSpec_t * this_);
#define OIIO_ImageSpec_default_channel_names OpenImageIO_v2_2__ImageSpec_default_channel_names


/** Returns the number of bytes comprising each channel of each pixel
(i.e., the size of a single value of the type described by the
`format` field). */
unsigned long OpenImageIO_v2_2__ImageSpec_channel_bytes(
    OIIO_ImageSpec_t const * this_);
#define OIIO_ImageSpec_channel_bytes OpenImageIO_v2_2__ImageSpec_channel_bytes


/** Return the number of bytes needed for the single specified
channel.  If native is false (default), compute the size of one
channel of `this->format`, but if native is true, compute the size
of the channel in terms of the "native" data format of that
channel as stored in the file. */
unsigned long OpenImageIO_v2_2__ImageSpec_channel_bytes_for(
    OIIO_ImageSpec_t const * this_
    , int chan
    , _Bool native);
#define OIIO_ImageSpec_channel_bytes_for OpenImageIO_v2_2__ImageSpec_channel_bytes_for


/** Returns the number of bytes comprising each scanline, i.e.,
`pixel_bytes(native) * width` This will return
`std::numeric_limits<imagesize_t>::max()` in the event of an
overflow where it's not representable in an `imagesize_t`. */
unsigned long OpenImageIO_v2_2__ImageSpec_scanline_bytes(
    OIIO_ImageSpec_t const * this_
    , _Bool native);
#define OIIO_ImageSpec_scanline_bytes OpenImageIO_v2_2__ImageSpec_scanline_bytes


/** Returns, as a string, a serialized version of the `ImageSpec`. The
`format` may be either `ImageSpec::SerialText` or
`ImageSpec::SerialXML`. The `verbose` argument may be one of:
`ImageSpec::SerialBrief` (just resolution and other vital
statistics, one line for `SerialText`, `ImageSpec::SerialDetailed`
(contains all metadata in original form), or
`ImageSpec::SerialDetailedHuman` (contains all metadata, in many
cases with human-readable explanation). */
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











/** Return the name of the format implemented by this class. */
char const * OpenImageIO_v2_2__ImageInput_format_name(
    OIIO_ImageInput_t const * this_);
#define OIIO_ImageInput_format_name OpenImageIO_v2_2__ImageInput_format_name


/** If any of the API routines returned false indicating an error, this
method will return the error string (and clear any error flags).  If
no error has occurred since the last time `geterror()` was called,
it will return an empty string. */
std___cxx11_string_t OpenImageIO_v2_2__ImageInput_geterror(
    OIIO_ImageInput_t const * this_);
#define OIIO_ImageInput_geterror OpenImageIO_v2_2__ImageInput_geterror










/** Union of two regions, the smallest region containing both. */
OIIO_ROI_t OpenImageIO_v2_2_roi_union(
    OIIO_ROI_t const * A
    , OIIO_ROI_t const * B);
#define OIIO_roi_union OpenImageIO_v2_2_roi_union


/** Intersection of two regions. */
OIIO_ROI_t OpenImageIO_v2_2_roi_intersection(
    OIIO_ROI_t const * A
    , OIIO_ROI_t const * B);
#define OIIO_roi_intersection OpenImageIO_v2_2_roi_intersection

#ifdef __cplusplus
}
#endif
