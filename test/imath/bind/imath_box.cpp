#include <OpenEXR/ImathBox.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

// I don't think we actually need the matching namespace structure any more
// since we're using the type aliases on the classes as "type pointers"
namespace IMATH_INTERNAL_NAMESPACE {

namespace Imath = ::IMATH_INTERNAL_NAMESPACE;

template <class V> class Box {
public:
    // This allows us to see through to the type in Imath
    using BoundType = Imath::Box<V>;

    // IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Box();
    // IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Box(const V& point);
    // IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Box(const V& minV, const V& maxV);

    // IMATH_HOSTDEVICE void makeEmpty();
    void extendBy(const V& point);
    void extendBy(const Imath::Box<V>& box);

} CPPMM_VALUETYPE CPPMM_TRIVIALLY_MOVABLE CPPMM_TRIVIALLY_COPYABLE;

// This 'pulls' the Imath::Box specialization through
template class Box<Imath::Vec3<float>>;
template class Box<Imath::Vec3<int>>;
using Box3f = Imath::Box3f;
using Box3i = Imath::Box3i;

} // namespace IMATH_INTERNAL_NAMESPACE
} // namespace cppmm_bind

// namespace IMATH_INTERNAL_NAMESPACE {
// template class Box<Vec3<float>>;
// }

// Need this explicit instantiation to actually get the library templates
// in the AST
template class Imath::Box<Imath::Vec3<float>>;
template class Imath::Box<Imath::Vec3<int>>;
