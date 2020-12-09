#[repr(C, align(8))]
pub struct cppmm_string_vector {
    unused: [u8; 24],
}

extern "C" {

    pub fn cppmm_string_vector_get(
        vec: *const cppmm_string_vector,
        index: i32,
    ) -> *const std::os::raw::c_char;
    pub fn cppmm_string_vector_size(vec: *const cppmm_string_vector) -> i32;

}
