#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;



extern "C" {

pub fn usestd_takes_string(s: *const std___cxx11_string_t) -> c_void;

pub fn usestd_takes_vector_string(v: *const std_vector_string_t) -> c_void;


} // extern "C"
