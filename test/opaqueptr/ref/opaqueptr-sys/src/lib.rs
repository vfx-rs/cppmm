#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(opaqueptr_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(opaqueptr_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn opaqueptr_get_exception_string() -> *const std::os::raw::c_char;
}

pub use c_optr::optr__PubCtor_t as optr_PubCtor_t;
pub use c_optr::optr__PrvCtor_t as optr_PrvCtor_t;
pub use c_optr::optr__AllPrv_t as optr_AllPrv_t;
pub use c_optr::optr__Opaque_t as optr_Opaque_t;

pub use c_optr::optr__PubCtor_ctor as optr_PubCtor_ctor;
pub use c_optr::optr__PubCtor_dtor as optr_PubCtor_dtor;
pub use c_optr::optr__PubCtor_doit as optr_PubCtor_doit;
pub use c_optr::optr__PrvCtor_doit as optr_PrvCtor_doit;
pub mod cppmmabi;
pub mod c_optr;


#[cfg(test)]
mod test;
