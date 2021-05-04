#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;

/// A test class to make sure we can
/// grab comments to be injected into C and Rust
#[repr(C)]
pub struct comments__Class_t {
    _unused: [u8; 0],
}


extern "C" {

/// This method doesn't do anything interesting at all
pub fn comments__Class_method(this_: *mut comments_Class_t) -> Exception;

/// This is a free function that also does nothing interesting
pub fn comments_function() -> Exception;


} // extern "C"
