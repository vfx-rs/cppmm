#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

/// Proxy class for I/O. This provides a simplified interface for file I/O
/// that can have custom overrides.
#[repr(C)]
pub struct OpenImageIO_v2_2__Filesystem__IOProxy_t {
    _unused: [u8; 0],
}
/// IOProxy subclass for reading that wraps an cspan<char>.
#[repr(C)]
pub struct OpenImageIO_v2_2__Filesystem__IOMemReader_t {
    _unused: [u8; 0],
}

#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(pub u32);
pub const OIIO_Filesystem_IOProxy_Mode_Closed: OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e = OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(0);
pub const OIIO_Filesystem_IOProxy_Mode_Read: OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e = OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(114);
pub const OIIO_Filesystem_IOProxy_Mode_Write: OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e = OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(119);


extern "C" {

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_delete(this_: *mut OIIO_Filesystem_IOProxy_t) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_proxytype(this_: *const OIIO_Filesystem_IOProxy_t, return_: *mut *const c_char) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_close(this_: *mut OIIO_Filesystem_IOProxy_t) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_opened(this_: *const OIIO_Filesystem_IOProxy_t, return_: *mut bool) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_tell(this_: *mut OIIO_Filesystem_IOProxy_t, return_: *mut c_long) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_seek(this_: *mut OIIO_Filesystem_IOProxy_t, return_: *mut bool, offset: c_long) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_read(this_: *mut OIIO_Filesystem_IOProxy_t, return_: *mut c_ulong, buf: *mut c_void, size: c_ulong) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_write(this_: *mut OIIO_Filesystem_IOProxy_t, return_: *mut c_ulong, buf: *const c_void, size: c_ulong) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_pread(this_: *mut OIIO_Filesystem_IOProxy_t, return_: *mut c_ulong, buf: *mut c_void, size: c_ulong, offset: c_long) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_pwrite(this_: *mut OIIO_Filesystem_IOProxy_t, return_: *mut c_ulong, buf: *const c_void, size: c_ulong, offset: c_long) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_filename(this_: *const OIIO_Filesystem_IOProxy_t, return_: *mut *const std___cxx11_string_t) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_seek_1(this_: *mut OIIO_Filesystem_IOProxy_t, return_: *mut bool, offset: c_long, origin: c_int) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_proxytype(this_: *const OIIO_Filesystem_IOMemReader_t, return_: *mut *const c_char) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_close(this_: *mut OIIO_Filesystem_IOMemReader_t) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_opened(this_: *const OIIO_Filesystem_IOMemReader_t, return_: *mut bool) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_tell(this_: *mut OIIO_Filesystem_IOMemReader_t, return_: *mut c_long) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_seek(this_: *mut OIIO_Filesystem_IOMemReader_t, return_: *mut bool, offset: c_long) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_read(this_: *mut OIIO_Filesystem_IOMemReader_t, return_: *mut c_ulong, buf: *mut c_void, size: c_ulong) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_write(this_: *mut OIIO_Filesystem_IOMemReader_t, return_: *mut c_ulong, buf: *const c_void, size: c_ulong) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_pread(this_: *mut OIIO_Filesystem_IOMemReader_t, return_: *mut c_ulong, buf: *mut c_void, size: c_ulong, offset: c_long) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_pwrite(this_: *mut OIIO_Filesystem_IOMemReader_t, return_: *mut c_ulong, buf: *const c_void, size: c_ulong, offset: c_long) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_seek_1(this_: *mut OIIO_Filesystem_IOMemReader_t, return_: *mut bool, offset: c_long, origin: c_int) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_new(this_: *mut *mut OIIO_Filesystem_IOMemReader_t, buf: *mut c_void, size: c_ulong) -> Exception;

pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_delete(this_: *mut OIIO_Filesystem_IOMemReader_t) -> Exception;

/// Return the filename (excluding any directories, but including the
/// file extension, if any) of a filepath.
pub fn OpenImageIO_v2_2_Filesystem_filename(return_: *mut *mut std___cxx11_string_t, filepath: *const std___cxx11_string_t) -> Exception;

/// Return the file extension (including the last '.' if
/// include_dot=true) of a filename or filepath.
pub fn OpenImageIO_v2_2_Filesystem_extension(return_: *mut *mut std___cxx11_string_t, filepath: *const std___cxx11_string_t, include_dot: bool) -> Exception;

/// Return all but the last part of the path, for example,
/// parent_path("foo/bar") returns "foo", and parent_path("foo")
/// returns "".
pub fn OpenImageIO_v2_2_Filesystem_parent_path(return_: *mut *mut std___cxx11_string_t, filepath: *const std___cxx11_string_t) -> Exception;

/// Replace the file extension of a filename or filepath. Does not alter
/// filepath, just returns a new string.  Note that the new_extension
/// should contain a leading '.' dot.
pub fn OpenImageIO_v2_2_Filesystem_replace_extension(return_: *mut *mut std___cxx11_string_t, filepath: *const std___cxx11_string_t, new_extension: *const std___cxx11_string_t) -> Exception;


} // extern "C"
