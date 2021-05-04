#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(4))]
#[derive(Clone)]
pub struct Imath_2_5__Vec3_float__t {
    pub x: c_float,
    pub y: c_float,
    pub z: c_float,
}

#[repr(C, align(4))]
#[derive(Clone)]
pub struct Imath_2_5__Vec3_int__t {
    pub x: c_int,
    pub y: c_int,
    pub z: c_int,
}



extern "C" {

pub fn Imath_2_5__Vec3_float__Vec3(this_: *mut Imath_V3f_t) -> Exception;

pub fn Imath_2_5__Vec3_float__Vec3_1(this_: *mut Imath_V3f_t, rhs: *const Imath_V3f_t) -> Exception;

pub fn Imath_2_5__Vec3_float__setValue(this_: *mut Imath_V3f_t, a: c_float, b: c_float, c: c_float) -> Exception;

pub fn Imath_2_5__Vec3_float__dot(this_: *const Imath_V3f_t, return_: *mut c_float, v: *const Imath_V3f_t) -> Exception;

pub fn Imath_2_5__Vec3_float__cross(this_: *const Imath_V3f_t, return_: *mut Imath_V3f_t, v: *const Imath_V3f_t) -> Exception;

pub fn Imath_2_5__Vec3_float__op_iadd(this_: *mut Imath_V3f_t, return_: *mut *const Imath_V3f_t, v: *const Imath_V3f_t) -> Exception;

pub fn Imath_2_5__Vec3_float__length(this_: *const Imath_V3f_t, return_: *mut c_float) -> Exception;

pub fn Imath_2_5__Vec3_float__length2(this_: *const Imath_V3f_t, return_: *mut c_float) -> Exception;

pub fn Imath_2_5__Vec3_float__normalize(this_: *mut Imath_V3f_t, return_: *mut *const Imath_V3f_t) -> Exception;

pub fn Imath_2_5__Vec3_float__normalized(this_: *const Imath_V3f_t, return_: *mut Imath_V3f_t) -> Exception;

pub fn Imath_2_5__Vec3_int__Vec3(this_: *mut Imath_V3i_t) -> Exception;

pub fn Imath_2_5__Vec3_int__Vec3_1(this_: *mut Imath_V3i_t, rhs: *const Imath_V3i_t) -> Exception;

pub fn Imath_2_5__Vec3_int__dot(this_: *const Imath_V3i_t, return_: *mut c_int, v: *const Imath_V3i_t) -> Exception;

pub fn Imath_2_5__Vec3_int__cross(this_: *const Imath_V3i_t, return_: *mut Imath_V3i_t, v: *const Imath_V3i_t) -> Exception;

pub fn Imath_2_5__Vec3_int__op_iadd(this_: *mut Imath_V3i_t, return_: *mut *const Imath_V3i_t, v: *const Imath_V3i_t) -> Exception;

pub fn Imath_2_5__Vec3_int__length(this_: *const Imath_V3i_t, return_: *mut c_int) -> Exception;

pub fn Imath_2_5__Vec3_int__length2(this_: *const Imath_V3i_t, return_: *mut c_int) -> Exception;

pub fn Imath_2_5__Vec3_int__normalize(this_: *mut Imath_V3i_t, return_: *mut *const Imath_V3i_t) -> Exception;

pub fn Imath_2_5__Vec3_int__normalized(this_: *const Imath_V3i_t, return_: *mut Imath_V3i_t) -> Exception;


} // extern "C"
