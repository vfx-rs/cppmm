#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }
            1 => {
                let s = unsafe { std::ffi::CStr::from_ptr(exceptions_get_exception_string()).to_string_lossy().to_string()};
                Err(Error::StdRuntimeError(s))
            }
            2 => {
                let s = unsafe { std::ffi::CStr::from_ptr(exceptions_get_exception_string()).to_string_lossy().to_string()};
                Err(Error::StdLogicError(s))
            }
            3 => {
                let s = unsafe { std::ffi::CStr::from_ptr(exceptions_get_exception_string()).to_string_lossy().to_string()};
                Err(Error::StdInvalidArgument(s))
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(exceptions_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(exceptions_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unexpected exception value: {} - {}", self.0, s)
            }
        }
    }
}

#[derive(Debug, PartialEq)]
pub enum Error {
    StdRuntimeError(String),
    StdLogicError(String),
    StdInvalidArgument(String),
}

impl std::error::Error for Error {
    fn source(&self) -> Option<&(dyn std::error::Error + 'static)> {
        None
    }
}

use std::fmt;
impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {

        match self {
                    Error::StdRuntimeError(s) => write!(f, "StdRuntimeError: {}", s),
                Error::StdLogicError(s) => write!(f, "StdLogicError: {}", s),
                Error::StdInvalidArgument(s) => write!(f, "StdInvalidArgument: {}", s),

        }
    }
}
extern {
    pub fn exceptions_get_exception_string() -> *const std::os::raw::c_char;
}

pub use c_ex::ex__Struct_t as ex_Struct_t;

pub use c_ex::ex__Struct_sizeof as ex_Struct_sizeof;
pub use c_ex::ex__Struct_alignof as ex_Struct_alignof;
pub use c_ex::ex__Struct_m1 as ex_Struct_m1;
pub use c_ex::ex__Struct_m2 as ex_Struct_m2;
pub use c_ex::ex__Struct_m3 as ex_Struct_m3;
pub use c_ex::ex__Struct_m4 as ex_Struct_m4;
pub use c_ex::ex_f1 as ex_f1;
pub use c_ex::ex_f2 as ex_f2;
pub mod cppmmabi;
pub mod c_ex;


#[cfg(test)]
mod test;
