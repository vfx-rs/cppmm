use crate::*;

#[test]
fn it_works() {
    let s = std::ffi::CString::new("this_is_a_test_string").unwrap();
    unsafe {
        let mut std_str = std_string::new();
        std_string_from_cstr(&mut std_str, s.as_ptr());

        // Check that the contents of the std_string is correct
        assert_eq!(
            std::ffi::CStr::from_ptr(std_string_c_str(&std_str)),
            s.as_c_str()
        );

        let t = test_Test_Test(&std_str);

        // Check that the Test class also contains a valid copy of the value
        assert_eq!(
            std::ffi::CStr::from_ptr(std_string_c_str(test_Test_get_value(t))),
            s.as_c_str()
        );
    }
}
