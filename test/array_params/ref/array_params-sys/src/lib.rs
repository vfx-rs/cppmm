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
pub mod c_array_params;
pub use c_array_params::imath__Matrix44_float__t as imath_M44f_t;

pub use c_array_params::imath__Matrix44_float__from_array as imath_M44f_from_array;


#[cfg(test)]
mod test;
