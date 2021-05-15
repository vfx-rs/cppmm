#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(dtor_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(dtor_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unexpected exception value: {} - {}", self.0, s)
            }
        }
    }
}

#[derive(Debug, PartialEq)]
pub enum Error {
}

impl std::error::Error for Error {
    fn source(&self) -> Option<&(dyn std::error::Error + 'static)> {
        None
    }
}

use std::fmt;
impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {

        Ok(())
    }
}
extern {
    pub fn dtor_get_exception_string() -> *const std::os::raw::c_char;
}

pub mod c_dtor;
pub use c_dtor::dtor__Struct_t as dtor_Struct_t;

pub use c_dtor::dtor__Struct_Struct as dtor_Struct_Struct;
pub use c_dtor::dtor__Struct_dtor as dtor_Struct_dtor;
pub mod std_string;
pub use std_string::std____cxx11__basic_string_char__t as std___cxx11_string_t;

pub use std_string::std____cxx11__basic_string_char__sizeof as std___cxx11_string_sizeof;
pub use std_string::std____cxx11__basic_string_char__alignof as std___cxx11_string_alignof;
pub use std_string::std____cxx11__basic_string_char__ctor as std___cxx11_string_ctor;
pub use std_string::std____cxx11__basic_string_char__copy as std___cxx11_string_copy;
pub use std_string::std____cxx11__basic_string_char__dtor as std___cxx11_string_dtor;
pub use std_string::std____cxx11__basic_string_char__assign as std___cxx11_string_assign;
pub use std_string::std____cxx11__basic_string_char__c_str as std___cxx11_string_c_str;


#[cfg(test)]
mod test;
