#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(4))]
#[derive(Clone)]
pub struct nest__NestBE_t {
    pub b: c_int,
}



extern "C" {

pub fn nest__NestBE_do_something(this_: *mut nest_NestBE_t) -> Exception;


} // extern "C"
