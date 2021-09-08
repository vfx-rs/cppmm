#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(deep_namespace_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(deep_namespace_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn deep_namespace_get_exception_string() -> *const std::os::raw::c_char;
}

pub use c_dn::DN__v2_2__Class_t as DN_Class_t;
pub use c_dn::DN__v2_2__Class__Struct_t as DN_Class_Struct_t;

pub use c_dn::DN__v2_2__Class__Enum_e as DN_Class_Enum;
pub use c_dn::DN_Class_Enum_One;
pub use c_dn::DN_Class_Enum_Two;
pub use c_dn::DN_Class_Enum_Three;
pub use c_dn::DN__v2_2__Class__Struct_structMethod as DN_Class_Struct_structMethod;
pub use c_dn::DN_v2_2_someFunction as DN_someFunction;
pub mod cppmmabi;
pub mod c_dn;


#[cfg(test)]
mod test;
