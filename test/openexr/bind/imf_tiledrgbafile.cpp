#include <OpenEXR/ImfTiledRgbaFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct TiledRgbaOutputFile {
    using BoundType = Imf::TiledRgbaOutputFile;

} CPPMM_OPAQUEBYTES;

struct TiledRgbaInputFile {
    using BoundType = Imf::TiledRgbaInputFile;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
