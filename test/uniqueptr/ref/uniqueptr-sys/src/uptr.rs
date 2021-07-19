#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C)]
pub struct std__unique_ptr_foo__Foo__t {
    _unused: [u8; 0],
}


extern "C" {

pub fn std__unique_ptr_foo__Foo__ctor(this_: *mut *mut std_FooPtr_t, p: *mut foo_Foo_t) -> Exception;

pub fn std__unique_ptr_foo__Foo__dtor(this_: *mut std_FooPtr_t) -> Exception;

pub fn std__unique_ptr_foo__Foo__get(this_: *const std_FooPtr_t, return_: *mut *mut foo_Foo_t) -> Exception;


} // extern "C"
