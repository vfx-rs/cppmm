#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

/// Proxy class for I/O. This provides a simplified interface for file I/O
/// that can have custom overrides.
#[repr(C, align(8))]
#[derive(Clone)]
pub struct OpenImageIO_v2_2__Filesystem__IOProxy_t {
    _inner: [u8; 88]
}

impl Default for OpenImageIO_v2_2__Filesystem__IOProxy_t {
    fn default() -> Self {
        Self { _inner: [0u8; 88] }
    }
}

/// IOProxy subclass for reading that wraps an cspan<char>.
#[repr(C, align(8))]
#[derive(Clone)]
pub struct OpenImageIO_v2_2__Filesystem__IOMemReader_t {
    _inner: [u8; 104]
}

impl Default for OpenImageIO_v2_2__Filesystem__IOMemReader_t {
    fn default() -> Self {
        Self { _inner: [0u8; 104] }
    }
}


#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(pub u32);
pub const OIIO_Filesystem_IOProxy_Mode_Closed: OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e = OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(0);
pub const OIIO_Filesystem_IOProxy_Mode_Read: OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e = OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(114);
pub const OIIO_Filesystem_IOProxy_Mode_Write: OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e = OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(119);


extern "C" {

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_delete(this_: *mut OIIO_Filesystem_IOProxy_t) -> c_void;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_proxytype(this_: *const OIIO_Filesystem_IOProxy_t) -> *const c_char;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_close(this_: *mut OIIO_Filesystem_IOProxy_t) -> c_void;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_opened(this_: *const OIIO_Filesystem_IOProxy_t) -> bool;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_tell(this_: *mut OIIO_Filesystem_IOProxy_t) -> c_long;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_seek(this_: *mut OIIO_Filesystem_IOProxy_t, offset: c_long) -> bool;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_read(this_: *mut OIIO_Filesystem_IOProxy_t, buf: *mut c_void, size: c_ulong) -> c_ulong;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_write(this_: *mut OIIO_Filesystem_IOProxy_t, buf: *const c_void, size: c_ulong) -> c_ulong;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_pread(this_: *mut OIIO_Filesystem_IOProxy_t, buf: *mut c_void, size: c_ulong, offset: c_long) -> c_ulong;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_pwrite(this_: *mut OIIO_Filesystem_IOProxy_t, buf: *const c_void, size: c_ulong, offset: c_long) -> c_ulong;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_filename(this_: *const OIIO_Filesystem_IOProxy_t) -> *const std___cxx11_string_t;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_seek_1(this_: *mut OIIO_Filesystem_IOProxy_t, offset: c_long, origin: c_int) -> bool;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_proxytype(this_: *const OIIO_Filesystem_IOMemReader_t) -> *const c_char;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_close(this_: *mut OIIO_Filesystem_IOMemReader_t) -> c_void;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_opened(this_: *const OIIO_Filesystem_IOMemReader_t) -> bool;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_tell(this_: *mut OIIO_Filesystem_IOMemReader_t) -> c_long;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_seek(this_: *mut OIIO_Filesystem_IOMemReader_t, offset: c_long) -> bool;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_read(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *mut c_void, size: c_ulong) -> c_ulong;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_write(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *const c_void, size: c_ulong) -> c_ulong;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_pread(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *mut c_void, size: c_ulong, offset: c_long) -> c_ulong;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_pwrite(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *const c_void, size: c_ulong, offset: c_long) -> c_ulong;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_seek_1(this_: *mut OIIO_Filesystem_IOMemReader_t, offset: c_long, origin: c_int) -> bool;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_new(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *mut c_void, size: c_ulong) -> c_void;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_delete(this_: *mut OIIO_Filesystem_IOMemReader_t) -> c_void;

/// Return the filename (excluding any directories, but including the
/// file extension, if any) of a filepath.
pub fn OpenImageIO_v2_2_Filesystem_filename(filepath: *const std___cxx11_string_t) -> std___cxx11_string_t;

/// Return the file extension (including the last '.' if
/// include_dot=true) of a filename or filepath.
pub fn OpenImageIO_v2_2_Filesystem_extension(filepath: *const std___cxx11_string_t, include_dot: bool) -> std___cxx11_string_t;

/// Return all but the last part of the path, for example,
/// parent_path("foo/bar") returns "foo", and parent_path("foo")
/// returns "".
pub fn OpenImageIO_v2_2_Filesystem_parent_path(filepath: *const std___cxx11_string_t) -> std___cxx11_string_t;

/// Replace the file extension of a filename or filepath. Does not alter
/// filepath, just returns a new string.  Note that the new_extension
/// should contain a leading '.' dot.
pub fn OpenImageIO_v2_2_Filesystem_replace_extension(filepath: *const std___cxx11_string_t, new_extension: *const std___cxx11_string_t) -> std___cxx11_string_t;


} // extern "C"
