#include <OpenEXR/ImfVersion.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

//
const int MAGIC = 20000630;
const int VERSION_NUMBER_FIELD = 0x000000ff;
const int VERSION_FLAGS_FIELD = 0xffffff00;
const int EXR_VERSION = 2;
const int TILED_FLAG = 0x00000200; // File is tiled

const int LONG_NAMES_FLAG = 0x00000400; // File contains long
                                        // attribute or channel
                                        // names

const int NON_IMAGE_FLAG = 0x00000800; // File has at least one part
                                       // which is not a regular
                                       // scanline image or regular tiled image
                                       // (that is, it is a deep format)

const int MULTI_PART_FILE_FLAG = 0x00001000; // File has multiple parts
const int ALL_FLAGS =
    TILED_FLAG | LONG_NAMES_FLAG | NON_IMAGE_FLAG | MULTI_PART_FILE_FLAG;
inline bool isTiled(int version);
inline bool isMultiPart(int version);
inline bool isNonImage(int version);
inline int makeTiled(int version);
inline int makeNotTiled(int version);
inline int getVersion(int version);
inline int getFlags(int version);
inline bool supportsFlags(int flags);
IMF_EXPORT
bool isImfMagic(const char bytes[4]);

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
