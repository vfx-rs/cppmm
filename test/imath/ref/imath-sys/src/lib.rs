#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(imath_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(imath_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn imath_get_exception_string() -> *const std::os::raw::c_char;
}

pub use imath_vec::Imath_2_5__Vec3_float__t as Imath_V3f_t;
pub use imath_vec::Imath_2_5__Vec3_int__t as Imath_V3i_t;

pub use imath_vec::Imath_2_5__Vec3_float__ctor as Imath_V3f_ctor;
pub use imath_vec::Imath_2_5__Vec3_float__ctor_1 as Imath_V3f_ctor_1;
pub use imath_vec::Imath_2_5__Vec3_float__setValue as Imath_V3f_setValue;
pub use imath_vec::Imath_2_5__Vec3_float__dot as Imath_V3f_dot;
pub use imath_vec::Imath_2_5__Vec3_float__cross as Imath_V3f_cross;
pub use imath_vec::Imath_2_5__Vec3_float__op_iadd as Imath_V3f_op_iadd;
pub use imath_vec::Imath_2_5__Vec3_float__length as Imath_V3f_length;
pub use imath_vec::Imath_2_5__Vec3_float__length2 as Imath_V3f_length2;
pub use imath_vec::Imath_2_5__Vec3_float__normalize as Imath_V3f_normalize;
pub use imath_vec::Imath_2_5__Vec3_float__normalized as Imath_V3f_normalized;
pub use imath_vec::Imath_2_5__Vec3_int__ctor as Imath_V3i_ctor;
pub use imath_vec::Imath_2_5__Vec3_int__ctor_1 as Imath_V3i_ctor_1;
pub use imath_vec::Imath_2_5__Vec3_int__dot as Imath_V3i_dot;
pub use imath_vec::Imath_2_5__Vec3_int__cross as Imath_V3i_cross;
pub use imath_vec::Imath_2_5__Vec3_int__op_iadd as Imath_V3i_op_iadd;
pub use imath_vec::Imath_2_5__Vec3_int__length as Imath_V3i_length;
pub use imath_vec::Imath_2_5__Vec3_int__length2 as Imath_V3i_length2;
pub use imath_vec::Imath_2_5__Vec3_int__normalize as Imath_V3i_normalize;
pub use imath_vec::Imath_2_5__Vec3_int__normalized as Imath_V3i_normalized;
pub use imath_box::Imath_2_5__Box_Imath__Vec3_float___t as Imath_Box3f_t;
pub use imath_box::Imath_2_5__Box_Imath__Vec3_int___t as Imath_Box3i_t;

pub use imath_box::Imath_2_5__Box_Imath__Vec3_float___extendBy as Imath_Box3f_extendBy;
pub use imath_box::Imath_2_5__Box_Imath__Vec3_float___extendBy_1 as Imath_Box3f_extendBy_1;
pub use imath_box::Imath_2_5__Box_Imath__Vec3_int___extendBy as Imath_Box3i_extendBy;
pub use imath_box::Imath_2_5__Box_Imath__Vec3_int___extendBy_1 as Imath_Box3i_extendBy_1;
pub mod imath_box;
pub mod cppmmabi;
pub mod imath_vec;


#[cfg(test)]
mod test;
