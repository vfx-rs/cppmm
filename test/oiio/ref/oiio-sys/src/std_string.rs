#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C)]
pub struct std____cxx11__basic_string_char__t {
    _unused: [u8; 0],
}


extern "C" {

pub fn std____cxx11__basic_string_char__basic_string(this_: *mut *mut std___cxx11_string_t) -> Exception;

pub fn std____cxx11__basic_string_char__basic_string_1(this_: *mut *mut std___cxx11_string_t, rhs: *const std___cxx11_string_t) -> Exception;

pub fn std____cxx11__basic_string_char__assign(this_: *mut std___cxx11_string_t, return_: *mut *mut std___cxx11_string_t, s: *const c_char, count: c_ulong) -> Exception;

pub fn std____cxx11__basic_string_char__c_str(this_: *const std___cxx11_string_t, return_: *mut *const c_char) -> Exception;


} // extern "C"
