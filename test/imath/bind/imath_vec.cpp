#include <Imath/ImathVec.h>

#include <vector>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

template <class T> class Vec3 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::Imath::Vec3<T>;
    // Need to actually create an instance of the type to get it to specialize
    // fully
    BoundType bound_inst;

    // we're not actually paying any attention to the method declarations yet
    // no matching
    bool equalWithAbsError(const Vec3<T>& v, T e) const;
    bool equalWithRelError(const Vec3<T>& v, T e) const;

    T dot(const ::Imath::Vec3<T>& v) const;
    ::Imath::Vec3<T> cross(const ::Imath::Vec3<T>& v) const;

    const ::Imath::Vec3<T>& operator+=(const ::Imath::Vec3<T>& v);
    ::Imath::Vec3<T> operator+(const ::Imath::Vec3<T>& v) const;

    const ::Imath::Vec3<T>& operator-=(const ::Imath::Vec3<T>& v);
    ::Imath::Vec3<T> operator-(const ::Imath::Vec3<T>& v) const CPPMM_RENAME(op_neg);

    constexpr ::Imath::Vec3<T> operator-() const;// CPPMM_RENAME(op_neg);

    const ::Imath::Vec3<T>& operator*=(const ::Imath::Vec3<T>& v);
    const ::Imath::Vec3<T>& operator*=(T a) CPPMM_RENAME(mul_assign_t);
    ::Imath::Vec3<T> operator*(const ::Imath::Vec3<T>& v) const;
    ::Imath::Vec3<T> operator*(T a) const CPPMM_RENAME(mul_t);

    const ::Imath::Vec3<T>& operator/=(const ::Imath::Vec3<T>& v);
    const ::Imath::Vec3<T>& operator/=(T a) CPPMM_RENAME(div_assign_t);
    ::Imath::Vec3<T> operator/(const ::Imath::Vec3<T>& v) const;
    ::Imath::Vec3<T> operator/(T a) const CPPMM_RENAME(div_t);

    T length() const;
    constexpr T length2() const;

    const ::Imath::Vec3<T>& normalize();    // modifies *this
    ::Imath::Vec3<T> normalized() const; // does not modify *this

    constexpr static unsigned int dimensions();

    constexpr static T baseTypeMin();
    constexpr static T baseTypeMax();
    constexpr static T baseTypeSmallest();
    constexpr static T baseTypeEpsilon();

    template <class S> IMATH_HOSTDEVICE void setValue (S a, S b, S c);
} CPPMM_VALUETYPE;

// These type aliases will cause the class template to be monomorphized with
// the given template parameter as if it had been explicitly declared
using V3f = Vec3<float>;
V3f v3f;
using V3i = Vec3<int>;
V3i v3i;

} // namespace cppmm_bind

namespace IMATH_INTERNAL_NAMESPACE {

// in order for clang to see the code for template functions that depend on
// another template parameter list, we have to explicitly specialize them for
// all the types we're interested in like this:
// yuck - just realised that for matching we're going to need to do this for
// the binding version as well.
template <>
template <>
IMATH_HOSTDEVICE void ::Imath::Vec3<float>::setValue(float a, float b, float c);

}
