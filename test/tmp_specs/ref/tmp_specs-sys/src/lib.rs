#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(tmp_specs_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(tmp_specs_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn tmp_specs_get_exception_string() -> *const std::os::raw::c_char;
}

pub use c_specs::specs__Attribute_int__t as specs_IntAttribute_t;
pub use c_specs::specs__Attribute_float__t as specs_FloatAttribute_t;
pub use c_specs::specs__Attribute_std__string__t as specs_StringAttribute_t;
pub use c_specs::specs__Specs_t as specs_Specs_t;

pub use c_specs::specs__Attribute_int__value as specs_IntAttribute_value;
pub use c_specs::specs__Attribute_int__do_something as specs_IntAttribute_do_something;
pub use c_specs::specs__Attribute_int__ctor as specs_IntAttribute_ctor;
pub use c_specs::specs__Attribute_float__value as specs_FloatAttribute_value;
pub use c_specs::specs__Attribute_float__do_something as specs_FloatAttribute_do_something;
pub use c_specs::specs__Attribute_float__ctor as specs_FloatAttribute_ctor;
pub use c_specs::specs__Attribute_std__string__value as specs_StringAttribute_value;
pub use c_specs::specs__Attribute_std__string__do_something as specs_StringAttribute_do_something;
pub use c_specs::specs__Attribute_std__string__ctor as specs_StringAttribute_ctor;
pub use c_specs::specs__Attribute_std__string__dtor as specs_StringAttribute_dtor;
pub use c_specs::specs__Specs_findAttribute_int as specs_Specs_findAttribute_int;
pub use c_specs::specs__Specs_findAttribute_float as specs_Specs_findAttribute_float;
pub use c_specs::specs__Specs_findAttribute_int_const as specs_Specs_findAttribute_int_const;
pub use c_specs::specs__Specs_findAttribute_float_const as specs_Specs_findAttribute_float_const;
pub use std_string::std____cxx11__basic_string_char__t as std_string_t;
pub use std_string::std__vector_std__string__t as std_vector_string_t;

pub use std_string::std____cxx11__basic_string_char__sizeof as std_string_sizeof;
pub use std_string::std____cxx11__basic_string_char__alignof as std_string_alignof;
pub use std_string::std____cxx11__basic_string_char__assign as std_string_assign;
pub use std_string::std____cxx11__basic_string_char__c_str as std_string_c_str;
pub use std_string::std__vector_std__string__sizeof as std_vector_string_sizeof;
pub use std_string::std__vector_std__string__alignof as std_vector_string_alignof;
pub use std_string::std__vector_std__string__ctor as std_vector_string_ctor;
pub use std_string::std__vector_std__string__dtor as std_vector_string_dtor;
pub mod cppmmabi;
pub mod std_string;
pub mod c_specs;


#[cfg(test)]
mod test;
