#include <Imath/ImathVec.h>

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm:opaquebytes")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))

namespace cppmm_bind {

namespace IMATH_INTERNAL_NAMESPACE {

namespace Imath = IMATH_INTERNAL_NAMESPACE;

template <class T> class Vec3 {
public:
    bool equalWithAbsError(const Vec3<T>& v, T e) const;
    bool equalWithRelError(const Vec3<T>& v, T e) const;

    T dot(const Vec3& v) const;
    Vec3 cross(const Vec3& v) const;

    const Vec3& operator+=(const Vec3& v);
    Vec3 operator+(const Vec3& v) const;

    const Vec3& operator-=(const Vec3& v);
    Vec3 operator-(const Vec3& v) const;

    constexpr Vec3 operator-() const CPPMM_RENAME(op_neg);

    const Vec3& operator*=(const Vec3& v);
    const Vec3& operator*=(T a) CPPMM_RENAME(mul_assign_t);
    Vec3 operator*(const Vec3& v) const;
    Vec3 operator*(T a) const CPPMM_RENAME(mul_t);

    const Vec3& operator/=(const Vec3& v);
    const Vec3& operator/=(T a) CPPMM_RENAME(div_assign_t);
    Vec3 operator/(const Vec3& v) const;
    Vec3 operator/(T a) const CPPMM_RENAME(div_t);

    T length() const;
    constexpr T length2() const;

    const Vec3& normalize();    // modifies *this
    Vec3<T> normalized() const; // does not modify *this

    constexpr static unsigned int dimensions();

    constexpr static T baseTypeMin();
    constexpr static T baseTypeMax();
    constexpr static T baseTypeSmallest();
    constexpr static T baseTypeEpsilon();

} CPPMM_VALUETYPE;

// These type aliases will cause the class template to be monomorphized with
// the given template parameter as if it had been explicitly declared
using V3f = Vec3<float>;
using V3i = Vec3<int>;

} // namespace IMATH_INTERNAL_NAMESPACE

} // namespace cppmm_bind
