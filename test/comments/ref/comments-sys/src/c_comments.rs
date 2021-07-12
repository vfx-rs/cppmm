#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C)]
pub struct comments__Class_t {
    _unused: [u8; 0],
}


extern "C" {

pub fn comments__Class_method(this_: *mut comments_Class_t) -> Exception;

pub fn comments_function() -> Exception;


} // extern "C"
