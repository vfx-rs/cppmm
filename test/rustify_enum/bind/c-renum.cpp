#include <renum.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace rustify {

enum Compression {
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
    NUM_COMPRESSION_METHODS
} CPPMM_ENUM_SUFFIX(_COMPRESSION) CPPMM_RUSTIFY_ENUM;

enum LineOrder {
    INCREASING_Y = 0,
    DECREASING_Y = 1,
    RANDOM_Y = 2,
    NUM_LINEORDERS,
} CPPMM_RUSTIFY_ENUM;

enum RgbaChannels {
    RGBA_CHANNELS_R,
    RGBA_CHANNELS_G,
    RGBA_CHANNELS_B,
    RGBA_CHANNELS_A,
    RGBA_CHANNELS_ALL,
} CPPMM_ENUM_PREFIX(RGBA_) CPPMM_RUSTIFY_ENUM;

} // namespace rustify
} // namespace cppmm_bind
