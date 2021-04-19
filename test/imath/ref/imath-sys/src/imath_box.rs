#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(4))]
#[derive(Clone)]
pub struct Imath_2_5__Box_Imath__Vec3_float___t {
    pub min: Imath_V3f_t,
    pub max: Imath_V3f_t,
}

#[repr(C, align(4))]
#[derive(Clone)]
pub struct Imath_2_5__Box_Imath__Vec3_int___t {
    pub min: Imath_V3i_t,
    pub max: Imath_V3i_t,
}



extern "C" {

pub fn Imath_2_5__Box_Imath__Vec3_float___extendBy(this_: *mut Imath_Box3f_t, point: *const Imath_V3f_t) -> c_void;
pub fn Imath_2_5__Box_Imath__Vec3_float___extendBy_1(this_: *mut Imath_Box3f_t, box_: *const Imath_Box3f_t) -> c_void;
pub fn Imath_2_5__Box_Imath__Vec3_int___extendBy(this_: *mut Imath_Box3i_t, point: *const Imath_V3i_t) -> c_void;
pub fn Imath_2_5__Box_Imath__Vec3_int___extendBy_1(this_: *mut Imath_Box3i_t, box_: *const Imath_Box3i_t) -> c_void;

} // extern "C"
