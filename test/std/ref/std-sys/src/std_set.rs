#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;

#[repr(C)]
pub struct std___Rb_tree_node_base_t {
    _unused: [u8; 0],
}

impl std__set_std__string__t {
    pub fn layout() -> std::alloc::Layout {
        unsafe {
            std::alloc::Layout::from_size_align(
                std__set_std__string__sizeof(),
                std__set_std__string__alignof(),
            ).unwrap()
        }
    }
}

#[repr(C, align(8))]
#[derive(Clone)]
pub struct std__set_std__string___const_iterator_t {
    pub _m_node: *const std__Rb_tree_node_base_t,
}



extern "C" {

pub fn std__set_std__string__sizeof() -> usize;

pub fn std__set_std__string__alignof() -> usize;

pub fn std__set_std__string__ctor(this_: *mut std_set_string_t) -> Exception;

pub fn std__set_std__string__dtor(this_: *mut std_set_string_t) -> Exception;

pub fn std__set_std__string__cbegin(this_: *const std_set_string_t, return_: *mut std_set_string_iterator_t) -> Exception;

pub fn std__set_std__string__cend(this_: *const std_set_string_t, return_: *mut std_set_string_iterator_t) -> Exception;

pub fn std__set_std__string__size(this_: *const std_set_string_t, return_: *mut usize) -> Exception;

pub fn std__set_std__string___const_iterator_deref(this_: *const std_set_string_iterator_t, return_: *mut *const std_string_t) -> Exception;

pub fn std__set_std__string___const_iterator_inc(this_: *mut std_set_string_iterator_t, return_: *mut *mut std_set_string_iterator_t) -> Exception;

pub fn std_set_string_const_iterator_eq(return_: *mut bool, __x: *const std_set_string_iterator_t, __y: *const std_set_string_iterator_t) -> Exception;


} // extern "C"
