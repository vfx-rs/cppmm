#include <OpenEXR/ImathVec.h>

#include <vector>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace IMATH_INTERNAL_NAMESPACE {

namespace Imath = ::IMATH_INTERNAL_NAMESPACE;
template <class T> class Vec2 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = Imath::Vec2<T>;

    T& operator[](int i) CPPMM_RENAME(index);
    const T& operator[](int i) const CPPMM_RENAME(index_const);

    Vec2() CPPMM_IGNORE;                        // no initialization
    explicit Vec2(T a) CPPMM_RENAME(broadcast); // (a a)
    Vec2(T a, T b);                             // (a b)

    Vec2(const Imath::Vec2<T>& v);
    template <class S> Vec2(const Imath::Vec2<S>& v) CPPMM_IGNORE;

    const Imath::Vec2<T>& operator=(const Imath::Vec2<T>& v);

    //------------
    // Destructor
    //------------

    ~Vec2() = default;

    //----------------------
    // Compatibility with Sb
    //----------------------

    template <class S> void setValue(S a, S b) CPPMM_IGNORE;

    template <class S> void setValue(const Vec2<S>& v) CPPMM_IGNORE;

    template <class S> void getValue(S& a, S& b) const CPPMM_IGNORE;

    template <class S> void getValue(Vec2<S>& v) const CPPMM_IGNORE;

    T* getValue() CPPMM_IGNORE;
    const T* getValue() const CPPMM_IGNORE;

    //---------
    // Equality
    //---------

    template <class S> bool operator==(const Imath::Vec2<S>& v) const;

    template <class S> bool operator!=(const Imath::Vec2<S>& v) const;

    //-----------------------------------------------------------------------
    // Compare two vectors and test if they are "approximately equal":
    //
    // equalWithAbsError (v, e)
    //
    //	    Returns true if the coefficients of this and v are the same with
    //	    an absolute error of no more than e, i.e., for all i
    //
    //      abs (this[i] - v[i]) <= e
    //
    // equalWithRelError (v, e)
    //
    //	    Returns true if the coefficients of this and v are the same with
    //	    a relative error of no more than e, i.e., for all i
    //
    //      abs (this[i] - v[i]) <= e * abs (this[i])
    //-----------------------------------------------------------------------

    bool equalWithAbsError(const Imath::Vec2<T>& v, T e) const;
    bool equalWithRelError(const Imath::Vec2<T>& v, T e) const;

    //------------
    // Dot product
    //------------

    T dot(const Imath::Vec2<T>& v) const;
    T operator^(const Imath::Vec2<T>& v) const CPPMM_IGNORE;

    //------------------------------------------------
    // Right-handed cross product, i.e. z component of
    // Vec3 (this->x, this->y, 0) % Vec3 (v.x, v.y, 0)
    //------------------------------------------------

    T cross(const Imath::Vec2<T>& v) const;
    T operator%(const Imath::Vec2<T>& v) const CPPMM_IGNORE;

    //------------------------
    // Component-wise addition
    //------------------------

    const Imath::Vec2<T>& operator+=(const Imath::Vec2<T>& v);
    Imath::Vec2<T> operator+(const Imath::Vec2<T>& v) const;

    //---------------------------
    // Component-wise subtraction
    //---------------------------

    const Imath::Vec2<T>& operator-=(const Imath::Vec2<T>& v);
    Imath::Vec2<T> operator-(const Imath::Vec2<T>& v) const;

    //------------------------------------
    // Component-wise multiplication by -1
    //------------------------------------

    Imath::Vec2<T> operator-() const;
    const Imath::Vec2<T>& negate();

    //------------------------------
    // Component-wise multiplication
    //------------------------------

    const Imath::Vec2<T>& operator*=(const Imath::Vec2<T>& v);
    const Imath::Vec2<T>& operator*=(T a);
    Imath::Vec2<T> operator*(const Imath::Vec2<T>& v) const;
    Imath::Vec2<T> operator*(T a) const;

    //------------------------
    // Component-wise division
    //------------------------

    const Imath::Vec2<T>& operator/=(const Imath::Vec2<T>& v);
    const Imath::Vec2<T>& operator/=(T a);
    Imath::Vec2<T> operator/(const Imath::Vec2<T>& v) const;
    Imath::Vec2<T> operator/(T a) const;

    //----------------------------------------------------------------
    // Length and normalization:  If v.length() is 0.0, v.normalize()
    // and v.normalized() produce a null vector; v.normalizeExc() and
    // v.normalizedExc() throw a NullVecExc.
    // v.normalizeNonNull() and v.normalizedNonNull() are slightly
    // faster than the other normalization routines, but if v.length()
    // is 0.0, the result is undefined.
    //----------------------------------------------------------------

    T length() const;
    T length2() const;

    const Imath::Vec2<T>& normalize(); // modifies *this
    const Imath::Vec2<T>& normalizeExc();
    const Imath::Vec2<T>& normalizeNonNull();

    Imath::Vec2<T> normalized() const; // does not modify *this
    Imath::Vec2<T> normalizedExc() const;
    Imath::Vec2<T> normalizedNonNull() const;

    //--------------------------------------------------------
    // Number of dimensions, i.e. number of elements in a Vec2
    //--------------------------------------------------------

    static unsigned int dimensions();

    //-------------------------------------------------
    // Limitations of type T (see also class limits<T>)
    //-------------------------------------------------

    static T baseTypeMin();
    static T baseTypeMax();
    static T baseTypeSmallest();
    static T baseTypeEpsilon();

} CPPMM_VALUETYPE;

// explicit instantiation
template class Vec2<short>;
template class Vec2<int>;
template class Vec2<float>;
template class Vec2<double>;
using V2s = Imath::V2s;
using V2i = Imath::V2i;
using V2f = Imath::V2f;
using V2d = Imath::V2d;

template <class T> class Vec3 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = Imath::Vec3<T>;

} CPPMM_VALUETYPE;

// explicit instantiation
template class Vec3<short>;
template class Vec3<int>;
template class Vec3<float>;
template class Vec3<double>;
using V3s = Imath::V3s;
using V3i = Imath::V3i;
using V3f = Imath::V3f;
using V3d = Imath::V3d;

template <class T> class Vec4 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = Imath::Vec4<T>;

} CPPMM_VALUETYPE;

// explicit instantiation
template class Vec4<short>;
template class Vec4<int>;
template class Vec4<float>;
template class Vec4<double>;
using V4s = Imath::V4s;
using V4i = Imath::V4i;
using V4f = Imath::V4f;
using V4d = Imath::V4d;

} // namespace IMATH_INTERNAL_NAMESPACE
} // namespace cppmm_bind

template class Imath::Vec2<short>;
template class Imath::Vec2<int>;
template class Imath::Vec2<float>;
template class Imath::Vec2<double>;

template class Imath::Vec3<short>;
template class Imath::Vec3<int>;
template class Imath::Vec3<float>;
template class Imath::Vec3<double>;

template class Imath::Vec4<short>;
template class Imath::Vec4<int>;
template class Imath::Vec4<float>;
template class Imath::Vec4<double>;
