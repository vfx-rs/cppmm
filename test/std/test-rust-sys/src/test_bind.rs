use crate::*;

#[repr(C)]
pub struct test_Test_t {
    _unused: [u8; 0],
}
pub type test_Test = *mut test_Test_t;
extern "C" {

    pub fn test_Test_edit_value(_self: *mut test_Test) -> *mut std_string;

    pub fn test_Test_get_value(_self: *const test_Test) -> *const std_string;

    pub fn test_Test_set_value(
        _self: *mut test_Test,
        value: *const std_string,
    ) -> std::os::raw::c_void;

    pub fn test_Test_clone_value(_self: *const test_Test) -> std_string;

    pub fn test_Test_Test(value: *const std_string) -> *mut test_Test;
}
