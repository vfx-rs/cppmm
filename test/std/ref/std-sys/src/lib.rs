pub mod c_usestd;

pub use c_usestd::_takes_string as _takes_string_1;
pub use c_usestd::_takes_vector_string as _takes_vector_string_1;
pub mod std_string;
pub use std_string::std____cxx11__basic_string_char__t as std___cxx11_string_t;
pub use std_string::std__vector_std__string__t as std_vector_string_t;

pub use std_string::std____cxx11__basic_string_char__assign as std___cxx11_string_assign;
pub use std_string::std____cxx11__basic_string_char__c_str as std___cxx11_string_c_str;
pub use std_string::std__vector_std__string__vector as std_vector_string_vector;
pub use std_string::std__vector_std__string__dtor as std_vector_string_dtor;


#[cfg(test)]
mod test;
