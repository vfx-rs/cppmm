#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(property_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(property_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn property_get_exception_string() -> *const std::os::raw::c_char;
}

pub use prop::prop__Bar_t as prop_Bar_t;
pub use prop::prop__Foo_t as prop_Foo_t;

pub use prop::prop__Foo_bum as prop_Foo_bum;
pub use prop::prop__Foo_get_a as prop_Foo_get_a;
pub use prop::prop__Foo_set_a as prop_Foo_set_a;
pub use prop::prop__Foo_get_b as prop_Foo_get_b;
pub use prop::prop__Foo_set_b as prop_Foo_set_b;
pub use prop::prop__Foo_get_bar as prop_Foo_get_bar;
pub use prop::prop__Foo_set_bar as prop_Foo_set_bar;
pub use prop::prop__Foo_get_u as prop_Foo_get_u;
pub use prop::prop__Foo_set_u as prop_Foo_set_u;
pub use prop::prop_fuz as prop_fuz;
pub mod cppmmabi;
pub mod prop;


#[cfg(test)]
mod test;
