#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;

#[repr(C)]
pub struct dtor__Struct_t {
    _unused: [u8; 0],
}


extern "C" {

pub fn dtor__Struct_ctor(this_: *mut *mut dtor_Struct_t) -> Exception;

pub fn dtor__Struct_dtor(this_: *mut dtor_Struct_t) -> Exception;


} // extern "C"
