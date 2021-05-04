use crate::c_renum::*;

#[test]
fn it_works() {
    let e = rustify__Compression_e(4);
    assert_eq!(Compression::from(e), Compression::Piz);
}
