#include <OpenEXR/ImfArray.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

template <class T> class Array {
public:
    using BoundType = Imf::Array<T>;
} CPPMM_OPAQUEBYTES;

template class Array<float>;
using ArrayFloat = Imf::Array<float>;

template <class T> class Array2D {
public:
    using BoundType = Imf::Array2D<T>;
} CPPMM_OPAQUEBYTES;

template class Array2D<float>;
using Array2DFloat = Imf::Array2D<float>;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind

template class Imf::Array<float>;
template class Imf::Array2D<float>;
