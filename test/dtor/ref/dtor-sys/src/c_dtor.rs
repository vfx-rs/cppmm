#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(8))]
#[derive(Clone)]
pub struct dtor__Struct_t {
    _inner: [u8; 48]
}

impl Default for dtor__Struct_t {
    fn default() -> Self {
        Self { _inner: [0u8; 48] }
    }
}



extern "C" {

pub fn dtor__Struct_Struct(this_: *mut dtor_Struct_t) -> c_void;

pub fn dtor__Struct_dtor(this_: *mut dtor_Struct_t) -> c_void;


} // extern "C"
