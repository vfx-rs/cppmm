#include <OpenEXR/ImfFrameBuffer.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct Slice {
    using BoundType = Imf::Slice;

    IMF_EXPORT
    Slice(Imf::PixelType type, char* base = 0, size_t xStride = 0,
          size_t yStride = 0, int xSampling = 1, int ySampling = 1,
          double fillValue = 0.0, bool xTileCoords = false,
          bool yTileCoords = false);

    IMF_EXPORT
    Slice(const Imf::Slice & rhs);

    IMF_EXPORT
    static Imf::Slice Make(Imf::PixelType type, const void* ptr,
                           const IMATH_NAMESPACE::V2i& origin, int64_t w,
                           int64_t h, size_t xStride = 0, size_t yStride = 0,
                           int xSampling = 1, int ySampling = 1,
                           double fillValue = 0.0, bool xTileCoords = false,
                           bool yTileCoords = false) CPPMM_IGNORE;

    IMF_EXPORT
    static Imf::Slice Make(Imf::PixelType type, const void* ptr,
                           const IMATH_NAMESPACE::Box2i& dataWindow,
                           size_t xStride = 0, size_t yStride = 0,
                           int xSampling = 1, int ySampling = 1,
                           double fillValue = 0.0, bool xTileCoords = false,
                           bool yTileCoords = false);
} CPPMM_VALUETYPE;

struct FrameBuffer {
    using BoundType = Imf::FrameBuffer;

    IMF_EXPORT
    void insert(const char name[], const Imf::Slice& slice);

    IMF_EXPORT
    void insert(const std::string& name, const Imf::Slice& slice) CPPMM_IGNORE;

    IMF_EXPORT
    Imf::Slice& operator[](const char name[]);
    IMF_EXPORT
    const Imf::Slice& operator[](const char name[]) const;

    IMF_EXPORT
    Imf::Slice& operator[](const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    const Imf::Slice& operator[](const std::string& name) const CPPMM_IGNORE;

    IMF_EXPORT
    Imf::Slice* findSlice(const char name[]);
    IMF_EXPORT
    const Imf::Slice* findSlice(const char name[]) const;

    IMF_EXPORT
    Imf::Slice* findSlice(const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    const Imf::Slice* findSlice(const std::string& name) const CPPMM_IGNORE;

    IMF_EXPORT
    Imf::FrameBuffer::Iterator begin();
    IMF_EXPORT
    Imf::FrameBuffer::ConstIterator begin() const CPPMM_RENAME(begin_const);

    IMF_EXPORT
    Imf::FrameBuffer::Iterator end();
    IMF_EXPORT
    Imf::FrameBuffer::ConstIterator end() const CPPMM_RENAME(end_const);

    IMF_EXPORT
    Imf::FrameBuffer::Iterator find(const char name[]);
    IMF_EXPORT
    Imf::FrameBuffer::ConstIterator find(const char name[]) const;

    IMF_EXPORT
    Imf::FrameBuffer::Iterator find(const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    Imf::FrameBuffer::ConstIterator
    find(const std::string& name) const CPPMM_IGNORE;

    struct Iterator {
        using BoundType = Imf::FrameBuffer::Iterator;
        IMF_EXPORT
        Iterator();
        IMF_EXPORT
        Iterator(const Imf::FrameBuffer::SliceMap::iterator& i) CPPMM_IGNORE;
        IMF_EXPORT
        Iterator(const Imf::FrameBuffer::Iterator& rhs);

        IMF_EXPORT
        Iterator& operator++();
        IMF_EXPORT
        Iterator operator++(int) CPPMM_IGNORE;

        IMF_EXPORT
        const char* name() const;
        IMF_EXPORT
        Imf::Slice& slice() const;

    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::FrameBuffer::ConstIterator;
        IMF_EXPORT
        ConstIterator();
        IMF_EXPORT
        ConstIterator(const Imf::FrameBuffer::SliceMap::iterator& i)
            CPPMM_IGNORE;
        IMF_EXPORT
        ConstIterator(const Imf::FrameBuffer::ConstIterator& rhs);

        IMF_EXPORT
        ConstIterator& operator++();
        IMF_EXPORT
        ConstIterator operator++(int) CPPMM_IGNORE;

        IMF_EXPORT
        const char* name() const;
        IMF_EXPORT
        Imf::Slice& slice() const;

    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
