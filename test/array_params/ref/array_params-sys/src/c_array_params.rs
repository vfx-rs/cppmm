#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;

#[repr(C, align(4))]
#[derive(Clone)]
pub struct imath__Matrix44_float__t {
    pub data: *mut c_float,
}



extern "C" {

pub fn imath__Matrix44_float__from_array(this_: *mut imath_M44f_t, a: *const c_float) -> Exception;


} // extern "C"
