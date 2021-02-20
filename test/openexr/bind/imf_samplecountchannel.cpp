#include <OpenEXR/ImfSampleCountChannel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct SampleCountChannel {
    using BoundType = Imf::SampleCountChannel;

    struct Edit {
        using BoundType = Imf::SampleCountChannel::Edit;
    } CPPMM_OPAQUEBYTES;

} CPPMM_VALUETYPE;

enum RgbaChannels {};

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
