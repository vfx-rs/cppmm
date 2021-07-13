#[repr(transparent)] 
pub struct Exception(u32);

impl Exception {
    pub fn into_result(self) -> Result<(), Error> {
        match self.0 {
            0 => {
                Ok(())
            }

            std::u32::MAX => {
                let s = unsafe { std::ffi::CStr::from_ptr(rustify_enum_get_exception_string()).to_string_lossy().to_string()};
                panic!("Unhandled exception: {}", s)
            }
            _ => {
                let s = unsafe { std::ffi::CStr::from_ptr(rustify_enum_get_exception_string()).to_string_lossy().to_string()};
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
    pub fn rustify_enum_get_exception_string() -> *const std::os::raw::c_char;
}


pub use c_renum::rustify__Compression_e as rustify_Compression;
pub use c_renum::rustify_Compression_NO_COMPRESSION;
pub use c_renum::rustify_Compression_RLE_COMPRESSION;
pub use c_renum::rustify_Compression_ZIPS_COMPRESSION;
pub use c_renum::rustify_Compression_ZIP_COMPRESSION;
pub use c_renum::rustify_Compression_PIZ_COMPRESSION;
pub use c_renum::rustify_Compression_PXR24_COMPRESSION;
pub use c_renum::rustify_Compression_B44_COMPRESSION;
pub use c_renum::rustify_Compression_B44A_COMPRESSION;
pub use c_renum::rustify_Compression_DWAA_COMPRESSION;
pub use c_renum::rustify_Compression_DWAB_COMPRESSION;
pub use c_renum::rustify_Compression_NUM_COMPRESSION_METHODS;
pub use c_renum::Compression;
pub use c_renum::rustify__LineOrder_e as rustify_LineOrder;
pub use c_renum::rustify_LineOrder_INCREASING_Y;
pub use c_renum::rustify_LineOrder_DECREASING_Y;
pub use c_renum::rustify_LineOrder_RANDOM_Y;
pub use c_renum::rustify_LineOrder_NUM_LINEORDERS;
pub use c_renum::LineOrder;
pub use c_renum::rustify__RgbaChannels_e as rustify_RgbaChannels;
pub use c_renum::rustify_RgbaChannels_RGBA_CHANNELS_R;
pub use c_renum::rustify_RgbaChannels_RGBA_CHANNELS_G;
pub use c_renum::rustify_RgbaChannels_RGBA_CHANNELS_B;
pub use c_renum::rustify_RgbaChannels_RGBA_CHANNELS_A;
pub use c_renum::rustify_RgbaChannels_RGBA_CHANNELS_ALL;
pub use c_renum::RgbaChannels;
pub mod c_renum;


#[cfg(test)]
mod test;
