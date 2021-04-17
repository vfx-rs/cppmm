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

        let sw_center = Imath_V2f_t {
            x: 0.0f32,
            y: 0.0f32,
        };
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
        let mut pixels = vec![
            Imf_Rgba_t {
                r: half_t::default(),
                g: half_t::default(),
                b: half_t::default(),
                a: half_t::default()
            };
            256 * 128
        ];

        // draw a pattern.
        for y in 0..height {
            for x in 0..width {
                let u = x as f32 / width as f32;
                let v = y as f32 / height as f32;

                let pix = &mut pixels[(y * width + x) as usize];
                half_from_float(&mut pix.r, u);
                half_from_float(&mut pix.g, v);
                half_from_float(&mut pix.b, 0.0f32);
                half_from_float(&mut pix.a, 1.0f32);
            }
        }

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
