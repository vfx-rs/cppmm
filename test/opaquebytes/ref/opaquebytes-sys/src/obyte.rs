#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;


impl obyte__Foo_t {
    pub fn layout() -> std::alloc::Layout {
        unsafe {
            std::alloc::Layout::from_size_align(
                obyte__Foo_sizeof(),
                obyte__Foo_alignof(),
            ).unwrap()
        }
    }
}



extern "C" {

pub fn obyte__Foo_sizeof() -> usize;

pub fn obyte__Foo_alignof() -> usize;


} // extern "C"
