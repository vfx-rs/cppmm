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
pub struct specs__Attribute_std__string__t {
    _unused: [u8; 0],
}
#[repr(C)]
pub struct specs__Specs_t {
    _unused: [u8; 0],
}


extern "C" {

pub fn specs__Attribute_int__value(this_: *mut specs_IntAttribute_t, return_: *mut *const c_int) -> Exception;

pub fn specs__Attribute_int__do_something(v: *mut c_int) -> Exception;

pub fn specs__Attribute_int__ctor(this_: *mut *mut specs_IntAttribute_t) -> Exception;

pub fn specs__Attribute_float__value(this_: *mut specs_FloatAttribute_t, return_: *mut *const c_float) -> Exception;

pub fn specs__Attribute_float__do_something(v: *mut c_float) -> Exception;

pub fn specs__Attribute_float__ctor(this_: *mut *mut specs_FloatAttribute_t) -> Exception;

pub fn specs__Attribute_std__string__value(this_: *mut specs_StringAttribute_t, return_: *mut *const std_string_t) -> Exception;

pub fn specs__Attribute_std__string__do_something(v: *mut std_string_t) -> Exception;

pub fn specs__Attribute_std__string__ctor(this_: *mut *mut specs_StringAttribute_t) -> Exception;

pub fn specs__Attribute_std__string__dtor(this_: *mut specs_StringAttribute_t) -> Exception;

pub fn specs__Specs_findAttribute_int(this_: *mut specs_Specs_t, return_: *mut *mut specs_IntAttribute_t, name: *const c_char) -> Exception;

pub fn specs__Specs_findAttribute_float(this_: *mut specs_Specs_t, return_: *mut *mut specs_FloatAttribute_t, name: *const c_char) -> Exception;

pub fn specs__Specs_findAttribute_int_const(this_: *const specs_Specs_t, return_: *mut *const specs_IntAttribute_t, name: *const c_char) -> Exception;

pub fn specs__Specs_findAttribute_float_const(this_: *const specs_Specs_t, return_: *mut *const specs_FloatAttribute_t, name: *const c_char) -> Exception;


} // extern "C"
