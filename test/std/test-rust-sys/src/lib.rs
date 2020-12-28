#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

mod std_string_bind;
pub use std_string_bind::*;

#[cfg(test)]
mod test;

pub mod cppmm_containers;
use cppmm_containers::*;
pub mod test_bind;
use test_bind::*;

pub use test_bind::test_Test;
pub use test_bind::test_Test_Test;
pub use test_bind::test_Test_clone_value;
pub use test_bind::test_Test_edit_value;
pub use test_bind::test_Test_get_value;
pub use test_bind::test_Test_set_value;
