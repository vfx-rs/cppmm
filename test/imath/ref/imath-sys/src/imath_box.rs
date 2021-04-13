#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(4))]
#[derive(Clone)]
pub struct Imath_2_5__Box_Imath__Vec3_float___t {
    _inner: [u8; 24]
}

impl Default for Imath_2_5__Box_Imath__Vec3_float___t {
    fn default() -> Self {
        Self { _inner: [0u8; 24] }
    }
}

#[repr(C, align(4))]
#[derive(Clone)]
pub struct Imath_2_5__Box_Imath__Vec3_int___t {
    _inner: [u8; 24]
}

impl Default for Imath_2_5__Box_Imath__Vec3_int___t {
    fn default() -> Self {
        Self { _inner: [0u8; 24] }
    }
}



extern "C" {

pub fn Imath_2_5__Box_Imath__Vec3_float___extendBy(this_: *mut Imath_Box3f_t, point: *const Imath_V3f_t);
pub fn Imath_2_5__Box_Imath__Vec3_float___extendBy_1(this_: *mut Imath_Box3f_t, box_: *const Imath_Box3f_t);
pub fn Imath_2_5__Box_Imath__Vec3_int___extendBy(this_: *mut Imath_Box3i_t, box_: *const Imath_Box3i_t);

} // extern "C"
