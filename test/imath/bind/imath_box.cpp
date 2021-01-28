#include <Imath/ImathBox.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

// I don't think we actually need the matching namespace structure any more
// since we're using the type aliases on the classes as "type pointers"
namespace IMATH_INTERNAL_NAMESPACE {

namespace Imath = IMATH_INTERNAL_NAMESPACE;

template <class V> class Box {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::Imath::Box<V>;
    // Need to actually create an instance of the type to get it to specialize
    // fully
    BoundType bound_inst;

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Box() {}
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Box(const V& point);
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Box(const V& minV, const V& maxV);

    IMATH_HOSTDEVICE void makeEmpty();
    IMATH_HOSTDEVICE void extendBy(const V& point);
    IMATH_HOSTDEVICE void extendBy(const ::Imath::Box<V>& box);

} CPPMM_VALUETYPE;

// This 'pulls' the Imath::Box specialization through
using Box3f = Box<::Imath::V3f>;
// Again need an instance of it for clang to actually create the specialization
// maybe we could wrap this up in a macro to be less ugly
Box3f box3f;

} // namespace IMATH_INTERNAL_NAMESPACE


} // namespace cppmm_bind
