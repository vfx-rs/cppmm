#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(8))]
pub struct std__vector_std__string__t {
    _inner: [u8; 24]
}



extern "C" {

pub fn std__vector_std__string__vector(this_: *mut std_vector_string_t);
pub fn std__vector_std__string__dtor(this_: *mut std_vector_string_t);

} // extern "C"
