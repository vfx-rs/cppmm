#include <OpenEXR/ImfFrameBuffer.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct Slice {
    using BoundType = Imf::Slice;
} CPPMM_VALUETYPE;

struct FrameBuffer {
    using BoundType = Imf::FrameBuffer;

    struct Iterator {
        using BoundType = Imf::FrameBuffer::Iterator;
    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::FrameBuffer::ConstIterator;
    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
