#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(std_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(std_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn std_get_exception_string() -> *const std::os::raw::c_char;
}

pub mod c_usestd;

pub use c_usestd::usestd_takes_string as usestd_takes_string;
pub use c_usestd::usestd_takes_vector_string as usestd_takes_vector_string;
pub mod std_string;
pub use std_string::std____cxx11__basic_string_char__t as std_string_t;
pub use std_string::std__vector_std__string__t as std_vector_string_t;

pub use std_string::std____cxx11__basic_string_char__assign as std_string_assign;
pub use std_string::std____cxx11__basic_string_char__c_str as std_string_c_str;
pub use std_string::std__vector_std__string__vector as std_vector_string_vector;
pub use std_string::std__vector_std__string__dtor as std_vector_string_dtor;


#[cfg(test)]
mod test;
