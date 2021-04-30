#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C)]
pub struct optr__PubCtor_t {
    _unused: [u8; 0],
}
#[repr(C)]
pub struct optr__PrvCtor_t {
    _unused: [u8; 0],
}
#[repr(C)]
pub struct optr__AllPrv_t {
    _unused: [u8; 0],
}
#[repr(C)]
pub struct optr__Opaque_t {
    _unused: [u8; 0],
}


extern "C" {

pub fn optr__PubCtor_ctor(this_: *mut *mut optr_PubCtor_t) -> c_void;

pub fn optr__PubCtor_dtor(this_: *mut optr_PubCtor_t) -> c_void;

pub fn optr__PubCtor_doit(this_: *mut optr_PubCtor_t) -> c_void;

pub fn optr__PrvCtor_doit(this_: *mut optr_PrvCtor_t) -> c_void;


} // extern "C"
