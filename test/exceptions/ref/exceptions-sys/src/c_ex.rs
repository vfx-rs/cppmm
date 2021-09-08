#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;


impl ex__Struct_t {
    pub fn layout() -> std::alloc::Layout {
        unsafe {
            std::alloc::Layout::from_size_align(
                ex__Struct_sizeof(),
                ex__Struct_alignof(),
            ).unwrap()
        }
    }
}



extern "C" {

pub fn ex__Struct_sizeof() -> usize;

pub fn ex__Struct_alignof() -> usize;

pub fn ex__Struct_m1(this_: *mut ex_Struct_t) -> Exception;

pub fn ex__Struct_m2(this_: *mut ex_Struct_t, return_: *mut c_float, a: c_float) -> Exception;

pub fn ex__Struct_m3(this_: *const ex_Struct_t, return_: *mut c_float, a: c_int) -> Exception;

pub fn ex__Struct_m4(this_: *const ex_Struct_t, return_: *mut c_float, a: c_int) -> Exception;

pub fn ex_f1(return_: *mut c_float, a: c_int) -> Exception;

pub fn ex_f2() -> Exception;


} // extern "C"
