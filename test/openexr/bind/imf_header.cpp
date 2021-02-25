#include <OpenEXR/ImfHeader.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct Header {
    using BoundType = Imf::Header;

    IMF_EXPORT
    Header(int width, int height, float pixelAspectRatio,
           const IMATH_NAMESPACE::V2f& screenWindowCenter,
           float screenWindowWidth, Imf::LineOrder lineOrder,
           Imf::Compression) CPPMM_IGNORE;

    IMF_EXPORT
    Header(int width, int height, const IMATH_NAMESPACE::Box2i& dataWindow,
           float pixelAspectRatio,
           const IMATH_NAMESPACE::V2f& screenWindowCenter,
           float screenWindowWidth, Imf::LineOrder lineOrder,
           Imf::Compression) CPPMM_IGNORE;

    IMF_EXPORT
    Header(const IMATH_NAMESPACE::Box2i& displayWindow,
           const IMATH_NAMESPACE::Box2i& dataWindow, float pixelAspectRatio,
           const IMATH_NAMESPACE::V2f& screenWindowCenter,
           float screenWindowWidth, Imf::LineOrder lineOrder, Imf::Compression);

    IMF_EXPORT
    Header(const Header& other);

    IMF_EXPORT
    ~Header();

    IMF_EXPORT
    Header& operator=(const Header& other);

    IMF_EXPORT
    void insert(const char name[], const Imf::Attribute& attribute);

    IMF_EXPORT
    void insert(const std::string& name,
                const Imf::Attribute& attribute) CPPMM_IGNORE;

    IMF_EXPORT
    void erase(const char name[]);
    IMF_EXPORT
    void erase(const std::string& name) CPPMM_IGNORE;

    IMF_EXPORT
    Imf::Attribute& operator[](const char name[]) CPPMM_RENAME(index)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);
    IMF_EXPORT
    const Imf::Attribute& operator[](const char name[]) const
        CPPMM_RENAME(index_const)
            CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    IMF_EXPORT
    Imf::Attribute& operator[](const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    const Imf::Attribute&
    operator[](const std::string& name) const CPPMM_IGNORE;

    template <class T>
    T& typedAttribute(const char name[])
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);
    template <class T>
    const T& typedAttribute(const char name[]) const
        CPPMM_RENAME(typedAttribute_const)
            CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    template <class T> T& typedAttribute(const std::string& name) CPPMM_IGNORE;
    template <class T>
    const T& typedAttribute(const std::string& name) const CPPMM_IGNORE;

    template <class T>
    T* findTypedAttribute(const char name[])
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);
    template <class T>
    const T* findTypedAttribute(const char name[]) const
        CPPMM_RENAME(findTypedAttribute_const)
            CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    template <class T>
    T* findTypedAttribute(const std::string& name) CPPMM_IGNORE;
    template <class T>
    const T* findTypedAttribute(const std::string& name) const CPPMM_IGNORE;

    IMF_EXPORT
    Imf::Header::Iterator begin();
    IMF_EXPORT
    Imf::Header::ConstIterator begin() const CPPMM_RENAME(begin_const);

    IMF_EXPORT
    Imf::Header::Iterator end();
    IMF_EXPORT
    Imf::Header::ConstIterator end() const CPPMM_RENAME(end_const);

    IMF_EXPORT
    Imf::Header::Iterator find(const char name[]);
    IMF_EXPORT
    Imf::Header::ConstIterator find(const char name[]) const
        CPPMM_RENAME(find_const);

    IMF_EXPORT
    Imf::Header::Iterator find(const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    Imf::Header::ConstIterator find(const std::string& name) const CPPMM_IGNORE;

    IMF_EXPORT
    IMATH_NAMESPACE::Box2i& displayWindow();
    IMF_EXPORT
    const IMATH_NAMESPACE::Box2i& displayWindow() const
        CPPMM_RENAME(displayWindow_const);

    IMF_EXPORT
    IMATH_NAMESPACE::Box2i& dataWindow();
    IMF_EXPORT
    const IMATH_NAMESPACE::Box2i& dataWindow() const
        CPPMM_RENAME(dataWindow_const);

    IMF_EXPORT
    float& pixelAspectRatio();
    IMF_EXPORT
    const float& pixelAspectRatio() const CPPMM_RENAME(pixelAspectRatio_const);

    IMF_EXPORT
    IMATH_NAMESPACE::V2f& screenWindowCenter();
    IMF_EXPORT
    const IMATH_NAMESPACE::V2f& screenWindowCenter() const
        CPPMM_RENAME(screenWindowCenter_const);

    IMF_EXPORT
    float& screenWindowWidth();
    IMF_EXPORT
    const float& screenWindowWidth() const
        CPPMM_RENAME(screenWindowWidth_const);

    IMF_EXPORT
    Imf::ChannelList& channels();
    IMF_EXPORT
    const Imf::ChannelList& channels() const CPPMM_RENAME(channels_const);

    IMF_EXPORT
    Imf::LineOrder& lineOrder();
    IMF_EXPORT
    const Imf::LineOrder& lineOrder() const CPPMM_RENAME(lineOrder_const);

    IMF_EXPORT
    Imf::Compression& compression();
    IMF_EXPORT
    const Imf::Compression& compression() const CPPMM_RENAME(compression_const);

    IMF_EXPORT
    void setName(const std::string& name);

    IMF_EXPORT
    std::string& name();
    IMF_EXPORT
    const std::string& name() const CPPMM_RENAME(name_const);

    IMF_EXPORT
    bool hasName() const;

    IMF_EXPORT
    void setType(const std::string& Type);

    IMF_EXPORT
    std::string& type();
    IMF_EXPORT
    const std::string& type() const CPPMM_RENAME(type_const);

    IMF_EXPORT
    bool hasType() const;

    IMF_EXPORT
    void setVersion(const int version);

    IMF_EXPORT
    int& version();
    IMF_EXPORT
    const int& version() const;

    IMF_EXPORT
    bool hasVersion() const;

    IMF_EXPORT
    void setChunkCount(int chunks);
    IMF_EXPORT
    bool hasChunkCount() const;
    IMF_EXPORT
    const int& chunkCount() const CPPMM_RENAME(chunkCount_const);
    IMF_EXPORT
    int& chunkCount();

    IMF_EXPORT
    void setView(const std::string& view);
    IMF_EXPORT
    bool hasView() const;
    IMF_EXPORT
    std::string& view();
    IMF_EXPORT
    const std::string& view() const CPPMM_RENAME(view_const);

    IMF_EXPORT
    void setTileDescription(const Imf::TileDescription& td);

    IMF_EXPORT
    Imf::TileDescription& tileDescription();
    IMF_EXPORT
    const Imf::TileDescription& tileDescription() const
        CPPMM_RENAME(tileDescription_const);

    IMF_EXPORT
    bool hasTileDescription() const;

    IMF_EXPORT
    void setPreviewImage(const Imf::PreviewImage& p);

    IMF_EXPORT
    Imf::PreviewImage& previewImage();
    IMF_EXPORT
    const Imf::PreviewImage& previewImage() const
        CPPMM_RENAME(previewImage_const);

    IMF_EXPORT
    bool hasPreviewImage() const;

    IMF_EXPORT
    void sanityCheck(bool isTiled = false, bool isMultipartFile = false) const;

    IMF_EXPORT
    static void setMaxImageSize(int maxWidth, int maxHeight);
    IMF_EXPORT
    static void setMaxTileSize(int maxWidth, int maxHeight);

    IMF_EXPORT
    bool readsNothing();

    IMF_EXPORT
    Imf::Int64 writeTo(Imf::OStream& os, bool isTiled = false) const;

    IMF_EXPORT
    void readFrom(Imf::IStream& is, int& version);

    struct Iterator {
        using BoundType = Imf::Header::Iterator;

        IMF_EXPORT
        Iterator();
        IMF_EXPORT
        Iterator(const Imf::Header::AttributeMap::iterator& i) CPPMM_IGNORE;

        IMF_EXPORT
        Imf::Header::Iterator& operator++() CPPMM_RENAME(inc);
        IMF_EXPORT
        Imf::Header::Iterator operator++(int) CPPMM_IGNORE;

        IMF_EXPORT
        const char* name() const;
        IMF_EXPORT
        Imf::Attribute& attribute() const;

    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::Header::ConstIterator;

        IMF_EXPORT
        ConstIterator();
        IMF_EXPORT
        ConstIterator(const Imf::Header::AttributeMap::iterator& i)
            CPPMM_IGNORE;

        IMF_EXPORT
        Imf::Header::ConstIterator& operator++() CPPMM_RENAME(inc);
        IMF_EXPORT
        Imf::Header::ConstIterator operator++(int) CPPMM_IGNORE;

        IMF_EXPORT
        const char* name() const;
        IMF_EXPORT
        Imf::Attribute& attribute() const;

    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
