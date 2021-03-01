#include <OpenEXR/ImfDeepImageLevel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepImageLevel {
    using BoundType = Imf::DeepImageLevel;

    // Inherited from ImageLevel
    Imf::Image& image();
    const Imf::Image& image() const CPPMM_RENAME(image_const);

    int xLevelNumber() const;
    int yLevelNumber() const;

    const IMATH_NAMESPACE::Box2i& dataWindow() const;

    IMFUTIL_EXPORT
    Imf::DeepImage& deepImage();
    IMFUTIL_EXPORT
    const Imf::DeepImage& deepImage() const CPPMM_RENAME(deepImage_const);

    IMFUTIL_EXPORT
    Imf::DeepImageChannel* findChannel(const std::string& name);
    IMFUTIL_EXPORT
    const Imf::DeepImageChannel* findChannel(const std::string& name) const
        CPPMM_RENAME(findChannel_const);

    IMFUTIL_EXPORT
    Imf::DeepImageChannel& channel(const std::string& name)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);
    IMFUTIL_EXPORT
    const Imf::DeepImageChannel& channel(const std::string& name) const
        CPPMM_RENAME(channel_const)
            CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    template <class T>
    Imf::TypedDeepImageChannel<T>* findTypedChannel(const std::string& name);

    template <class T>
    const Imf::TypedDeepImageChannel<T>*
    findTypedChannel(const std::string& name) const
        CPPMM_RENAME(findTypedChannel_const);

    template <class T>
    Imf::TypedDeepImageChannel<T>& typedChannel(const std::string& name)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    template <class T>
    const Imf::TypedDeepImageChannel<T>&
    typedChannel(const std::string& name) const CPPMM_RENAME(typedChannel_const)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    IMFUTIL_EXPORT
    Imf::DeepImageLevel::Iterator begin();
    IMFUTIL_EXPORT
    Imf::DeepImageLevel::ConstIterator begin() const CPPMM_RENAME(begin_const);

    IMFUTIL_EXPORT
    Imf::DeepImageLevel::Iterator end();
    IMFUTIL_EXPORT
    Imf::DeepImageLevel::ConstIterator end() const CPPMM_RENAME(end_const);

    IMFUTIL_EXPORT
    Imf::SampleCountChannel& sampleCounts();
    IMFUTIL_EXPORT
    const Imf::SampleCountChannel& sampleCounts() const
        CPPMM_RENAME(sampleCounts_const);

    struct Iterator {
        using BoundType = Imf::DeepImageLevel::Iterator;
        IMFUTIL_EXPORT
        Iterator();
        IMFUTIL_EXPORT
        Iterator(const Imf::DeepImageLevel::ChannelMap::iterator& i)
            CPPMM_IGNORE;
        IMF_EXPORT
        Iterator(const Iterator& rhs);

        IMFUTIL_EXPORT
        Imf::DeepImageLevel::Iterator& operator++() CPPMM_RENAME(inc);
        IMFUTIL_EXPORT
        Imf::DeepImageLevel::Iterator operator++(int) CPPMM_IGNORE;

        IMFUTIL_EXPORT
        const std::string& name() const;
        IMFUTIL_EXPORT
        Imf::DeepImageChannel& channel() const;

    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::DeepImageLevel::ConstIterator;

        IMFUTIL_EXPORT
        ConstIterator();
        IMFUTIL_EXPORT
        ConstIterator(const Imf::DeepImageLevel::ChannelMap::const_iterator& i)
            CPPMM_IGNORE;
        IMF_EXPORT
        ConstIterator(const ConstIterator& rhs);

        IMFUTIL_EXPORT
        Imf::DeepImageLevel::ConstIterator& operator++() CPPMM_RENAME(inc);
        IMFUTIL_EXPORT
        Imf::DeepImageLevel::ConstIterator operator++(int) CPPMM_IGNORE;

        IMFUTIL_EXPORT
        const std::string& name() const;
        IMFUTIL_EXPORT
        const Imf::DeepImageChannel& channel() const;

    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
