#include <OpenEXR/ImfDeepFrameBuffer.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepSlice {
    using BoundType = Imf::DeepSlice;
} CPPMM_VALUETYPE;

struct DeepFrameBuffer {
    using BoundType = Imf::DeepFrameBuffer;

    struct Iterator {
        using BoundType = Imf::DeepFrameBuffer::Iterator;
    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::DeepFrameBuffer::ConstIterator;
    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
