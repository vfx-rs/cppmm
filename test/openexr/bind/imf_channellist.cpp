#include <OpenEXR/ImfChannelList.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

class Channel {
public:
    using BoundType = Imf::Channel;
} CPPMM_VALUETYPE;

class ChannelList {
public:
    using BoundType = Imf::ChannelList;

    class Iterator {
    public:
        using BoundType = Imf::ChannelList::Iterator;
    } CPPMM_OPAQUEPTR;

    class ConstIterator {
    public:
        using BoundType = Imf::ChannelList::ConstIterator;
    } CPPMM_OPAQUEPTR;

} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
