#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C, align(8))]
pub struct pxrInternal_v0_20__pxrReserved____TfToken_t {
    _inner: [u8; 8]
}



extern "C" {

pub fn pxrInternal_v0_20__pxrReserved____TfToken_copy(this_: *mut pxr_TfToken_t, rhs: *const pxr_TfToken_t);
pub fn pxrInternal_v0_20__pxrReserved____TfToken_assign(this_: *mut pxr_TfToken_t, rhs: *const pxr_TfToken_t) -> *mut pxr_TfToken_t;
pub fn pxrInternal_v0_20__pxrReserved____TfToken_destruct(this_: *mut pxr_TfToken_t);
pub fn pxrInternal_v0_20__pxrReserved____TfToken_from_string(this_: *mut pxr_TfToken_t, s: *const c_char);
pub fn pxrInternal_v0_20__pxrReserved____TfToken_Hash(this_: *const pxr_TfToken_t) -> c_ulong;
pub fn pxrInternal_v0_20__pxrReserved____TfToken_size(this_: *const pxr_TfToken_t) -> c_ulong;
pub fn pxrInternal_v0_20__pxrReserved____TfToken_GetText(this_: *const pxr_TfToken_t) -> *const c_char;
pub fn pxrInternal_v0_20__pxrReserved____TfToken_data(this_: *const pxr_TfToken_t) -> *const c_char;
pub fn pxrInternal_v0_20__pxrReserved____TfToken__eq(this_: *const pxr_TfToken_t, o: *const pxr_TfToken_t) -> bool;
pub fn pxrInternal_v0_20__pxrReserved____TfToken__ne(this_: *const pxr_TfToken_t, o: *const pxr_TfToken_t) -> bool;
pub fn pxrInternal_v0_20__pxrReserved____TfToken_eq_string(this_: *const pxr_TfToken_t, o: *const c_char) -> bool;
pub fn pxrInternal_v0_20__pxrReserved____TfToken_neq_string(this_: *const pxr_TfToken_t, o: *const c_char) -> bool;
pub fn pxrInternal_v0_20__pxrReserved____TfToken_operator_(this_: *const pxr_TfToken_t, r: *const pxr_TfToken_t) -> bool;
pub fn pxrInternal_v0_20__pxrReserved____TfToken_IsEmpty(this_: *const pxr_TfToken_t) -> bool;
pub fn pxrInternal_v0_20__pxrReserved____TfToken_IsImmortal(this_: *const pxr_TfToken_t) -> bool;

} // extern "C"
