#include <OpenEXR/ImfFramesPerSecond.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

IMF_EXPORT
int hufCompress(const unsigned short raw[/*nRaw*/], int nRaw,
                char compressed[/*2 * nRaw + 65536*/]);

IMF_EXPORT
void hufUncompress(const char compressed[/*nCompressed*/], int nCompressed,
                   unsigned short raw[/*nRaw*/], int nRaw);

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
