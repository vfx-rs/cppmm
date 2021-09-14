#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(mimpl_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(mimpl_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn mimpl_get_exception_string() -> *const std::os::raw::c_char;
}

pub use mimpl::mimpl__Number_t as mimpl_Number_t;

pub use mimpl::mimpl__Number_ctor as mimpl_Number_ctor;
pub use mimpl::mimpl__Number_get_number as mimpl_Number_get_number;
pub use mimpl::Number_do_get_number as Number_do_get_number;
pub mod mimpl;
pub mod cppmmabi;


#[cfg(test)]
mod test;
