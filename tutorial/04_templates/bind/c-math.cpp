#include <math.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace MYMATH_INTERNAL_NAMESPACE {

namespace Mymath = ::MYMATH_INTERNAL_NAMESPACE;

template <typename T> struct Vec3 {
    using BoundType = Mymath::Vec3<T>;

    Vec3() CPPMM_RENAME(default);
    Vec3(T x, T y, T z) CPPMM_RENAME(new);
    Vec3(T v) CPPMM_RENAME(from_scalar);
    Vec3(const Mymath::Vec3<T>& v) CPPMM_RENAME(copy);

    T length() const;
} CPPMM_VALUETYPE;

template class Vec3<float>; // instantiate binding for float
template class Vec3<int>;   // instantiate binding for int

using V3f = Mymath::Vec3<float>;
using V3i = Mymath::Vec3<int>;

} // namespace MYMATH_INTERNAL_NAMESPACE

} // namespace cppmm_bind

template class Mymath::Vec3<float>; // instantiate library Vec3 for float
template class Mymath::Vec3<int>;   // instantiate library Vec3 for int
