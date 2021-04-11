#include <OpenEXR/ImfChannelList.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

class Channel {
public:
    using BoundType = Imf::Channel;

    IMF_EXPORT
    Channel(Imf::PixelType type, int xSampling, int ySampling, bool pLinear);

    IMF_EXPORT
    Channel(const Imf::Channel& rhs);

    IMF_EXPORT
    bool operator==(const Imf::Channel& other) const;
} CPPMM_VALUETYPE;

class ChannelList {
public:
    using BoundType = Imf::ChannelList;

    ChannelList(const Imf::ChannelList& rhs);

    IMF_EXPORT
    void insert(const char name[], const Imf::Channel& channel);

    IMF_EXPORT
    void insert(const std::string& name,
                const Imf::Channel& channel) CPPMM_IGNORE;

    IMF_EXPORT
    Imf::Channel& operator[](const char name[]) CPPMM_RENAME(index);
    IMF_EXPORT
    const Imf::Channel& operator[](const char name[]) const
        CPPMM_RENAME(index_const);

    IMF_EXPORT
    Imf::Channel& operator[](const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    const Imf::Channel& operator[](const std::string& name) const CPPMM_IGNORE;

    IMF_EXPORT
    Imf::Channel* findChannel(const char name[]);
    IMF_EXPORT
    const Imf::Channel* findChannel(const char name[]) const
        CPPMM_RENAME(findChannel_const);

    IMF_EXPORT
    Imf::Channel* findChannel(const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    const Imf::Channel* findChannel(const std::string& name) const CPPMM_IGNORE;

    IMF_EXPORT
    Imf::ChannelList::Iterator begin();
    IMF_EXPORT
    Imf::ChannelList::ConstIterator begin() const CPPMM_RENAME(begin_const);

    IMF_EXPORT
    Imf::ChannelList::Iterator end();
    IMF_EXPORT
    Imf::ChannelList::ConstIterator end() const CPPMM_RENAME(end_const);

    IMF_EXPORT
    Imf::ChannelList::Iterator find(const char name[]);
    IMF_EXPORT
    Imf::ChannelList::ConstIterator find(const char name[]) const
        CPPMM_RENAME(find_const);

    IMF_EXPORT
    Imf::ChannelList::Iterator find(const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    Imf::ChannelList::ConstIterator
    find(const std::string& name) const CPPMM_IGNORE;

    IMF_EXPORT
    void layers(std::set<std::string>& layerNames) const;

    IMF_EXPORT
    void channelsInLayer(const std::string& layerName,
                         Imf::ChannelList::Iterator& first,
                         Imf::ChannelList::Iterator& last);

    IMF_EXPORT
    void channelsInLayer(const std::string& layerName,
                         Imf::ChannelList::ConstIterator& first,
                         Imf::ChannelList::ConstIterator& last) const
        CPPMM_RENAME(channelsInLayer_const);

    IMF_EXPORT
    void channelsWithPrefix(const char prefix[],
                            Imf::ChannelList::Iterator& first,
                            Imf::ChannelList::Iterator& last);

    IMF_EXPORT
    void channelsWithPrefix(const char prefix[],
                            Imf::ChannelList::ConstIterator& first,
                            Imf::ChannelList::ConstIterator& last) const
        CPPMM_RENAME(channelsWithPrefix_const);

    IMF_EXPORT
    bool operator==(const ChannelList& other) const;

    class Iterator {
    public:
        using BoundType = Imf::ChannelList::Iterator;
        IMF_EXPORT
        Iterator();
        IMF_EXPORT
        Iterator(const Imf::ChannelList::ChannelMap::iterator& i) CPPMM_IGNORE;
        IMF_EXPORT
        Iterator(const Imf::ChannelList::Iterator& rhs);

        IMF_EXPORT
        Iterator& operator++();
        IMF_EXPORT
        Iterator operator++(int) CPPMM_IGNORE;

        IMF_EXPORT
        const char* name() const;
        IMF_EXPORT
        Imf::Channel& channel() const;

    } CPPMM_OPAQUEBYTES;

    class ConstIterator {
    public:
        using BoundType = Imf::ChannelList::ConstIterator;

        IMF_EXPORT
        ConstIterator();
        IMF_EXPORT
        ConstIterator(const Imf::ChannelList::ChannelMap::const_iterator& i)
            CPPMM_IGNORE;
        IMF_EXPORT
        ConstIterator(const Imf::ChannelList::ConstIterator& rhs);

        IMF_EXPORT
        ConstIterator& operator++();
        IMF_EXPORT
        ConstIterator operator++(int) CPPMM_IGNORE;

        IMF_EXPORT
        const char* name() const;
        IMF_EXPORT
        Imf::Channel& channel() const;

    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
