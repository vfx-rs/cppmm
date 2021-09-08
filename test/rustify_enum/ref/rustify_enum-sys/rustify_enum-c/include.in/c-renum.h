#pragma once
#include "rustify_enum-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

enum rustify__Foo__Bar_e {
    rustify_Foo_Bar_Baz = 0,
    rustify_Foo_Bar_Qux = 1,
};
typedef unsigned int rustify_Foo_Bar;
enum rustify__Compression_e {
    rustify_Compression_NO_COMPRESSION = 0,
    rustify_Compression_RLE_COMPRESSION = 1,
    rustify_Compression_ZIPS_COMPRESSION = 2,
    rustify_Compression_ZIP_COMPRESSION = 3,
    rustify_Compression_PIZ_COMPRESSION = 4,
    rustify_Compression_PXR24_COMPRESSION = 5,
    rustify_Compression_B44_COMPRESSION = 6,
    rustify_Compression_B44A_COMPRESSION = 7,
    rustify_Compression_DWAA_COMPRESSION = 8,
    rustify_Compression_DWAB_COMPRESSION = 9,
    rustify_Compression_NUM_COMPRESSION_METHODS = 10,
};
typedef unsigned int rustify_Compression;
enum rustify__LineOrder_e {
    rustify_LineOrder_INCREASING_Y = 0,
    rustify_LineOrder_DECREASING_Y = 1,
    rustify_LineOrder_RANDOM_Y = 2,
    rustify_LineOrder_NUM_LINEORDERS = 3,
};
typedef unsigned int rustify_LineOrder;
enum rustify__RgbaChannels_e {
    rustify_RgbaChannels_RGBA_CHANNELS_R = 0,
    rustify_RgbaChannels_RGBA_CHANNELS_G = 1,
    rustify_RgbaChannels_RGBA_CHANNELS_B = 2,
    rustify_RgbaChannels_RGBA_CHANNELS_A = 3,
    rustify_RgbaChannels_RGBA_CHANNELS_ALL = 4,
};
typedef unsigned int rustify_RgbaChannels;

typedef struct rustify__Foo_t_s {
    char _unused;
} RUSTIFY_ENUM_CPPMM_ALIGN(1) rustify__Foo_t;
typedef rustify__Foo_t rustify_Foo_t;


#ifdef __cplusplus
}
#endif
