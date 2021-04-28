#include <OpenEXR/ImathVec.h>

#include <vector>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

template <class T> class Vec3 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::Imath::Vec3<T>;

    Vec3();
    Vec3(const ::Imath::Vec3<T>&);
    template <typename S> Vec3(const ::Imath::Vec3<S>& v);

    // we're not actually paying any attention to the method declarations yet
    // no matching
    /*
    bool equalWithAbsError(const Vec3<T>& v, T e) const;
    bool equalWithRelError(const Vec3<T>& v, T e) const;
    */

    T dot(const ::Imath::Vec3<T>& v) const;
    ::Imath::Vec3<T> cross(const ::Imath::Vec3<T>& v) const;
    const ::Imath::Vec3<T>& operator+=(const ::Imath::Vec3<T>& v)
        CPPMM_RENAME(op_iadd);

    const ::Imath::Vec3<T>& normalize();
    ::Imath::Vec3<T> normalized() const;

#if 0
    ::Imath::Vec3<T> operator+(const ::Imath::Vec3<T>& v) const;

    const ::Imath::Vec3<T>& operator-=(const ::Imath::Vec3<T>& v);
    ::Imath::Vec3<T> operator-(const ::Imath::Vec3<T>& v) const
    CPPMM_RENAME(op_sub);

    constexpr ::Imath::Vec3<T> operator-() const CPPMM_RENAME(op_neg);

    const ::Imath::Vec3<T>& operator*=(const ::Imath::Vec3<T>& v) CPPMM_RENAME(op_neg);
    const ::Imath::Vec3<T>& operator*=(T a) CPPMM_RENAME(mul_assign_t) CPPMM_RENAME(op_neg);
    ::Imath::Vec3<T> operator*(const ::Imath::Vec3<T>& v) const;
    ::Imath::Vec3<T> operator*(T a) const CPPMM_RENAME(mul_t);

    const ::Imath::Vec3<T>& operator/=(const ::Imath::Vec3<T>& v);
    const ::Imath::Vec3<T>& operator/=(T a) CPPMM_RENAME(div_assign_t);
    ::Imath::Vec3<T> operator/(const ::Imath::Vec3<T>& v) const;
    ::Imath::Vec3<T> operator/(T a) const CPPMM_RENAME(div_t);

    const ::Imath::Vec3<T>& normalize();    // modifies *this
    ::Imath::Vec3<T> normalized() const; // does not modify *this

    // constexpr static unsigned int dimensions();

    // constexpr static T baseTypeMin();
    // constexpr static T baseTypeMax();
    // constexpr static T baseTypeSmallest();
    // constexpr static T baseTypeEpsilon();
#endif
    T length() const;
    constexpr T length2() const;

    template <class S> void setValue(S a, S b, S c);

} CPPMM_VALUETYPE CPPMM_TRIVIALLY_MOVABLE CPPMM_TRIVIALLY_COPYABLE;

// explicit instantiation
template class Vec3<float>;
template class Vec3<int>;
using V3f = Imath::V3f;
using V3i = Imath::V3i;

// note the 'extern' here otherwise we get an error because we're not
// defining the template body up above
extern template void Vec3<float>::setValue(float a, float b, float c);
// extern template void Vec3<int>::setValue(int a, int b, int c);

} // namespace cppmm_bind

template class Imath::Vec3<float>;
template class Imath::Vec3<int>;

extern template void Imath::Vec3<float>::setValue(float a, float b, float c);
extern template void Imath::Vec3<int>::setValue(int a, int b, int c);
