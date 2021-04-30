pub mod c_dtor;
pub use c_dtor::dtor__Struct_t as dtor_Struct_t;

pub use c_dtor::dtor__Struct_Struct as dtor_Struct_Struct;
pub use c_dtor::dtor__Struct_dtor as dtor_Struct_dtor;
pub mod std_string;
pub use std_string::std____cxx11__basic_string_char__t as std___cxx11_string_t;

pub use std_string::std____cxx11__basic_string_char__ctor as std___cxx11_string_ctor;
pub use std_string::std____cxx11__basic_string_char__copy as std___cxx11_string_copy;
pub use std_string::std____cxx11__basic_string_char__dtor as std___cxx11_string_dtor;
pub use std_string::std____cxx11__basic_string_char__assign as std___cxx11_string_assign;
pub use std_string::std____cxx11__basic_string_char__c_str as std___cxx11_string_c_str;


#[cfg(test)]
mod test;
