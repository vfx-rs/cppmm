#include <OpenEXR/ImfRgbaFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct RgbaOutputFile {
    using BoundType = Imf::RgbaOutputFile;

} CPPMM_OPAQUEBYTES;

struct RgbaInputFile {
    using BoundType = Imf::RgbaInputFile;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
