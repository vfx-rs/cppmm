#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(8))]
pub struct OpenImageIO_v2_2__Filesystem__IOProxy_t {
    _inner: [u8; 88]
}

#[repr(C, align(8))]
pub struct OpenImageIO_v2_2__Filesystem__IOMemReader_t {
    _inner: [u8; 104]
}


#[repr(transparent)]
pub struct OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(pub u32);
pub const OIIO_Filesystem_IOProxy_Mode_Closed: OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e = OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(0);
pub const OIIO_Filesystem_IOProxy_Mode_Read: OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e = OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(114);
pub const OIIO_Filesystem_IOProxy_Mode_Write: OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e = OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e(119);


extern "C" {

pub fn OpenImageIO_v2_2__Filesystem__IOProxy_delete(this_: *mut OIIO_Filesystem_IOProxy_t);
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_proxytype(this_: *const OIIO_Filesystem_IOProxy_t) -> *const c_char;
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_close(this_: *mut OIIO_Filesystem_IOProxy_t);
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_opened(this_: *const OIIO_Filesystem_IOProxy_t) -> bool;
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_tell(this_: *mut OIIO_Filesystem_IOProxy_t) -> c_long;
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_seek(this_: *mut OIIO_Filesystem_IOProxy_t, offset: c_long) -> bool;
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_read(this_: *mut OIIO_Filesystem_IOProxy_t, buf: *mut void, size: c_ulong) -> c_ulong;
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_write(this_: *mut OIIO_Filesystem_IOProxy_t, buf: *const void, size: c_ulong) -> c_ulong;
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_pread(this_: *mut OIIO_Filesystem_IOProxy_t, buf: *mut void, size: c_ulong, offset: c_long) -> c_ulong;
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_pwrite(this_: *mut OIIO_Filesystem_IOProxy_t, buf: *const void, size: c_ulong, offset: c_long) -> c_ulong;
pub fn OpenImageIO_v2_2__Filesystem__IOProxy_seek_1(this_: *mut OIIO_Filesystem_IOProxy_t, offset: c_long, origin: c_int) -> bool;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_proxytype(this_: *const OIIO_Filesystem_IOMemReader_t) -> *const c_char;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_close(this_: *mut OIIO_Filesystem_IOMemReader_t);
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_opened(this_: *const OIIO_Filesystem_IOMemReader_t) -> bool;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_tell(this_: *mut OIIO_Filesystem_IOMemReader_t) -> c_long;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_seek(this_: *mut OIIO_Filesystem_IOMemReader_t, offset: c_long) -> bool;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_read(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *mut void, size: c_ulong) -> c_ulong;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_write(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *const void, size: c_ulong) -> c_ulong;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_pread(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *mut void, size: c_ulong, offset: c_long) -> c_ulong;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_pwrite(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *const void, size: c_ulong, offset: c_long) -> c_ulong;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_seek_1(this_: *mut OIIO_Filesystem_IOMemReader_t, offset: c_long, origin: c_int) -> bool;
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_new(this_: *mut OIIO_Filesystem_IOMemReader_t, buf: *mut void, size: c_ulong);
pub fn OpenImageIO_v2_2__Filesystem__IOMemReader_delete(this_: *mut OIIO_Filesystem_IOMemReader_t);

} // extern "C"
