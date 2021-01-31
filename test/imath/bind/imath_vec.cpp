#include <Imath/ImathVec.h>

#include <vector>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

template <class T> class Vec3 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::Imath::Vec3<T>;

    /*
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
    */

    // constexpr static unsigned int dimensions();

    // constexpr static T baseTypeMin();
    // constexpr static T baseTypeMax();
    // constexpr static T baseTypeSmallest();
    // constexpr static T baseTypeEpsilon();

    // ugh - in order for the explicit instantiation to work we must provide
    // a function body here.
    template <class S> IMATH_HOSTDEVICE void setValue (S a, S b, S c);

} CPPMM_VALUETYPE;

// explicit instantiation
template class Vec3<float>;

// note the 'extern' here otherwise we get an error because we're not
// defining the template body up above
extern template 
IMATH_HOSTDEVICE void Vec3<float>::setValue(float a, float b, float c);

} // namespace cppmm_bind

template class Imath::Vec3<float>;

extern template 
IMATH_HOSTDEVICE void Imath::Vec3<float>::setValue(float a, float b, float c);
