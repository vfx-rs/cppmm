#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }
            1 => {
                Err(Error::StdRuntimeError)
            }
            2 => {
                Err(Error::StdLogicError)
            }
            3 => {
                Err(Error::StdInvalidArgument)
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
    StdRuntimeError,
    StdLogicError,
    StdInvalidArgument,
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
                    Error::StdRuntimeError => write!(f, "StdRuntimeError"),
                Error::StdLogicError => write!(f, "StdLogicError"),
                Error::StdInvalidArgument => write!(f, "StdInvalidArgument"),

        }
    }
}
pub mod c_ex;
pub use c_ex::ex__Struct_t as ex_Struct_t;

pub use c_ex::ex__Struct_m1 as ex_Struct_m1;
pub use c_ex::ex__Struct_m2 as ex_Struct_m2;
pub use c_ex::ex_f1 as ex_f1;
pub use c_ex::ex_f2 as ex_f2;


#[cfg(test)]
mod test;
