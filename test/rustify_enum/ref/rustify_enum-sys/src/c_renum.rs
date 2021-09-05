#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(unused_imports)]
use crate::*;
pub use crate::cppmmabi::*;
use std::os::raw::*;

#[repr(C)]
pub struct rustify__Foo_t {
    _unused: [u8; 0],
}

#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct rustify__Foo__Bar_e(pub u32);
pub const rustify_Foo_Bar_Baz: rustify__Foo__Bar_e = rustify__Foo__Bar_e(0);
pub const rustify_Foo_Bar_Qux: rustify__Foo__Bar_e = rustify__Foo__Bar_e(1);

#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct rustify__Compression_e(pub u32);
pub const rustify_Compression_NO_COMPRESSION: rustify__Compression_e = rustify__Compression_e(0);
pub const rustify_Compression_RLE_COMPRESSION: rustify__Compression_e = rustify__Compression_e(1);
pub const rustify_Compression_ZIPS_COMPRESSION: rustify__Compression_e = rustify__Compression_e(2);
pub const rustify_Compression_ZIP_COMPRESSION: rustify__Compression_e = rustify__Compression_e(3);
pub const rustify_Compression_PIZ_COMPRESSION: rustify__Compression_e = rustify__Compression_e(4);
pub const rustify_Compression_PXR24_COMPRESSION: rustify__Compression_e = rustify__Compression_e(5);
pub const rustify_Compression_B44_COMPRESSION: rustify__Compression_e = rustify__Compression_e(6);
pub const rustify_Compression_B44A_COMPRESSION: rustify__Compression_e = rustify__Compression_e(7);
pub const rustify_Compression_DWAA_COMPRESSION: rustify__Compression_e = rustify__Compression_e(8);
pub const rustify_Compression_DWAB_COMPRESSION: rustify__Compression_e = rustify__Compression_e(9);
pub const rustify_Compression_NUM_COMPRESSION_METHODS: rustify__Compression_e = rustify__Compression_e(10);

#[repr(u32)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum Compression {
    No = 0,
    Rle = 1,
    Zips = 2,
    Zip = 3,
    Piz = 4,
    Pxr24 = 5,
    B44 = 6,
    B44a = 7,
    Dwaa = 8,
    Dwab = 9,
    NumCompressionMethods = 10,
}

impl From<rustify__Compression_e> for Compression {
    fn from(e: rustify__Compression_e) -> Compression {
        match e {
            rustify_Compression_NO_COMPRESSION => Compression::No,
            rustify_Compression_RLE_COMPRESSION => Compression::Rle,
            rustify_Compression_ZIPS_COMPRESSION => Compression::Zips,
            rustify_Compression_ZIP_COMPRESSION => Compression::Zip,
            rustify_Compression_PIZ_COMPRESSION => Compression::Piz,
            rustify_Compression_PXR24_COMPRESSION => Compression::Pxr24,
            rustify_Compression_B44_COMPRESSION => Compression::B44,
            rustify_Compression_B44A_COMPRESSION => Compression::B44a,
            rustify_Compression_DWAA_COMPRESSION => Compression::Dwaa,
            rustify_Compression_DWAB_COMPRESSION => Compression::Dwab,
            rustify_Compression_NUM_COMPRESSION_METHODS => Compression::NumCompressionMethods,
            _ => panic!("Invalid value {:?} for Compression in conversion", e),
        }
    }
}

impl From<Compression> for rustify__Compression_e {
    fn from(e: Compression) -> rustify__Compression_e {
        match e {
            Compression::No => rustify_Compression_NO_COMPRESSION,
            Compression::Rle => rustify_Compression_RLE_COMPRESSION,
            Compression::Zips => rustify_Compression_ZIPS_COMPRESSION,
            Compression::Zip => rustify_Compression_ZIP_COMPRESSION,
            Compression::Piz => rustify_Compression_PIZ_COMPRESSION,
            Compression::Pxr24 => rustify_Compression_PXR24_COMPRESSION,
            Compression::B44 => rustify_Compression_B44_COMPRESSION,
            Compression::B44a => rustify_Compression_B44A_COMPRESSION,
            Compression::Dwaa => rustify_Compression_DWAA_COMPRESSION,
            Compression::Dwab => rustify_Compression_DWAB_COMPRESSION,
            Compression::NumCompressionMethods => rustify_Compression_NUM_COMPRESSION_METHODS,
        }
    }
}

#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct rustify__LineOrder_e(pub u32);
pub const rustify_LineOrder_INCREASING_Y: rustify__LineOrder_e = rustify__LineOrder_e(0);
pub const rustify_LineOrder_DECREASING_Y: rustify__LineOrder_e = rustify__LineOrder_e(1);
pub const rustify_LineOrder_RANDOM_Y: rustify__LineOrder_e = rustify__LineOrder_e(2);
pub const rustify_LineOrder_NUM_LINEORDERS: rustify__LineOrder_e = rustify__LineOrder_e(3);

#[repr(u32)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum LineOrder {
    IncreasingY = 0,
    DecreasingY = 1,
    RandomY = 2,
    NumLineorders = 3,
}

impl From<rustify__LineOrder_e> for LineOrder {
    fn from(e: rustify__LineOrder_e) -> LineOrder {
        match e {
            rustify_LineOrder_INCREASING_Y => LineOrder::IncreasingY,
            rustify_LineOrder_DECREASING_Y => LineOrder::DecreasingY,
            rustify_LineOrder_RANDOM_Y => LineOrder::RandomY,
            rustify_LineOrder_NUM_LINEORDERS => LineOrder::NumLineorders,
            _ => panic!("Invalid value {:?} for LineOrder in conversion", e),
        }
    }
}

impl From<LineOrder> for rustify__LineOrder_e {
    fn from(e: LineOrder) -> rustify__LineOrder_e {
        match e {
            LineOrder::IncreasingY => rustify_LineOrder_INCREASING_Y,
            LineOrder::DecreasingY => rustify_LineOrder_DECREASING_Y,
            LineOrder::RandomY => rustify_LineOrder_RANDOM_Y,
            LineOrder::NumLineorders => rustify_LineOrder_NUM_LINEORDERS,
        }
    }
}

#[repr(transparent)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub struct rustify__RgbaChannels_e(pub u32);
pub const rustify_RgbaChannels_RGBA_CHANNELS_R: rustify__RgbaChannels_e = rustify__RgbaChannels_e(0);
pub const rustify_RgbaChannels_RGBA_CHANNELS_G: rustify__RgbaChannels_e = rustify__RgbaChannels_e(1);
pub const rustify_RgbaChannels_RGBA_CHANNELS_B: rustify__RgbaChannels_e = rustify__RgbaChannels_e(2);
pub const rustify_RgbaChannels_RGBA_CHANNELS_A: rustify__RgbaChannels_e = rustify__RgbaChannels_e(3);
pub const rustify_RgbaChannels_RGBA_CHANNELS_ALL: rustify__RgbaChannels_e = rustify__RgbaChannels_e(4);

#[repr(u32)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum RgbaChannels {
    ChannelsR = 0,
    ChannelsG = 1,
    ChannelsB = 2,
    ChannelsA = 3,
    ChannelsAll = 4,
}

impl From<rustify__RgbaChannels_e> for RgbaChannels {
    fn from(e: rustify__RgbaChannels_e) -> RgbaChannels {
        match e {
            rustify_RgbaChannels_RGBA_CHANNELS_R => RgbaChannels::ChannelsR,
            rustify_RgbaChannels_RGBA_CHANNELS_G => RgbaChannels::ChannelsG,
            rustify_RgbaChannels_RGBA_CHANNELS_B => RgbaChannels::ChannelsB,
            rustify_RgbaChannels_RGBA_CHANNELS_A => RgbaChannels::ChannelsA,
            rustify_RgbaChannels_RGBA_CHANNELS_ALL => RgbaChannels::ChannelsAll,
            _ => panic!("Invalid value {:?} for RgbaChannels in conversion", e),
        }
    }
}

impl From<RgbaChannels> for rustify__RgbaChannels_e {
    fn from(e: RgbaChannels) -> rustify__RgbaChannels_e {
        match e {
            RgbaChannels::ChannelsR => rustify_RgbaChannels_RGBA_CHANNELS_R,
            RgbaChannels::ChannelsG => rustify_RgbaChannels_RGBA_CHANNELS_G,
            RgbaChannels::ChannelsB => rustify_RgbaChannels_RGBA_CHANNELS_B,
            RgbaChannels::ChannelsA => rustify_RgbaChannels_RGBA_CHANNELS_A,
            RgbaChannels::ChannelsAll => rustify_RgbaChannels_RGBA_CHANNELS_ALL,
        }
    }
}


extern "C" {


} // extern "C"
