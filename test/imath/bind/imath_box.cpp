#include <Imath/ImathBox.h>

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm:opaquebytes")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))

namespace cppmm_bind {

namespace IMATH_INTERNAL_NAMESPACE {

namespace Imath = IMATH_INTERNAL_NAMESPACE;

template <class V> class Box {
public:
    V min;
    V max;

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Box() {}
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Box(const V& point);
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Box(const V& minV, const V& maxV);

    IMATH_HOSTDEVICE void makeEmpty();
    IMATH_HOSTDEVICE void extendBy(const V& point);
    IMATH_HOSTDEVICE void extendBy(const ::Imath::Box<V>& box);

    template <typename T>
    void templated_method(const T& t);

} CPPMM_VALUETYPE;

using Box3f = Box<::Imath::V3f>;
Box3f box3f;

template <>
template <>
void Box3f::templated_method(const float& t);

class Foo {
public:
    int a, b;

    Foo(){}
};

} // namespace IMATH_INTERNAL_NAMESPACE


} // namespace cppmm_bind
