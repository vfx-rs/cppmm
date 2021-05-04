#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(1))]
#[derive(Clone)]
pub struct ex__Struct_t {
    _inner: [u8; 1]
}

impl Default for ex__Struct_t {
    fn default() -> Self {
        Self { _inner: [0u8; 1] }
    }
}



extern "C" {

pub fn ex__Struct_m1(this_: *mut ex_Struct_t) -> Exception;

pub fn ex__Struct_m2(this_: *mut ex_Struct_t, return_: *mut c_float, a: c_float) -> Exception;

pub fn ex_f1(return_: *mut c_float, a: c_int) -> Exception;

pub fn ex_f2() -> Exception;


} // extern "C"
