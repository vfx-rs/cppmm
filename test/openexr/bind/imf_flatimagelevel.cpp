#include <OpenEXR/ImfFlatImageLevel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct FlatImageLevel {
    using BoundType = Imf::FlatImageLevel;

    struct Iterator {
        using BoundType = Imf::FlatImageLevel::Iterator;
    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::FlatImageLevel::ConstIterator;
    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
