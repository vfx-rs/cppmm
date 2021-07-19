#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(uniqueptr_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(uniqueptr_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn uniqueptr_get_exception_string() -> *const std::os::raw::c_char;
}

pub use foo::foo__Foo_t as foo_Foo_t;

pub use foo::foo__Foo_ctor as foo_Foo_ctor;
pub use foo::foo__Foo_dtor as foo_Foo_dtor;
pub use foo::foo__Foo_create as foo_Foo_create;
pub use uptr::std__unique_ptr_foo__Foo__t as std_FooPtr_t;

pub use uptr::std__unique_ptr_foo__Foo__ctor as std_FooPtr_ctor;
pub use uptr::std__unique_ptr_foo__Foo__dtor as std_FooPtr_dtor;
pub use uptr::std__unique_ptr_foo__Foo__get as std_FooPtr_get;
pub mod uptr;
pub mod foo;


#[cfg(test)]
mod test;
