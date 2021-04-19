#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

/// A test class to make sure we can
/// grab comments to be injected into C and Rust
#[repr(C, align(1))]
#[derive(Clone)]
pub struct comments__Class_t {
    _inner: [u8; 1]
}

impl Default for comments__Class_t {
    fn default() -> Self {
        Self { _inner: [0u8; 1] }
    }
}



extern "C" {

/// This method doesn't do anything interesting at all
pub fn comments__Class_method(this_: *mut comments_Class_t) -> c_void;

/// This is a free function that also does nothing interesting
pub fn comments_function() -> c_void;


} // extern "C"
