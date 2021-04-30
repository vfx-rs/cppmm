#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C)]
pub struct specs__Attribute_int__t {
    _unused: [u8; 0],
}
#[repr(C)]
pub struct specs__Attribute_float__t {
    _unused: [u8; 0],
}
#[repr(C)]
pub struct specs__Specs_t {
    _unused: [u8; 0],
}


extern "C" {

pub fn specs__Attribute_int__value(this_: *mut specs_IntAttribute_t) -> *const c_int;

pub fn specs__Attribute_float__value(this_: *mut specs_FloatAttribute_t) -> *const c_float;

pub fn specs__Specs_findAttribute_int(this_: *mut specs_Specs_t, name: *const c_char) -> *mut specs_IntAttribute_t;

pub fn specs__Specs_findAttribute_float(this_: *mut specs_Specs_t, name: *const c_char) -> *mut specs_FloatAttribute_t;

pub fn specs__Specs_findAttribute_int_const(this_: *const specs_Specs_t, name: *const c_char) -> *const specs_IntAttribute_t;

pub fn specs__Specs_findAttribute_float_const(this_: *const specs_Specs_t, name: *const c_char) -> *const specs_FloatAttribute_t;


} // extern "C"
