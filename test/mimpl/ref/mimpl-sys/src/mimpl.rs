#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;

#[repr(C)]
pub struct mimpl__Number_t {
    _unused: [u8; 0],
}


extern "C" {

pub fn mimpl__Number_ctor(this_: *mut *mut mimpl_Number_t) -> Exception;

pub fn mimpl__Number_get_number(this_: *const mimpl_Number_t, return_: *mut c_int) -> Exception;

pub fn Number_do_get_number(return_: *mut c_int, self_: *const mimpl_Number_t) -> Exception;


} // extern "C"
