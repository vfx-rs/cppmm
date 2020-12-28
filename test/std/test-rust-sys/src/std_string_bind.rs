#[repr(C, align(8))]
pub struct std_string {
    pub(self) _unused: [u8; 24],
} // TODO: Figure out what we want to do to allow users to create one of these

impl std_string {
    pub fn new() -> std_string {
        std_string { _unused: [0u8; 24] }
    }
}

extern "C" {

    pub fn std_string_ctor(_self: *mut std_string) -> std::os::raw::c_void;
    pub fn std_string_from_cstr(
        _self: *mut std_string,
        _str: *const std::os::raw::c_char,
    ) -> std::os::raw::c_void;

    pub fn std_string_dtor(_self: *mut std_string) -> std::os::raw::c_void;

    pub fn std_string_size(_self: *const std_string) -> i32;

    pub fn std_string_c_str(_self: *const std_string) -> *const std::os::raw::c_char;
}
