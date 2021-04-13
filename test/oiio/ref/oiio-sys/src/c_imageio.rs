#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(4))]
#[derive(Clone)]
pub struct OpenImageIO_v2_2__ROI_t {
    _inner: [u8; 32]
}

impl Default for OpenImageIO_v2_2__ROI_t {
    fn default() -> Self {
        Self { _inner: [0u8; 32] }
    }
}

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
pub struct OpenImageIO_v2_2__ImageSpec__SerialFormat_e(pub u32);
pub const OIIO_ImageSpec_SerialFormat_SerialText: OpenImageIO_v2_2__ImageSpec__SerialFormat_e = OpenImageIO_v2_2__ImageSpec__SerialFormat_e(0);
pub const OIIO_ImageSpec_SerialFormat_SerialXML: OpenImageIO_v2_2__ImageSpec__SerialFormat_e = OpenImageIO_v2_2__ImageSpec__SerialFormat_e(1);

#[repr(transparent)]
pub struct OpenImageIO_v2_2__ImageSpec__SerialVerbose_e(pub u32);
pub const OIIO_ImageSpec_SerialVerbose_SerialBrief: OpenImageIO_v2_2__ImageSpec__SerialVerbose_e = OpenImageIO_v2_2__ImageSpec__SerialVerbose_e(0);
pub const OIIO_ImageSpec_SerialVerbose_SerialDetailed: OpenImageIO_v2_2__ImageSpec__SerialVerbose_e = OpenImageIO_v2_2__ImageSpec__SerialVerbose_e(1);
pub const OIIO_ImageSpec_SerialVerbose_SerialDetailedHuman: OpenImageIO_v2_2__ImageSpec__SerialVerbose_e = OpenImageIO_v2_2__ImageSpec__SerialVerbose_e(2);


extern "C" {

pub fn OpenImageIO_v2_2__ROI_default(this_: *mut OIIO_ROI_t);
pub fn OpenImageIO_v2_2__ROI_defined(this_: *const OIIO_ROI_t) -> bool;
pub fn OpenImageIO_v2_2__ROI_width(this_: *const OIIO_ROI_t) -> c_int;
pub fn OpenImageIO_v2_2__ROI_height(this_: *const OIIO_ROI_t) -> c_int;
pub fn OpenImageIO_v2_2__ROI_depth(this_: *const OIIO_ROI_t) -> c_int;
pub fn OpenImageIO_v2_2__ROI_nchannels(this_: *const OIIO_ROI_t) -> c_int;
pub fn OpenImageIO_v2_2__ROI_npixels(this_: *const OIIO_ROI_t) -> c_ulong;
pub fn OpenImageIO_v2_2__ImageSpec_ImageSpec(this_: *mut OIIO_ImageSpec_t, format: OIIO_TypeDesc_t);
pub fn OpenImageIO_v2_2__ImageSpec_new_with_dimensions(this_: *mut OIIO_ImageSpec_t, xres: c_int, yres: c_int, nchans: c_int, fmt: OIIO_TypeDesc_t);
pub fn OpenImageIO_v2_2__ImageSpec_set_format(this_: *mut OIIO_ImageSpec_t, fmt: OIIO_TypeDesc_t);
pub fn OpenImageIO_v2_2__ImageSpec_default_channel_names(this_: *mut OIIO_ImageSpec_t);
pub fn OpenImageIO_v2_2__ImageSpec_channel_bytes(this_: *const OIIO_ImageSpec_t) -> c_ulong;
pub fn OpenImageIO_v2_2__ImageSpec_channel_bytes_for(this_: *const OIIO_ImageSpec_t, chan: c_int, native: bool) -> c_ulong;
pub fn OpenImageIO_v2_2__ImageSpec_scanline_bytes(this_: *const OIIO_ImageSpec_t, native: bool) -> c_ulong;
pub fn OpenImageIO_v2_2__ImageSpec_copy(this_: *mut OIIO_ImageSpec_t, other: *const OIIO_ImageSpec_t);
pub fn OpenImageIO_v2_2__ImageSpec_assign(this_: *mut OIIO_ImageSpec_t, other: *const OIIO_ImageSpec_t) -> *mut OIIO_ImageSpec_t;
pub fn OpenImageIO_v2_2__ImageInput_format_name(this_: *const OIIO_ImageInput_t) -> *const c_char;
pub fn OpenImageIO_v2_2_roi_union(A: *const OIIO_ROI_t, B: *const OIIO_ROI_t) -> OIIO_ROI_t;
pub fn OpenImageIO_v2_2_roi_intersection(A: *const OIIO_ROI_t, B: *const OIIO_ROI_t) -> OIIO_ROI_t;

} // extern "C"
