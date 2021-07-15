#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(nested_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(nested_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn nested_get_exception_string() -> *const std::os::raw::c_char;
}

pub use a::neste::nest__NestAE_t as nest_NestAE_t;

pub use a::neste::nest__NestAE_do_something as nest_NestAE_do_something;
pub use b::neste::nest__NestBE_t as nest_NestBE_t;

pub use b::neste::nest__NestBE_do_something as nest_NestBE_do_something;
pub use c::d::neste::nest__NestCDE_t as nest_NestCDE_t;

pub use c::d::neste::nest__NestCDE_do_something as nest_NestCDE_do_something;
pub mod a;
pub mod b;
pub mod c;


#[cfg(test)]
mod test;
