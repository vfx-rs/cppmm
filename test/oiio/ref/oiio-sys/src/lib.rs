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

pub mod std_vector;
pub use std_vector::std__vector_std__string__t as std_vector_string_t;

pub use std_vector::std__vector_std__string__vector as std_vector_string_vector;
pub use std_vector::std__vector_std__string__dtor as std_vector_string_dtor;
pub mod c_filesystem;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_t as OIIO_Filesystem_IOProxy_t;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_t as OIIO_Filesystem_IOMemReader_t;

pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy__Mode_e as OIIO_Filesystem_IOProxy_Mode;
pub use c_filesystem::OIIO_Filesystem_IOProxy_Mode_Closed;
pub use c_filesystem::OIIO_Filesystem_IOProxy_Mode_Read;
pub use c_filesystem::OIIO_Filesystem_IOProxy_Mode_Write;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_delete as OIIO_Filesystem_IOProxy_delete;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_proxytype as OIIO_Filesystem_IOProxy_proxytype;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_close as OIIO_Filesystem_IOProxy_close;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_opened as OIIO_Filesystem_IOProxy_opened;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_tell as OIIO_Filesystem_IOProxy_tell;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_seek as OIIO_Filesystem_IOProxy_seek;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_read as OIIO_Filesystem_IOProxy_read;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_write as OIIO_Filesystem_IOProxy_write;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_pread as OIIO_Filesystem_IOProxy_pread;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_pwrite as OIIO_Filesystem_IOProxy_pwrite;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_filename as OIIO_Filesystem_IOProxy_filename;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOProxy_seek_1 as OIIO_Filesystem_IOProxy_seek_1;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_proxytype as OIIO_Filesystem_IOMemReader_proxytype;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_close as OIIO_Filesystem_IOMemReader_close;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_opened as OIIO_Filesystem_IOMemReader_opened;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_tell as OIIO_Filesystem_IOMemReader_tell;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_seek as OIIO_Filesystem_IOMemReader_seek;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_read as OIIO_Filesystem_IOMemReader_read;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_write as OIIO_Filesystem_IOMemReader_write;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_pread as OIIO_Filesystem_IOMemReader_pread;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_pwrite as OIIO_Filesystem_IOMemReader_pwrite;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_seek_1 as OIIO_Filesystem_IOMemReader_seek_1;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_new as OIIO_Filesystem_IOMemReader_new;
pub use c_filesystem::OpenImageIO_v2_2__Filesystem__IOMemReader_delete as OIIO_Filesystem_IOMemReader_delete;
pub use c_filesystem::OpenImageIO_v2_2_Filesystem_filename as OIIO_Filesystem_filename;
pub use c_filesystem::OpenImageIO_v2_2_Filesystem_extension as OIIO_Filesystem_extension;
pub use c_filesystem::OpenImageIO_v2_2_Filesystem_parent_path as OIIO_Filesystem_parent_path;
pub use c_filesystem::OpenImageIO_v2_2_Filesystem_replace_extension as OIIO_Filesystem_replace_extension;
pub mod c_typedesc;
pub use c_typedesc::OpenImageIO_v2_2__TypeDesc_t as OIIO_TypeDesc_t;

pub use c_typedesc::OpenImageIO_v2_2__TypeDesc__BASETYPE_e as OIIO_TypeDesc_BASETYPE;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_UNKNOWN;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_NONE;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_UINT8;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_UCHAR;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_CHAR;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_INT8;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_USHORT;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_UINT16;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_INT16;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_SHORT;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_UINT;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_UINT32;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_INT32;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_INT;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_ULONGLONG;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_UINT64;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_INT64;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_LONGLONG;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_HALF;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_FLOAT;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_DOUBLE;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_STRING;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_PTR;
pub use c_typedesc::OIIO_TypeDesc_BASETYPE_LASTBASE;
pub use c_typedesc::OpenImageIO_v2_2__TypeDesc__AGGREGATE_e as OIIO_TypeDesc_AGGREGATE;
pub use c_typedesc::OIIO_TypeDesc_AGGREGATE_SCALAR;
pub use c_typedesc::OIIO_TypeDesc_AGGREGATE_VEC2;
pub use c_typedesc::OIIO_TypeDesc_AGGREGATE_VEC3;
pub use c_typedesc::OIIO_TypeDesc_AGGREGATE_VEC4;
pub use c_typedesc::OIIO_TypeDesc_AGGREGATE_MATRIX33;
pub use c_typedesc::OIIO_TypeDesc_AGGREGATE_MATRIX44;
pub use c_typedesc::OpenImageIO_v2_2__TypeDesc__VECSEMANTICS_e as OIIO_TypeDesc_VECSEMANTICS;
pub use c_typedesc::OIIO_TypeDesc_VECSEMANTICS_NOSEMANTICS;
pub use c_typedesc::OIIO_TypeDesc_VECSEMANTICS_NOXFORM;
pub use c_typedesc::OIIO_TypeDesc_VECSEMANTICS_COLOR;
pub use c_typedesc::OIIO_TypeDesc_VECSEMANTICS_POINT;
pub use c_typedesc::OIIO_TypeDesc_VECSEMANTICS_VECTOR;
pub use c_typedesc::OIIO_TypeDesc_VECSEMANTICS_NORMAL;
pub use c_typedesc::OIIO_TypeDesc_VECSEMANTICS_TIMECODE;
pub use c_typedesc::OIIO_TypeDesc_VECSEMANTICS_KEYCODE;
pub use c_typedesc::OIIO_TypeDesc_VECSEMANTICS_RATIONAL;
pub mod c_imageio;
pub use c_imageio::OpenImageIO_v2_2__ROI_t as OIIO_ROI_t;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_t as OIIO_ImageSpec_t;
pub use c_imageio::OpenImageIO_v2_2__ImageInput_t as OIIO_ImageInput_t;

pub use c_imageio::OpenImageIO_v2_2__ImageSpec__SerialFormat_e as OIIO_ImageSpec_SerialFormat;
pub use c_imageio::OIIO_ImageSpec_SerialFormat_SerialText;
pub use c_imageio::OIIO_ImageSpec_SerialFormat_SerialXML;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec__SerialVerbose_e as OIIO_ImageSpec_SerialVerbose;
pub use c_imageio::OIIO_ImageSpec_SerialVerbose_SerialBrief;
pub use c_imageio::OIIO_ImageSpec_SerialVerbose_SerialDetailed;
pub use c_imageio::OIIO_ImageSpec_SerialVerbose_SerialDetailedHuman;
pub use c_imageio::OpenImageIO_v2_2__ROI_default as OIIO_ROI_default;
pub use c_imageio::OpenImageIO_v2_2__ROI_defined as OIIO_ROI_defined;
pub use c_imageio::OpenImageIO_v2_2__ROI_width as OIIO_ROI_width;
pub use c_imageio::OpenImageIO_v2_2__ROI_height as OIIO_ROI_height;
pub use c_imageio::OpenImageIO_v2_2__ROI_depth as OIIO_ROI_depth;
pub use c_imageio::OpenImageIO_v2_2__ROI_nchannels as OIIO_ROI_nchannels;
pub use c_imageio::OpenImageIO_v2_2__ROI_npixels as OIIO_ROI_npixels;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_ImageSpec as OIIO_ImageSpec_ImageSpec;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_new_with_dimensions as OIIO_ImageSpec_new_with_dimensions;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_set_format as OIIO_ImageSpec_set_format;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_default_channel_names as OIIO_ImageSpec_default_channel_names;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_channel_bytes as OIIO_ImageSpec_channel_bytes;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_channel_bytes_for as OIIO_ImageSpec_channel_bytes_for;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_scanline_bytes as OIIO_ImageSpec_scanline_bytes;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_serialize as OIIO_ImageSpec_serialize;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_copy as OIIO_ImageSpec_copy;
pub use c_imageio::OpenImageIO_v2_2__ImageSpec_assign as OIIO_ImageSpec_assign;
pub use c_imageio::OpenImageIO_v2_2__ImageInput_format_name as OIIO_ImageInput_format_name;
pub use c_imageio::OpenImageIO_v2_2__ImageInput_geterror as OIIO_ImageInput_geterror;
pub use c_imageio::OpenImageIO_v2_2_roi_union as OIIO_roi_union;
pub use c_imageio::OpenImageIO_v2_2_roi_intersection as OIIO_roi_intersection;
pub mod std_string;
pub use std_string::std____cxx11__basic_string_char__t as std___cxx11_string_t;

pub use std_string::std____cxx11__basic_string_char__basic_string as std___cxx11_string_basic_string;
pub use std_string::std____cxx11__basic_string_char__basic_string_1 as std___cxx11_string_basic_string_1;
pub use std_string::std____cxx11__basic_string_char__assign as std___cxx11_string_assign;
pub use std_string::std____cxx11__basic_string_char__c_str as std___cxx11_string_c_str;


#[cfg(test)]
mod test;
