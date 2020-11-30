use crate::*;

use std::ffi::{CString, CStr};

#[test]
fn it_works() {
    let mut tok = pxr_TfToken::new();

    let s = CString::new("Hello, world!").unwrap();

    unsafe {
        pxr_TfToken_from_string(&mut tok, s.as_ptr());
        let ptr = pxr_TfToken_GetText(&tok);
        let s2 = CStr::from_ptr(ptr).to_string_lossy().into_owned();
        assert_eq!(s2, "Hello, world!");
    }
}
