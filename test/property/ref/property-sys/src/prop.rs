#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C)]
pub struct prop__Bar_t {
    _unused: [u8; 0],
}
#[repr(C)]
pub struct prop__Foo_t {
    _unused: [u8; 0],
}


extern "C" {

pub fn prop__Foo_bum() -> Exception;

pub fn prop__Foo_get_a(this_: *const prop_Foo_t, return_: *mut *const c_int) -> Exception;

pub fn prop__Foo_set_a(this_: *mut prop_Foo_t, value: *const c_int) -> Exception;

pub fn prop__Foo_get_b(this_: *const prop_Foo_t, return_: *mut *const c_float) -> Exception;

pub fn prop__Foo_set_b(this_: *mut prop_Foo_t, value: *const c_float) -> Exception;

pub fn prop__Foo_get_bar(this_: *const prop_Foo_t, return_: *mut *const prop_Bar_t) -> Exception;

pub fn prop__Foo_set_bar(this_: *mut prop_Foo_t, value: *const prop_Bar_t) -> Exception;

pub fn prop__Foo_get_u(this_: *const prop_Foo_t, return_: *mut *const u64) -> Exception;

pub fn prop__Foo_set_u(this_: *mut prop_Foo_t, value: *const u64) -> Exception;

pub fn prop_fuz(return_: *mut u64, a: *mut u64, b: *mut u64, c: u64) -> Exception;


} // extern "C"
