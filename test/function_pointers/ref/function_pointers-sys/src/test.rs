use crate::*;
use std::os::raw::c_void;

struct CallbackData {
    pub pc: Vec<f32>,
}

extern "C" fn callback(data: *mut c_void, pc: f32) -> bool {
    unsafe {
        (*(data as *mut CallbackData)).pc.push(pc);
    }
    true
}

#[test]
fn it_works() {
    let mut cb = Box::new(CallbackData { pc: Vec::new() });
    unsafe {
        fptr_takes_ages(
            callback,
            (&mut *cb) as *mut CallbackData as *mut c_void,
        );
    }
    assert_eq!(
        cb.pc,
        [0.0f32, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    );
}
