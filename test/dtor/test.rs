use crate::*;
use std::os::raw::c_void;

#[repr(transparent)]
pub struct Struct(pub *mut dtor_Struct_t);

unsafe fn get_struct() -> Struct {
    let mut ptr = std::ptr::null_mut();
    dtor_Struct_ctor(&mut ptr);
    Struct(ptr)
}

#[test]
fn it_works() {
    unsafe {
        let mut s = get_struct();
        dtor_Struct_dtor(s.0);
    }
}
