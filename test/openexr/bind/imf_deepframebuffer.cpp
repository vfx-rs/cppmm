#include <OpenEXR/ImfDeepFrameBuffer.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepSlice {
    using BoundType = Imf::DeepSlice;
    IMF_EXPORT
    DeepSlice(Imf::PixelType type, char* base, size_t xStride, size_t yStride,
              size_t sampleStride, int xSampling, int ySampling,
              double fillValue, bool xTileCoords, bool yTileCoords);
} CPPMM_VALUETYPE;

struct DeepFrameBuffer {
    using BoundType = Imf::DeepFrameBuffer;

    IMF_EXPORT
    void insert(const char name[], const Imf::DeepSlice& slice);

    IMF_EXPORT
    void insert(const std::string& name,
                const Imf::DeepSlice& slice) CPPMM_IGNORE;

    IMF_EXPORT
    Imf::DeepSlice& operator[](const char name[]);
    IMF_EXPORT
    const Imf::DeepSlice& operator[](const char name[]) const;

    IMF_EXPORT
    Imf::DeepSlice& operator[](const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    const Imf::DeepSlice&
    operator[](const std::string& name) const CPPMM_IGNORE;

    IMF_EXPORT
    Imf::DeepSlice* findSlice(const char name[]);
    IMF_EXPORT
    const Imf::DeepSlice* findSlice(const char name[]) const;

    IMF_EXPORT
    Imf::DeepSlice* findSlice(const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    const Imf::DeepSlice* findSlice(const std::string& name) const CPPMM_IGNORE;

    IMF_EXPORT
    Imf::DeepFrameBuffer::Iterator begin();
    IMF_EXPORT
    Imf::DeepFrameBuffer::ConstIterator begin() const CPPMM_RENAME(begin_const);

    IMF_EXPORT
    Imf::DeepFrameBuffer::Iterator end();
    IMF_EXPORT
    Imf::DeepFrameBuffer::ConstIterator end() const CPPMM_RENAME(end_const);

    IMF_EXPORT
    Imf::DeepFrameBuffer::Iterator find(const char name[]);
    IMF_EXPORT
    Imf::DeepFrameBuffer::ConstIterator find(const char name[]) const;

    IMF_EXPORT
    Imf::DeepFrameBuffer::Iterator find(const std::string& name) CPPMM_IGNORE;
    IMF_EXPORT
    Imf::DeepFrameBuffer::ConstIterator
    find(const std::string& name) const CPPMM_IGNORE;

    //----------------------------------------------------
    // Public function for accessing a sample count slice.
    //----------------------------------------------------

    IMF_EXPORT
    void insertSampleCountSlice(const Imf::Slice& slice);
    IMF_EXPORT
    const Imf::Slice& getSampleCountSlice() const;

    struct Iterator {
        using BoundType = Imf::DeepFrameBuffer::Iterator;
        IMF_EXPORT
        Iterator();
        IMF_EXPORT
        Iterator(const Imf::DeepFrameBuffer::SliceMap::iterator& i)
            CPPMM_IGNORE;

        IMF_EXPORT
        Iterator& operator++();
        IMF_EXPORT
        Iterator operator++(int) CPPMM_IGNORE;

        IMF_EXPORT
        const char* name() const;
        IMF_EXPORT
        Imf::DeepSlice& slice() const;

    } CPPMM_OPAQUEBYTES;

    struct ConstIterator {
        using BoundType = Imf::DeepFrameBuffer::ConstIterator;
        IMF_EXPORT
        ConstIterator();
        IMF_EXPORT
        ConstIterator(const Imf::DeepFrameBuffer::SliceMap::iterator& i)
            CPPMM_IGNORE;

        IMF_EXPORT
        ConstIterator& operator++();
        IMF_EXPORT
        ConstIterator operator++(int) CPPMM_IGNORE;

        IMF_EXPORT
        const char* name() const;
        IMF_EXPORT
        Imf::DeepSlice& slice() const;

    } CPPMM_OPAQUEBYTES;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
