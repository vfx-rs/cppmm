#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(4))]
#[derive(Clone)]
pub struct Imath_2_5__Vec3_float__t {
    _inner: [u8; 12]
}

impl Default for Imath_2_5__Vec3_float__t {
    fn default() -> Self {
        Self { _inner: [0u8; 12] }
    }
}

#[repr(C, align(4))]
#[derive(Clone)]
pub struct Imath_2_5__Vec3_int__t {
    _inner: [u8; 12]
}

impl Default for Imath_2_5__Vec3_int__t {
    fn default() -> Self {
        Self { _inner: [0u8; 12] }
    }
}



extern "C" {

pub fn Imath_2_5__Vec3_float__Vec3(this_: *mut Imath_V3f_t) -> c_void;
pub fn Imath_2_5__Vec3_float__Vec3_1(this_: *mut Imath_V3f_t, v: *const Imath_V3f_t) -> c_void;
pub fn Imath_2_5__Vec3_float__setValue(this_: *mut Imath_V3f_t, a: c_float, b: c_float, c: c_float) -> c_void;
pub fn Imath_2_5__Vec3_float__dot(this_: *const Imath_V3f_t, v: *const Imath_V3f_t) -> c_float;
pub fn Imath_2_5__Vec3_float__cross(this_: *const Imath_V3f_t, v: *const Imath_V3f_t) -> Imath_V3f_t;
pub fn Imath_2_5__Vec3_float__op_iadd(this_: *mut Imath_V3f_t, v: *const Imath_V3f_t) -> *const Imath_V3f_t;
pub fn Imath_2_5__Vec3_float__length(this_: *const Imath_V3f_t) -> c_float;
pub fn Imath_2_5__Vec3_float__length2(this_: *const Imath_V3f_t) -> c_float;
pub fn Imath_2_5__Vec3_float__normalize(this_: *mut Imath_V3f_t) -> *const Imath_V3f_t;
pub fn Imath_2_5__Vec3_float__normalized(this_: *const Imath_V3f_t) -> Imath_V3f_t;
pub fn Imath_2_5__Vec3_int__Vec3(this_: *mut Imath_V3i_t) -> c_void;
pub fn Imath_2_5__Vec3_int__Vec3_1(this_: *mut Imath_V3i_t, v: *const Imath_V3i_t) -> c_void;
pub fn Imath_2_5__Vec3_int__dot(this_: *const Imath_V3i_t, v: *const Imath_V3i_t) -> c_int;
pub fn Imath_2_5__Vec3_int__cross(this_: *const Imath_V3i_t, v: *const Imath_V3i_t) -> Imath_V3i_t;
pub fn Imath_2_5__Vec3_int__op_iadd(this_: *mut Imath_V3i_t, v: *const Imath_V3i_t) -> *const Imath_V3i_t;
pub fn Imath_2_5__Vec3_int__length(this_: *const Imath_V3i_t) -> c_int;
pub fn Imath_2_5__Vec3_int__length2(this_: *const Imath_V3i_t) -> c_int;
pub fn Imath_2_5__Vec3_int__normalize(this_: *mut Imath_V3i_t) -> *const Imath_V3i_t;
pub fn Imath_2_5__Vec3_int__normalized(this_: *const Imath_V3i_t) -> Imath_V3i_t;

} // extern "C"
