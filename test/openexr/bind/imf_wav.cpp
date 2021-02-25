#include <OpenEXR/ImfWav.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

IMF_EXPORT
void wav2Encode(
    unsigned short* in, // io: values in[y][x] are transformed in place
    int nx,             // i : x size
    int ox,             // i : x offset
    int ny,             // i : y size
    int oy,             // i : y offset
    unsigned short mx); // i : maximum in[x][y] value

IMF_EXPORT
void wav2Decode(
    unsigned short* in, // io: values in[y][x] are transformed in place
    int nx,             // i : x size
    int ox,             // i : x offset
    int ny,             // i : y size
    int oy,             // i : y offset
    unsigned short mx); // i : maximum in[x][y] value

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
