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

#[derive(Debug, PartialEq, thiserror::Error)]
pub enum Error {
}

pub mod tftoken_c;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_t as pxr_TfToken_t;

pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_copy as pxr_TfToken_copy;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_assign as pxr_TfToken_assign;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_destruct as pxr_TfToken_destruct;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_from_string as pxr_TfToken_from_string;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_Hash as pxr_TfToken_Hash;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_size as pxr_TfToken_size;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_GetText as pxr_TfToken_GetText;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_data as pxr_TfToken_data;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken__eq as pxr_TfToken__eq;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken__ne as pxr_TfToken__ne;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_eq_string as pxr_TfToken_eq_string;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_neq_string as pxr_TfToken_neq_string;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_operator_ as pxr_TfToken_operator_;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_IsEmpty as pxr_TfToken_IsEmpty;
pub use tftoken_c::pxrInternal_v0_20__pxrReserved____TfToken_IsImmortal as pxr_TfToken_IsImmortal;


#[cfg(test)]
mod test;
