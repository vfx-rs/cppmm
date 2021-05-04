use crate::*;

#[test]
fn it_works() {
    let mut s = ex_Struct_t::default();
    let f = 0.0f32;
    let mut r = 0.0f32;
    let i = 0i32;

    unsafe {
        assert_eq!(
            ex_Struct_m1(&mut s).into_result(),
            Err(Error::StdRuntimeError)
        );
        assert_eq!(
            "It's runtime, this is an error!",
            std::ffi::CStr::from_ptr(exceptions_get_exception_string())
                .to_str()
                .unwrap()
        );
        assert_eq!(
            ex_Struct_m2(&mut s, &mut r, -1.0f32).into_result(),
            Err(Error::StdRuntimeError)
        );
        assert_eq!(
            "It's runtime, this is an error!",
            std::ffi::CStr::from_ptr(exceptions_get_exception_string())
                .to_str()
                .unwrap()
        );
        assert_eq!(
            ex_Struct_m2(&mut s, &mut r, 1.0f32).into_result(),
            Err(Error::StdLogicError)
        );
        assert_eq!(
            "Your logic is bad. And you should feel bad",
            std::ffi::CStr::from_ptr(exceptions_get_exception_string())
                .to_str()
                .unwrap()
        );
    }
}
