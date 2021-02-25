#include <OpenEXR/ImfFlatImageLevel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct FlatImageLevel {
    using BoundType = Imf::FlatImageLevel;

    // Inherited from ImageLevel
    Imf::Image& image();
    const Imf::Image& image() const CPPMM_RENAME(image_const);

    int xLevelNumber() const;
    int yLevelNumber() const;

    const IMATH_NAMESPACE::Box2i& dataWindow() const;

    IMFUTIL_EXPORT
    Imf::FlatImage& deepImage();
    IMFUTIL_EXPORT
    const Imf::FlatImage& deepImage() const CPPMM_RENAME(deepImage_const);

    IMFUTIL_EXPORT
    Imf::FlatImageChannel* findChannel(const std::string& name);
    IMFUTIL_EXPORT
    const Imf::FlatImageChannel* findChannel(const std::string& name) const
        CPPMM_RENAME(findChannel_const);

    IMFUTIL_EXPORT
    Imf::FlatImageChannel& channel(const std::string& name)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);
    IMFUTIL_EXPORT
    const Imf::FlatImageChannel& channel(const std::string& name) const
        CPPMM_RENAME(channel_const)
            CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    template <class T>
    Imf::TypedFlatImageChannel<T>* findTypedChannel(const std::string& name);

    template <class T>
    const Imf::TypedFlatImageChannel<T>*
    findTypedChannel(const std::string& name) const
        CPPMM_RENAME(findTypedChannel_const);

    template <class T>
    Imf::TypedFlatImageChannel<T>& typedChannel(const std::string& name)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    template <class T>
    const Imf::TypedFlatImageChannel<T>&
    typedChannel(const std::string& name) const CPPMM_RENAME(typedChannel_const)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    IMFUTIL_EXPORT
    Imf::FlatImageLevel::Iterator begin();
    IMFUTIL_EXPORT
    Imf::FlatImageLevel::ConstIterator begin() const CPPMM_RENAME(begin_const);

    IMFUTIL_EXPORT
    Imf::FlatImageLevel::Iterator end();
    IMFUTIL_EXPORT
    Imf::FlatImageLevel::ConstIterator end() const CPPMM_RENAME(end_const);

    struct Iterator {
        using BoundType = Imf::FlatImageLevel::Iterator;
        IMFUTIL_EXPORT
        Iterator();
        IMFUTIL_EXPORT
        Iterator(const Imf::FlatImageLevel::ChannelMap::iterator& i)
            CPPMM_IGNORE;

        IMFUTIL_EXPORT
        Imf::FlatImageLevel::Iterator& operator++() CPPMM_RENAME(inc);
        IMFUTIL_EXPORT
        Imf::FlatImageLevel::Iterator operator++(int) CPPMM_IGNORE;

        IMFUTIL_EXPORT
        const std::string& name() const;
        IMFUTIL_EXPORT
        Imf::FlatImageChannel& channel() const;

    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::FlatImageLevel::ConstIterator;

        IMFUTIL_EXPORT
        ConstIterator();
        IMFUTIL_EXPORT
        ConstIterator(const Imf::FlatImageLevel::ChannelMap::const_iterator& i)
            CPPMM_IGNORE;

        IMFUTIL_EXPORT
        Imf::FlatImageLevel::ConstIterator& operator++() CPPMM_RENAME(inc);
        IMFUTIL_EXPORT
        Imf::FlatImageLevel::ConstIterator operator++(int) CPPMM_IGNORE;

        IMFUTIL_EXPORT
        const std::string& name() const;
        IMFUTIL_EXPORT
        const Imf::FlatImageChannel& channel() const;

    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
