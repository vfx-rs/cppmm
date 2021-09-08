#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;

#[repr(C)]
pub struct foo__Foo_t {
    _unused: [u8; 0],
}


extern "C" {

pub fn foo__Foo_ctor(this_: *mut *mut foo_Foo_t) -> Exception;

pub fn foo__Foo_dtor(this_: *mut foo_Foo_t) -> Exception;

pub fn foo__Foo_create(return_: *mut *mut std_FooPtr_t) -> Exception;


} // extern "C"
