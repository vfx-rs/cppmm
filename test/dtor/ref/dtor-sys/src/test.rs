use crate::*;
use std::os::raw::c_void;

#[repr(transparent)]
pub struct Struct(pub dtor_Struct_t);

unsafe fn get_struct() -> Struct {
    let mut s = dtor_Struct_t::default();
    dtor_Struct_Struct(&mut s);
    Struct(s)
}

#[test]
fn it_works() {
    unsafe {
        let mut s = get_struct();
        dtor_Struct_dtor(&mut s.0);
    }
}
