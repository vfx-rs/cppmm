#include <math.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace MYMATH_INTERNAL_NAMESPACE {

namespace Mymath = ::MYMATH_INTERNAL_NAMESPACE;

struct Vec3 {
    using BoundType = Mymath::Vec3;

    Vec3();
    Vec3(float x, float y, float z);
    Vec3(float v);
    Vec3(const Mymath::Vec3& v);

    float length() const;
};

} // namespace MYMATH_INTERNAL_NAMESPACE

} // namespace cppmm_bind
