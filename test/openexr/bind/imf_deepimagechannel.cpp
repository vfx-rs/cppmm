#include <OpenEXR/ImfDeepImageChannel.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepImageChannel {
    using BoundType = Imf::DeepImageChannel;
} CPPMM_OPAQUEBYTES;

template <typename T> struct TypedDeepImageChannel {
    using BoundType = Imf::TypedDeepImageChannel<T>;
} CPPMM_OPAQUEBYTES;

template class TypedDeepImageChannel<half>;
using DeepHalfChannel = Imf::TypedDeepImageChannel<half>;

template class TypedDeepImageChannel<float>;
using DeepFloatChannel = Imf::TypedDeepImageChannel<float>;

template class TypedDeepImageChannel<unsigned int>;
using DeepUIntChannel = Imf::TypedDeepImageChannel<unsigned int>;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind

template class Imf::TypedDeepImageChannel<half>;
template class Imf::TypedDeepImageChannel<float>;
template class Imf::TypedDeepImageChannel<unsigned int>;
