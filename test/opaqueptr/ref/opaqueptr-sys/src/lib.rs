#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                panic!("Unhandled exception")
            }
            _ => {
                panic!("Unexpected exception value")
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

pub mod c_optr;
pub use c_optr::optr__PubCtor_t as optr_PubCtor_t;
pub use c_optr::optr__PrvCtor_t as optr_PrvCtor_t;
pub use c_optr::optr__AllPrv_t as optr_AllPrv_t;
pub use c_optr::optr__Opaque_t as optr_Opaque_t;

pub use c_optr::optr__PubCtor_ctor as optr_PubCtor_ctor;
pub use c_optr::optr__PubCtor_dtor as optr_PubCtor_dtor;
pub use c_optr::optr__PubCtor_doit as optr_PubCtor_doit;
pub use c_optr::optr__PrvCtor_doit as optr_PrvCtor_doit;


#[cfg(test)]
mod test;
