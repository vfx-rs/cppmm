use crate::*;
use std::ffi::CStr;

#[test]
fn it_works() {
    unsafe {
        let mut vec = containers_Containers_returns_vec_string();
        containers_Containers_takes_mut_vec_string_ref(&mut vec);
        containers_Containers_takes_const_vec_string_ref(&vec);
        for i in 0..cppmm_string_vector_size(&vec) {
            println!("  {}", CStr::from_ptr(cppmm_string_vector_get(&vec, i)).to_string_lossy().into_owned());
        }
    }
}
