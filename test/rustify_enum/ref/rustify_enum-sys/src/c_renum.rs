#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
use std::os::raw::*;


#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub(crate) struct rustify__Compression_e(pub(crate) u32);
pub(crate) const rustify_Compression_NO_COMPRESSION: rustify__Compression_e = rustify__Compression_e(0);
pub(crate) const rustify_Compression_RLE_COMPRESSION: rustify__Compression_e = rustify__Compression_e(1);
pub(crate) const rustify_Compression_ZIPS_COMPRESSION: rustify__Compression_e = rustify__Compression_e(2);
pub(crate) const rustify_Compression_ZIP_COMPRESSION: rustify__Compression_e = rustify__Compression_e(3);
pub(crate) const rustify_Compression_PIZ_COMPRESSION: rustify__Compression_e = rustify__Compression_e(4);
pub(crate) const rustify_Compression_PXR24_COMPRESSION: rustify__Compression_e = rustify__Compression_e(5);
pub(crate) const rustify_Compression_B44_COMPRESSION: rustify__Compression_e = rustify__Compression_e(6);
pub(crate) const rustify_Compression_B44A_COMPRESSION: rustify__Compression_e = rustify__Compression_e(7);
pub(crate) const rustify_Compression_DWAA_COMPRESSION: rustify__Compression_e = rustify__Compression_e(8);
pub(crate) const rustify_Compression_DWAB_COMPRESSION: rustify__Compression_e = rustify__Compression_e(9);
pub(crate) const rustify_Compression_NUM_COMPRESSION_METHODS: rustify__Compression_e = rustify__Compression_e(10);

#[repr(u32)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum Compression {
    NO_COMPRESSION = 0,
    RLE_COMPRESSION = 1,
    ZIPS_COMPRESSION = 2,
    ZIP_COMPRESSION = 3,
    PIZ_COMPRESSION = 4,
    PXR24_COMPRESSION = 5,
    B44_COMPRESSION = 6,
    B44A_COMPRESSION = 7,
    DWAA_COMPRESSION = 8,
    DWAB_COMPRESSION = 9,
    NUM_COMPRESSION_METHODS = 10,
}

impl From<rustify__Compression_e> for Compression {
    fn from(e: rustify__Compression_e) -> Compression {
        match e {
            rustify_Compression_NO_COMPRESSION => Compression::NO_COMPRESSION,
            rustify_Compression_RLE_COMPRESSION => Compression::RLE_COMPRESSION,
            rustify_Compression_ZIPS_COMPRESSION => Compression::ZIPS_COMPRESSION,
            rustify_Compression_ZIP_COMPRESSION => Compression::ZIP_COMPRESSION,
            rustify_Compression_PIZ_COMPRESSION => Compression::PIZ_COMPRESSION,
            rustify_Compression_PXR24_COMPRESSION => Compression::PXR24_COMPRESSION,
            rustify_Compression_B44_COMPRESSION => Compression::B44_COMPRESSION,
            rustify_Compression_B44A_COMPRESSION => Compression::B44A_COMPRESSION,
            rustify_Compression_DWAA_COMPRESSION => Compression::DWAA_COMPRESSION,
            rustify_Compression_DWAB_COMPRESSION => Compression::DWAB_COMPRESSION,
            rustify_Compression_NUM_COMPRESSION_METHODS => Compression::NUM_COMPRESSION_METHODS,
            _ => panic!("Invalid value {:?} for Compression in conversion", e),
        }
    }
}

impl From<Compression> for rustify__Compression_e {
    fn from(e: Compression) -> rustify__Compression_e {
        match e {
            Compression::NO_COMPRESSION => rustify_Compression_NO_COMPRESSION,
            Compression::RLE_COMPRESSION => rustify_Compression_RLE_COMPRESSION,
            Compression::ZIPS_COMPRESSION => rustify_Compression_ZIPS_COMPRESSION,
            Compression::ZIP_COMPRESSION => rustify_Compression_ZIP_COMPRESSION,
            Compression::PIZ_COMPRESSION => rustify_Compression_PIZ_COMPRESSION,
            Compression::PXR24_COMPRESSION => rustify_Compression_PXR24_COMPRESSION,
            Compression::B44_COMPRESSION => rustify_Compression_B44_COMPRESSION,
            Compression::B44A_COMPRESSION => rustify_Compression_B44A_COMPRESSION,
            Compression::DWAA_COMPRESSION => rustify_Compression_DWAA_COMPRESSION,
            Compression::DWAB_COMPRESSION => rustify_Compression_DWAB_COMPRESSION,
            Compression::NUM_COMPRESSION_METHODS => rustify_Compression_NUM_COMPRESSION_METHODS,
        }
    }
}

#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub(crate) struct rustify__LineOrder_e(pub(crate) u32);
pub(crate) const rustify_LineOrder_INCREASING_Y: rustify__LineOrder_e = rustify__LineOrder_e(0);
pub(crate) const rustify_LineOrder_DECREASING_Y: rustify__LineOrder_e = rustify__LineOrder_e(1);
pub(crate) const rustify_LineOrder_RANDOM_Y: rustify__LineOrder_e = rustify__LineOrder_e(2);
pub(crate) const rustify_LineOrder_NUM_LINEORDERS: rustify__LineOrder_e = rustify__LineOrder_e(3);

#[repr(u32)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum LineOrder {
    INCREASING_Y = 0,
    DECREASING_Y = 1,
    RANDOM_Y = 2,
    NUM_LINEORDERS = 3,
}

impl From<rustify__LineOrder_e> for LineOrder {
    fn from(e: rustify__LineOrder_e) -> LineOrder {
        match e {
            rustify_LineOrder_INCREASING_Y => LineOrder::INCREASING_Y,
            rustify_LineOrder_DECREASING_Y => LineOrder::DECREASING_Y,
            rustify_LineOrder_RANDOM_Y => LineOrder::RANDOM_Y,
            rustify_LineOrder_NUM_LINEORDERS => LineOrder::NUM_LINEORDERS,
            _ => panic!("Invalid value {:?} for LineOrder in conversion", e),
        }
    }
}

impl From<LineOrder> for rustify__LineOrder_e {
    fn from(e: LineOrder) -> rustify__LineOrder_e {
        match e {
            LineOrder::INCREASING_Y => rustify_LineOrder_INCREASING_Y,
            LineOrder::DECREASING_Y => rustify_LineOrder_DECREASING_Y,
            LineOrder::RANDOM_Y => rustify_LineOrder_RANDOM_Y,
            LineOrder::NUM_LINEORDERS => rustify_LineOrder_NUM_LINEORDERS,
        }
    }
}

#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub(crate) struct rustify__RgbaChannels_e(pub(crate) u32);
pub(crate) const rustify_RgbaChannels_RGBA_CHANNELS_R: rustify__RgbaChannels_e = rustify__RgbaChannels_e(0);
pub(crate) const rustify_RgbaChannels_RGBA_CHANNELS_G: rustify__RgbaChannels_e = rustify__RgbaChannels_e(1);
pub(crate) const rustify_RgbaChannels_RGBA_CHANNELS_B: rustify__RgbaChannels_e = rustify__RgbaChannels_e(2);
pub(crate) const rustify_RgbaChannels_RGBA_CHANNELS_A: rustify__RgbaChannels_e = rustify__RgbaChannels_e(3);
pub(crate) const rustify_RgbaChannels_RGBA_CHANNELS_ALL: rustify__RgbaChannels_e = rustify__RgbaChannels_e(4);

#[repr(u32)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum RgbaChannels {
    RGBA_CHANNELS_R = 0,
    RGBA_CHANNELS_G = 1,
    RGBA_CHANNELS_B = 2,
    RGBA_CHANNELS_A = 3,
    RGBA_CHANNELS_ALL = 4,
}

impl From<rustify__RgbaChannels_e> for RgbaChannels {
    fn from(e: rustify__RgbaChannels_e) -> RgbaChannels {
        match e {
            rustify_RgbaChannels_RGBA_CHANNELS_R => RgbaChannels::RGBA_CHANNELS_R,
            rustify_RgbaChannels_RGBA_CHANNELS_G => RgbaChannels::RGBA_CHANNELS_G,
            rustify_RgbaChannels_RGBA_CHANNELS_B => RgbaChannels::RGBA_CHANNELS_B,
            rustify_RgbaChannels_RGBA_CHANNELS_A => RgbaChannels::RGBA_CHANNELS_A,
            rustify_RgbaChannels_RGBA_CHANNELS_ALL => RgbaChannels::RGBA_CHANNELS_ALL,
            _ => panic!("Invalid value {:?} for RgbaChannels in conversion", e),
        }
    }
}

impl From<RgbaChannels> for rustify__RgbaChannels_e {
    fn from(e: RgbaChannels) -> rustify__RgbaChannels_e {
        match e {
            RgbaChannels::RGBA_CHANNELS_R => rustify_RgbaChannels_RGBA_CHANNELS_R,
            RgbaChannels::RGBA_CHANNELS_G => rustify_RgbaChannels_RGBA_CHANNELS_G,
            RgbaChannels::RGBA_CHANNELS_B => rustify_RgbaChannels_RGBA_CHANNELS_B,
            RgbaChannels::RGBA_CHANNELS_A => rustify_RgbaChannels_RGBA_CHANNELS_A,
            RgbaChannels::RGBA_CHANNELS_ALL => rustify_RgbaChannels_RGBA_CHANNELS_ALL,
        }
    }
}


extern "C" {


} // extern "C"
