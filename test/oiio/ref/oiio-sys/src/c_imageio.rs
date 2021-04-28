#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

/// ROI is a small helper struct describing a rectangular region of interest
/// in an image. The region is [xbegin,xend) x [begin,yend) x [zbegin,zend),
/// with the "end" designators signifying one past the last pixel in each
/// dimension, a la STL style.
#[repr(C, align(4))]
#[derive(Clone)]
pub struct OpenImageIO_v2_2__ROI_t {
    pub xbegin: c_int,
    pub xend: c_int,
    pub ybegin: c_int,
    pub yend: c_int,
    pub zbegin: c_int,
    pub zend: c_int,
    pub chbegin: c_int,
    pub chend: c_int,
}

/// ImageSpec describes the data format of an image -- dimensions, layout,
/// number and meanings of image channels.
/// 
/// The `width, height, depth` are the size of the data of this image, i.e.,
/// the number of pixels in each dimension.  A ``depth`` greater than 1
/// indicates a 3D "volumetric" image. The `x, y, z` fields indicate the
/// *origin* of the pixel data of the image. These default to (0,0,0), but
/// setting them differently may indicate that this image is offset from the
/// usual origin.
/// Therefore the pixel data are defined over pixel coordinates
///    [`x` ... `x+width-1`] horizontally,
///    [`y` ... `y+height-1`] vertically,
///    and [`z` ... `z+depth-1`] in depth.
/// 
/// The analogous `full_width`, `full_height`, `full_depth` and `full_x`,
/// `full_y`, `full_z` fields define a "full" or "display" image window over
/// the region [`full_x` ... `full_x+full_width-1`] horizontally, [`full_y`
/// ... `full_y+full_height-1`] vertically, and [`full_z`...
/// `full_z+full_depth-1`] in depth.
/// 
/// Having the full display window different from the pixel data window can
/// be helpful in cases where you want to indicate that your image is a
/// *crop window* of a larger image (if the pixel data window is a subset of
/// the full display window), or that the pixels include *overscan* (if the
/// pixel data is a superset of the full display window), or may simply
/// indicate how different non-overlapping images piece together.
/// 
/// For tiled images, `tile_width`, `tile_height`, and `tile_depth` specify
/// that the image is stored in a file organized into rectangular *tiles*
/// of these dimensions. The default of 0 value for these fields indicates
/// that the image is stored in scanline order, rather than as tiles.
#[repr(C, align(8))]
#[derive(Clone)]
pub struct OpenImageIO_v2_2__ImageSpec_t {
    _inner: [u8; 160]
}

impl Default for OpenImageIO_v2_2__ImageSpec_t {
    fn default() -> Self {
        Self { _inner: [0u8; 160] }
    }
}

/// ImageInput abstracts the reading of an image file in a file
/// format-agnostic manner.
#[repr(C, align(8))]
#[derive(Clone)]
pub struct OpenImageIO_v2_2__ImageInput_t {
    _inner: [u8; 248]
}

impl Default for OpenImageIO_v2_2__ImageInput_t {
    fn default() -> Self {
        Self { _inner: [0u8; 248] }
    }
}


#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct OpenImageIO_v2_2__ImageSpec__SerialFormat_e(pub u32);
pub const OIIO_ImageSpec_SerialFormat_SerialText: OpenImageIO_v2_2__ImageSpec__SerialFormat_e = OpenImageIO_v2_2__ImageSpec__SerialFormat_e(0);
pub const OIIO_ImageSpec_SerialFormat_SerialXML: OpenImageIO_v2_2__ImageSpec__SerialFormat_e = OpenImageIO_v2_2__ImageSpec__SerialFormat_e(1);

#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct OpenImageIO_v2_2__ImageSpec__SerialVerbose_e(pub u32);
pub const OIIO_ImageSpec_SerialVerbose_SerialBrief: OpenImageIO_v2_2__ImageSpec__SerialVerbose_e = OpenImageIO_v2_2__ImageSpec__SerialVerbose_e(0);
pub const OIIO_ImageSpec_SerialVerbose_SerialDetailed: OpenImageIO_v2_2__ImageSpec__SerialVerbose_e = OpenImageIO_v2_2__ImageSpec__SerialVerbose_e(1);
pub const OIIO_ImageSpec_SerialVerbose_SerialDetailedHuman: OpenImageIO_v2_2__ImageSpec__SerialVerbose_e = OpenImageIO_v2_2__ImageSpec__SerialVerbose_e(2);


extern "C" {

/// Default constructor is an undefined region. Note that this is also
/// interpreted as All().
pub fn OpenImageIO_v2_2__ROI_default(this_: *mut OIIO_ROI_t) -> c_void;

/// Is a region defined?
pub fn OpenImageIO_v2_2__ROI_defined(this_: *const OIIO_ROI_t) -> bool;

/// @{
///  @name Spatial size functions.
///  The width, height, and depth of the region.
pub fn OpenImageIO_v2_2__ROI_width(this_: *const OIIO_ROI_t) -> c_int;

pub fn OpenImageIO_v2_2__ROI_height(this_: *const OIIO_ROI_t) -> c_int;

pub fn OpenImageIO_v2_2__ROI_depth(this_: *const OIIO_ROI_t) -> c_int;

/// Number of channels in the region.  Beware -- this defaults to a
/// huge number, and to be meaningful you must consider
/// std::min (imagebuf.nchannels(), roi.nchannels()).
pub fn OpenImageIO_v2_2__ROI_nchannels(this_: *const OIIO_ROI_t) -> c_int;

/// Total number of pixels in the region.
pub fn OpenImageIO_v2_2__ROI_npixels(this_: *const OIIO_ROI_t) -> c_ulong;

/// Constructor: given just the data format, set all other fields to
/// something reasonable.
pub fn OpenImageIO_v2_2__ImageSpec_ImageSpec(this_: *mut OIIO_ImageSpec_t, format: OIIO_TypeDesc_t) -> c_void;

/// Constructs an `ImageSpec` with the given x and y resolution, number
/// of channels, and pixel data format.
/// 
/// All other fields are set to the obvious defaults -- the image is an
/// ordinary 2D image (not a volume), the image is not offset or a crop
/// of a bigger image, the image is scanline-oriented (not tiled),
/// channel names are "R", "G", "B"' and "A" (up to and including 4
/// channels, beyond that they are named "channel *n*"), the fourth
/// channel (if it exists) is assumed to be alpha.
pub fn OpenImageIO_v2_2__ImageSpec_new_with_dimensions(this_: *mut OIIO_ImageSpec_t, xres: c_int, yres: c_int, nchans: c_int, fmt: OIIO_TypeDesc_t) -> c_void;

/// Set the data format, and clear any per-channel format information
/// in `channelformats`.
pub fn OpenImageIO_v2_2__ImageSpec_set_format(this_: *mut OIIO_ImageSpec_t, fmt: OIIO_TypeDesc_t) -> c_void;

/// Sets the `channelnames` to reasonable defaults for the number of
/// channels.  Specifically, channel names are set to "R", "G", "B,"
/// and "A" (up to and including 4 channels, beyond that they are named
/// "channel*n*".
pub fn OpenImageIO_v2_2__ImageSpec_default_channel_names(this_: *mut OIIO_ImageSpec_t) -> c_void;

/// Returns the number of bytes comprising each channel of each pixel
/// (i.e., the size of a single value of the type described by the
/// `format` field).
pub fn OpenImageIO_v2_2__ImageSpec_channel_bytes(this_: *const OIIO_ImageSpec_t) -> c_ulong;

/// Return the number of bytes needed for the single specified
/// channel.  If native is false (default), compute the size of one
/// channel of `this->format`, but if native is true, compute the size
/// of the channel in terms of the "native" data format of that
/// channel as stored in the file.
pub fn OpenImageIO_v2_2__ImageSpec_channel_bytes_for(this_: *const OIIO_ImageSpec_t, chan: c_int, native: bool) -> c_ulong;

/// Returns the number of bytes comprising each scanline, i.e.,
/// `pixel_bytes(native) * width` This will return
/// `std::numeric_limits<imagesize_t>::max()` in the event of an
/// overflow where it's not representable in an `imagesize_t`.
pub fn OpenImageIO_v2_2__ImageSpec_scanline_bytes(this_: *const OIIO_ImageSpec_t, native: bool) -> c_ulong;

/// Returns, as a string, a serialized version of the `ImageSpec`. The
/// `format` may be either `ImageSpec::SerialText` or
/// `ImageSpec::SerialXML`. The `verbose` argument may be one of:
/// `ImageSpec::SerialBrief` (just resolution and other vital
/// statistics, one line for `SerialText`, `ImageSpec::SerialDetailed`
/// (contains all metadata in original form), or
/// `ImageSpec::SerialDetailedHuman` (contains all metadata, in many
/// cases with human-readable explanation).
pub fn OpenImageIO_v2_2__ImageSpec_serialize(this_: *const OIIO_ImageSpec_t, format: OIIO_ImageSpec_SerialFormat, verbose: OIIO_ImageSpec_SerialVerbose) -> std___cxx11_string_t;

pub fn OpenImageIO_v2_2__ImageSpec_copy(this_: *mut OIIO_ImageSpec_t, other: *const OIIO_ImageSpec_t) -> c_void;

pub fn OpenImageIO_v2_2__ImageSpec_assign(this_: *mut OIIO_ImageSpec_t, other: *const OIIO_ImageSpec_t) -> *mut OIIO_ImageSpec_t;

/// Return the name of the format implemented by this class.
pub fn OpenImageIO_v2_2__ImageInput_format_name(this_: *const OIIO_ImageInput_t) -> *const c_char;

/// If any of the API routines returned false indicating an error, this
/// method will return the error string (and clear any error flags).  If
/// no error has occurred since the last time `geterror()` was called,
/// it will return an empty string.
pub fn OpenImageIO_v2_2__ImageInput_geterror(this_: *const OIIO_ImageInput_t) -> std___cxx11_string_t;

/// Union of two regions, the smallest region containing both.
pub fn OpenImageIO_v2_2_roi_union(a: *const OIIO_ROI_t, b: *const OIIO_ROI_t) -> OIIO_ROI_t;

/// Intersection of two regions.
pub fn OpenImageIO_v2_2_roi_intersection(a: *const OIIO_ROI_t, b: *const OIIO_ROI_t) -> OIIO_ROI_t;


} // extern "C"
