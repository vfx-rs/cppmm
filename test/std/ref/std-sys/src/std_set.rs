#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

#[repr(C)]
pub struct std___Rb_tree_node_base_t {
    _unused: [u8; 0],
}
#[repr(C, align(8))]
#[derive(Clone)]
pub struct std__set_std__string__t {
    _inner: [u8; 48]
}

impl Default for std__set_std__string__t {
    fn default() -> Self {
        Self { _inner: [0u8; 48] }
    }
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
pub struct std___Rb_tree_const_iterator_std____cxx11__basic_string_char___t {
    pub _m_node: *const std__Rb_tree_node_base_t,
}



extern "C" {

pub fn std__set_std__string__sizeof() -> usize;

pub fn std__set_std__string__alignof() -> usize;

pub fn std__set_std__string__ctor(this_: *mut std_set_string_t) -> Exception;

pub fn std__set_std__string__dtor(this_: *mut std_set_string_t) -> Exception;

pub fn std__set_std__string__cbegin(this_: *const std_set_string_t, return_: *mut std_set_string_iterator_t) -> Exception;

pub fn std__set_std__string__cend(this_: *const std_set_string_t, return_: *mut std_set_string_iterator_t) -> Exception;

pub fn std__set_std__string__size(this_: *const std_set_string_t, return_: *mut c_ulong) -> Exception;

pub fn std___Rb_tree_const_iterator_std____cxx11__basic_string_char___deref(this_: *const std_set_string_iterator_t, return_: *mut *const std_string_t) -> Exception;

pub fn std___Rb_tree_const_iterator_std____cxx11__basic_string_char___inc(this_: *mut std_set_string_iterator_t, return_: *mut *mut std_set_string_iterator_t) -> Exception;

pub fn std_set_string_const_iterator_eq(return_: *mut bool, __x: *const std_set_string_iterator_t, __y: *const std_set_string_iterator_t) -> Exception;


} // extern "C"
