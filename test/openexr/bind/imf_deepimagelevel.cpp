#include <OpenEXR/ImfDeepImageLevel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepImageLevel {
    using BoundType = Imf::DeepImageLevel;

    struct Iterator {
        using BoundType = Imf::DeepImageLevel::Iterator;
    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::DeepImageLevel::ConstIterator;
    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
