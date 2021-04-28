#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(4))]
#[derive(Clone)]
pub struct specs__Attribute_int__t {
    _inner: [u8; 4]
}

impl Default for specs__Attribute_int__t {
    fn default() -> Self {
        Self { _inner: [0u8; 4] }
    }
}

#[repr(C, align(4))]
#[derive(Clone)]
pub struct specs__Attribute_float__t {
    _inner: [u8; 4]
}

impl Default for specs__Attribute_float__t {
    fn default() -> Self {
        Self { _inner: [0u8; 4] }
    }
}

#[repr(C, align(1))]
#[derive(Clone)]
pub struct specs__Specs_t {
    _inner: [u8; 1]
}

impl Default for specs__Specs_t {
    fn default() -> Self {
        Self { _inner: [0u8; 1] }
    }
}



extern "C" {

pub fn specs__Attribute_int__value(this_: *mut specs_IntAttribute_t) -> *const c_int;

pub fn specs__Attribute_float__value(this_: *mut specs_FloatAttribute_t) -> *const c_float;

pub fn specs__Specs_findAttribute_int(this_: *mut specs_Specs_t, name: *const c_char) -> *mut specs_IntAttribute_t;

pub fn specs__Specs_findAttribute_float(this_: *mut specs_Specs_t, name: *const c_char) -> *mut specs_FloatAttribute_t;


} // extern "C"
