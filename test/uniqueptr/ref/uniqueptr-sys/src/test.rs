use crate::*;

#[test]
fn it_works() {
    let mut p = std::ptr::null_mut();
    unsafe {
        std_FooPtr_ctor(&mut p, std::ptr::null_mut());

        foo_Foo_create(&mut p);

        std_FooPtr_dtor(p);
    }
}
