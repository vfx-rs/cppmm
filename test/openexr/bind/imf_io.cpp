#include <OpenEXR/ImfIO.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct OStream {
    using BoundType = Imf::OStream;

} CPPMM_OPAQUEPTR;

struct IStream {
    using BoundType = Imf::IStream;

} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
