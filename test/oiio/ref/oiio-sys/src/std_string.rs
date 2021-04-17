#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(8))]
#[derive(Clone)]
pub struct std____cxx11__basic_string_char__t {
    _inner: [u8; 32]
}

impl Default for std____cxx11__basic_string_char__t {
    fn default() -> Self {
        Self { _inner: [0u8; 32] }
    }
}



extern "C" {

pub fn std____cxx11__basic_string_char__basic_string(this_: *mut std___cxx11_string_t) -> c_void;
pub fn std____cxx11__basic_string_char__basic_string_1(this_: *mut std___cxx11_string_t, rhs: *const std___cxx11_string_t) -> c_void;
pub fn std____cxx11__basic_string_char__assign(this_: *mut std___cxx11_string_t, s: *const c_char, count: c_ulong) -> *mut std___cxx11_string_t;
pub fn std____cxx11__basic_string_char__c_str(this_: *const std___cxx11_string_t) -> *const c_char;

} // extern "C"
