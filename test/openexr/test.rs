use crate::*;

use std::ffi::CString;

#[test]
fn write_rgba1() {
    unsafe {
        let mut file = Imf_RgbaOutputFile_t::default();
        let filename = CString::new("write_rgba1.exr").unwrap();

        let width = 256i32;
        let height = 128i32;

        let channels = Imf_RgbaChannels_WRITE_RGBA;

        let par = 1.0f32;

        let sw_center = Imath_V2f_t::default();
        let sw_width = 1.0f32;

        let line_order = Imf_LineOrder_INCREASING_Y;
        let compression = Imf_Compression_PIZ_COMPRESSION;
        let num_threads = 1;

        Imf_RgbaOutputFile_with_dimensions(
            &mut file,
            filename.as_ptr(),
            width,
            height,
            channels,
            par,
            sw_center,
            sw_width,
            line_order,
            compression,
            num_threads,
        );

        // allocate pixel storage
        let pixels = vec![Imf_Rgba_t::default(); 256 * 128];

        Imf_RgbaOutputFile_setFrameBuffer(
            &mut file,
            pixels.as_ptr(),
            1,
            width as u64,
        );

        Imf_RgbaOutputFile_writePixels(&mut file, height);

        Imf_RgbaOutputFile_dtor(&mut file);
    }
}
