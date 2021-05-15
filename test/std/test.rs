use crate::*;

#[test]
fn it_works() {
    let lay = std_string_t::layout();
    assert_eq!(lay.size(), std::mem::size_of::<std_string_t>());
    assert_eq!(lay.align(), std::mem::align_of::<std_string_t>());

    let lay = std_vector_string_t::layout();
    assert_eq!(lay.size(), std::mem::size_of::<std_vector_string_t>());
    assert_eq!(lay.align(), std::mem::align_of::<std_vector_string_t>());
}
