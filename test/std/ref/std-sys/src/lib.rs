#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(std_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(std_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn std_get_exception_string() -> *const std::os::raw::c_char;
}


pub use c_usestd::usestd_takes_string as usestd_takes_string;
pub use c_usestd::usestd_takes_vector_string as usestd_takes_vector_string;
pub use std_set::std___Rb_tree_node_base_t as std__Rb_tree_node_base_t;
pub use std_set::std__set_std__string__t as std_set_string_t;
pub use std_set::std___Rb_tree_const_iterator_std____cxx11__basic_string_char___t as std_set_string_iterator_t;

pub use std_set::std__set_std__string__sizeof as std_set_string_sizeof;
pub use std_set::std__set_std__string__alignof as std_set_string_alignof;
pub use std_set::std__set_std__string__ctor as std_set_string_ctor;
pub use std_set::std__set_std__string__dtor as std_set_string_dtor;
pub use std_set::std__set_std__string__cbegin as std_set_string_cbegin;
pub use std_set::std__set_std__string__cend as std_set_string_cend;
pub use std_set::std__set_std__string__size as std_set_string_size;
pub use std_set::std___Rb_tree_const_iterator_std____cxx11__basic_string_char___deref as std_set_string_iterator_deref;
pub use std_set::std___Rb_tree_const_iterator_std____cxx11__basic_string_char___inc as std_set_string_iterator_inc;
pub use std_set::std_set_string_const_iterator_eq as std_set_string_const_iterator_eq;
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
pub mod std_set;
pub mod std_string;
pub mod c_usestd;


#[cfg(test)]
mod test;
