#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;

#[repr(C, align(4))]
#[derive(Clone)]
pub struct nest__NestAE_t {
    pub a: c_int,
}



extern "C" {

pub fn nest__NestAE_do_something(this_: *mut nest_NestAE_t) -> Exception;


} // extern "C"
