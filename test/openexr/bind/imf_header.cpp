#include <OpenEXR/ImfHeader.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct Header {
    using BoundType = Imf::Header;

    struct Iterator {
        using BoundType = Imf::Header::Iterator;
    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::Header::ConstIterator;
    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
