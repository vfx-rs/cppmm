#include <OpenEXR/ImfFlatImageChannel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct FlatImageChannel {
    using BoundType = Imf::FlatImageChannel;
} CPPMM_OPAQUEBYTES;

template <typename T> struct TypedFlatImageChannel {
    using BoundType = Imf::TypedFlatImageChannel<T>;
} CPPMM_OPAQUEBYTES;

template class TypedFlatImageChannel<half>;
using FlatHalfChannel = Imf::TypedFlatImageChannel<half>;

template class TypedFlatImageChannel<float>;
using FlatFloatChannel = Imf::TypedFlatImageChannel<float>;

template class TypedFlatImageChannel<unsigned int>;
using FlatUIntChannel = Imf::TypedFlatImageChannel<unsigned int>;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind

template class Imf::TypedFlatImageChannel<half>;
template class Imf::TypedFlatImageChannel<float>;
template class Imf::TypedFlatImageChannel<unsigned int>;
