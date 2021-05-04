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
            ex_Struct_m2(&mut s, &mut r, -1.0f32).into_result(),
            Err(Error::StdRuntimeError)
        );
        assert_eq!(
            ex_Struct_m2(&mut s, &mut r, 1.0f32).into_result(),
            Err(Error::StdLogicError)
        );
    }
}
