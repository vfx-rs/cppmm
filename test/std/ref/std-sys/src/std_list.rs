#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;

#[repr(C)]
pub struct std__list_std__string__t {
    _unused: [u8; 0],
}
#[repr(C)]
pub struct std__list_std__string___iterator_t {
    _unused: [u8; 0],
}


extern "C" {

pub fn std__list_std__string__ctor(this_: *mut *mut std_list_string_t) -> Exception;

pub fn std__list_std__string___iterator_op_inc(this_: *mut std_list_string_iterator_t, return_: *mut *mut std_list_string_iterator_t) -> Exception;

pub fn std__list_std__string___iterator_deref(this_: *const std_list_string_iterator_t, return_: *mut *const std_string_t) -> Exception;

pub fn std__list_std__string___iterator_deref_mut(this_: *mut std_list_string_iterator_t, return_: *mut *mut std_string_t) -> Exception;


} // extern "C"
