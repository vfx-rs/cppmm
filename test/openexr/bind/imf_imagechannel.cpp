#include <OpenEXR/ImfImageChannel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct ImageChannel {
    using BoundType = Imf::ImageChannel;
} CPPMM_OPAQUEBYTES;

// template <typename T> struct TypedImageChannel {
//     using BoundType = Imf::TypedImageChannel<T>;
// } CPPMM_OPAQUEBYTES;

// template class TypedImageChannel<half>;
// using HalfChannel = Imf::TypedImageChannel<half>;

// template class TypedImageChannel<float>;
// using FloatChannel = Imf::TypedImageChannel<float>;

// template class TypedImageChannel<unsigned int>;
// using UIntChannel = Imf::TypedImageChannel<unsigned int>;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind

// template class Imf::TypedImageChannel<half>;
// template class Imf::TypedImageChannel<float>;
// template class Imf::TypedImageChannel<unsigned int>;
