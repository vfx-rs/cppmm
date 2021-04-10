#include <OpenEXR/ImfArray.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

template <class T> class Array {
public:
    using BoundType = Imf::Array<T>;

    Array() CPPMM_RENAME(new);
    Array(long size) CPPMM_RENAME(with_size);
    ~Array() CPPMM_RENAME(delete);

    operator T*() CPPMM_RENAME(as_ptr);
    operator const T*() const CPPMM_RENAME(as_const_ptr);

    void resizeErase(long size);
    void resizeEraseUnsafe(long size);

    long size() const;
} CPPMM_OPAQUEBYTES;

template class Array<float>;
using ArrayFloat = Imf::Array<float>;

template class Array<char>;
using ArrayChar = Imf::Array<char>;

template <class T> class Array2D {
public:
    using BoundType = Imf::Array2D<T>;
    Array2D() CPPMM_RENAME(new);
    Array2D(long sizeX, long sizeY) CPPMM_RENAME(with_size);
    ~Array2D() CPPMM_RENAME(delete);

    T* operator[](long x) CPPMM_RENAME(row);
    const T* operator[](long x) const CPPMM_RENAME(const_row);

    void resizeErase(long sizeX, long sizeY);
    void resizeEraseUnsafe(long sizeX, long sizeY);

    long height() const;
    long width() const;
} CPPMM_OPAQUEBYTES;

template class Array2D<float>;
using Array2DFloat = Imf::Array2D<float>;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind

template class Imf::Array<float>;
template class Imf::Array<char>;
template class Imf::Array2D<float>;
