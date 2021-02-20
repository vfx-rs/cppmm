#include <OpenEXR/ImfAcesFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

class AcesOutputFile {
public:
    using BoundType = Imf::AcesOutputFile;
} CPPMM_OPAQUEPTR;

class AcesInputFile {
public:
    using BoundType = Imf::AcesInputFile;
} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
