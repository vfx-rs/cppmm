#include <OpenEXR/ImathMatrix.h>

#include <vector>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace IMATH_INTERNAL_NAMESPACE {

namespace Imath = ::IMATH_INTERNAL_NAMESPACE;
enum Uninitialized { UNINITIALIZED };

template <class T> class Matrix33 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = Imath::Matrix33<T>;

    T* operator[](int i) CPPMM_RENAME(row);
    const T* operator[](int i) const CPPMM_RENAME(row_const);

    Matrix33(Imath::Uninitialized _unused) CPPMM_RENAME(uninitialized);

    Matrix33() CPPMM_RENAME(identity);
    // 1 0 0
    // 0 1 0
    // 0 0 1

    Matrix33(T a) CPPMM_RENAME(broadcast);
    // a a a
    // a a a
    // a a a

    Matrix33(const T a[3][3]) CPPMM_RENAME(from_array);
    // a[0][0] a[0][1] a[0][2]
    // a[1][0] a[1][1] a[1][2]
    // a[2][0] a[2][1] a[2][2]

    Matrix33(T a, T b, T c, T d, T e, T f, T g, T h, T i);

    // a b c
    // d e f
    // g h i

    Matrix33(const Imath::Matrix33<T>& v);
    template <class S>
    explicit Matrix33(const Imath::Matrix33<S>& v) CPPMM_IGNORE;

    const Imath::Matrix33<T>& operator=(const Imath::Matrix33<T>& v);
    const Imath::Matrix33<T>& operator=(T a) CPPMM_IGNORE;

    ~Matrix33() = default;

    T* getValue();
    const T* getValue() const CPPMM_RENAME(getValue_const);

    template <class S> void getValue(Imath::Matrix33<S>& v) const CPPMM_IGNORE;
    template <class S>
    Imath::Matrix33<T>& setValue(const Imath::Matrix33<S>& v) CPPMM_IGNORE;

    template <class S>
    Imath::Matrix33<T>& setTheMatrix(const Imath::Matrix33<S>& v) CPPMM_IGNORE;

    void makeIdentity();

    bool operator==(const Imath::Matrix33<T>& v) const;
    bool operator!=(const Imath::Matrix33<T>& v) const;

    bool equalWithAbsError(const Imath::Matrix33<T>& v, T e) const;
    bool equalWithRelError(const Imath::Matrix33<T>& v, T e) const;

    const Imath::Matrix33<T>& operator+=(const Imath::Matrix33<T>& v);
    const Imath::Matrix33<T>& operator+=(T a) CPPMM_RENAME(add_assign_scalar);
    Imath::Matrix33<T> operator+(const Imath::Matrix33<T>& v) const;

    const Imath::Matrix33<T>& operator-=(const Imath::Matrix33<T>& v);
    const Imath::Matrix33<T>& operator-=(T a) CPPMM_RENAME(sub_assign_scalar);
    Imath::Matrix33<T> operator-(const Imath::Matrix33<T>& v) const;

    Imath::Matrix33<T> operator-() const;
    const Imath::Matrix33<T>& negate();

    const Imath::Matrix33<T>& operator*=(T a) CPPMM_RENAME(mul_assign_scalar);
    Imath::Matrix33<T> operator*(T a) const CPPMM_RENAME(mul_scalar);

    const Imath::Matrix33<T>& operator*=(const Imath::Matrix33<T>& v);
    Imath::Matrix33<T> operator*(const Imath::Matrix33<T>& v) const;

    template <class S>
    void multVecMatrix(const Imath::Vec2<S>& src, Imath::Vec2<S>& dst) const;

    template <class S>
    void multDirMatrix(const Imath::Vec2<S>& src, Imath::Vec2<S>& dst) const;

    const Imath::Matrix33<T>& operator/=(T a) CPPMM_RENAME(div_assign_scalar);
    Imath::Matrix33<T> operator/(T a) const CPPMM_RENAME(div_scalar);

    const Imath::Matrix33<T>& transpose();
    Imath::Matrix33<T> transposed() const;

    const Imath::Matrix33<T>& invert(bool singExc = false);

    Imath::Matrix33<T> inverse(bool singExc = false) const;

    const Imath::Matrix33<T>& gjInvert(bool singExc = false);

    Imath::Matrix33<T> gjInverse(bool singExc = false) const;

    T minorOf(const int r, const int c) const;
    T fastMinor(const int r0, const int r1, const int c0, const int c1) const;
    T determinant() const;
    template <class S> const Imath::Matrix33<T>& setRotation(S r);
    template <class S> const Imath::Matrix33<T>& rotate(S r);
    const Imath::Matrix33<T>& setScale(T s);
    template <class S>
    const Imath::Matrix33<T>& setScale(const Imath::Vec2<S>& s);
    template <class S> const Imath::Matrix33<T>& scale(const Imath::Vec2<S>& s);
    template <class S>
    const Imath::Matrix33<T>& setTranslation(const Imath::Vec2<S>& t);
    Imath::Vec2<T> translation() const;
    template <class S>
    const Imath::Matrix33<T>& translate(const Imath::Vec2<S>& t);
    template <class S>
    const Imath::Matrix33<T>& setShear(const S& h)
        CPPMM_RENAME(setShear_scalar);
    template <class S>
    const Imath::Matrix33<T>& setShear(const Imath::Vec2<S>& h);
    template <class S>
    const Imath::Matrix33<T>& shear(const S& xy) CPPMM_RENAME(shear_scalar);
    template <class S> const Imath::Matrix33<T>& shear(const Imath::Vec2<S>& h);

    static unsigned int dimensions();

    static T baseTypeMin();
    static T baseTypeMax();
    static T baseTypeSmallest();
    static T baseTypeEpsilon();

} CPPMM_VALUETYPE;

// explicit instantiation
template class Matrix33<float>;
template class Matrix33<double>;
using M33f = Imath::M33f;
using M33d = Imath::M33d;

template <class T> class Matrix44 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::Imath::Matrix44<T>;

    T* operator[](int i) CPPMM_RENAME(row);
    const T* operator[](int i) const CPPMM_RENAME(row_const);

    //-------------
    // Constructors
    //-------------

    Matrix44(Imath::Uninitialized _unused) CPPMM_RENAME(uninitialized);

    Matrix44() CPPMM_RENAME(identity);
    // 1 0 0 0
    // 0 1 0 0
    // 0 0 1 0
    // 0 0 0 1

    Matrix44(T a) CPPMM_RENAME(broadcast);
    // a a a a
    // a a a a
    // a a a a
    // a a a a

    Matrix44(const T a[4][4]) CPPMM_RENAME(from_array);
    // a[0][0] a[0][1] a[0][2] a[0][3]
    // a[1][0] a[1][1] a[1][2] a[1][3]
    // a[2][0] a[2][1] a[2][2] a[2][3]
    // a[3][0] a[3][1] a[3][2] a[3][3]

    Matrix44(T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k, T l, T m,
             T n, T o, T p);

    // a b c d
    // e f g h
    // i j k l
    // m n o p

    Matrix44(Imath::Matrix33<T> r, Imath::Vec3<T> t)
        CPPMM_RENAME(from_rotation_and_translation);
    // r r r 0
    // r r r 0
    // r r r 0
    // t t t 1

    //------------
    // Destructor
    //------------

    ~Matrix44() = default;

    //--------------------------------
    // Copy constructor and assignment
    //--------------------------------

    Matrix44(const Imath::Matrix44<T>& v);
    template <class S> explicit Matrix44(const Matrix44<S>& v) CPPMM_IGNORE;

    const Imath::Matrix44<T>& operator=(const Imath::Matrix44<T>& v);
    const Imath::Matrix44<T>& operator=(T a) CPPMM_IGNORE;

    T* getValue();
    const T* getValue() const;

    template <class S> void getValue(Imath::Matrix44<S>& v) const CPPMM_IGNORE;
    template <class S>
    Imath::Matrix44<T>& setValue(const Imath::Matrix44<S>& v) CPPMM_IGNORE;

    template <class S>
    Imath::Matrix44<T>& setTheMatrix(const Imath::Matrix44<S>& v) CPPMM_IGNORE;

    void makeIdentity();

    bool operator==(const Imath::Matrix44<T>& v) const;
    bool operator!=(const Imath::Matrix44<T>& v) const;

    bool equalWithAbsError(const Imath::Matrix44<T>& v, T e) const;
    bool equalWithRelError(const Imath::Matrix44<T>& v, T e) const;

    const Imath::Matrix44<T>& operator+=(const Imath::Matrix44<T>& v);
    const Imath::Matrix44<T>& operator+=(T a) CPPMM_RENAME(add_assign_scalar);
    Imath::Matrix44<T> operator+(const Imath::Matrix44<T>& v) const;

    const Imath::Matrix44<T>& operator-=(const Imath::Matrix44<T>& v);
    const Imath::Matrix44<T>& operator-=(T a) CPPMM_RENAME(sub_assign_scalar);
    Imath::Matrix44<T> operator-(const Imath::Matrix44<T>& v) const;

    Imath::Matrix44<T> operator-() const;
    const Imath::Matrix44<T>& negate();

    const Imath::Matrix44<T>& operator*=(T a) CPPMM_RENAME(mul_assign_scalar);
    Imath::Matrix44<T> operator*(T a) const CPPMM_RENAME(mul_scalar);

    const Imath::Matrix44<T>& operator*=(const Imath::Matrix44<T>& v);
    Imath::Matrix44<T> operator*(const Imath::Matrix44<T>& v) const;

    static void multiply(const Imath::Matrix44<T>& a, // assumes that
                         const Imath::Matrix44<T>& b, // &a != &c and
                         Imath::Matrix44<T>& c);      // &b != &c.

    template <class S>
    void multVecMatrix(const Imath::Vec3<S>& src, Imath::Vec3<S>& dst) const;

    template <class S>
    void multDirMatrix(const Imath::Vec3<S>& src, Imath::Vec3<S>& dst) const;

    const Imath::Matrix44<T>& operator/=(T a) CPPMM_RENAME(div_assign_scalar);
    Imath::Matrix44<T> operator/(T a) const CPPMM_RENAME(div_scalar);

    const Imath::Matrix44<T>& transpose();
    Imath::Matrix44<T> transposed() const;

    const Imath::Matrix44<T>& invert(bool singExc = false);
    Imath::Matrix44<T> inverse(bool singExc = false) const;
    const Imath::Matrix44<T>& gjInvert(bool singExc = false);
    Imath::Matrix44<T> gjInverse(bool singExc = false) const;

    T minorOf(const int r, const int c) const;

    T fastMinor(const int r0, const int r1, const int r2, const int c0,
                const int c1, const int c2) const;

    T determinant() const;

    template <class S>
    const Imath::Matrix44<T>& setEulerAngles(const Imath::Vec3<S>& r);

    template <class S>
    const Imath::Matrix44<T>& setAxisAngle(const Imath::Vec3<S>& ax, S ang);

    template <class S>
    const Imath::Matrix44<T>& rotate(const Imath::Vec3<S>& r);
    const Imath::Matrix44<T>& setScale(T s) CPPMM_RENAME(setScale_uniform);
    template <class S>
    const Imath::Matrix44<T>& setScale(const Imath::Vec3<S>& s);

    template <class S> const Imath::Matrix44<T>& scale(const Imath::Vec3<S>& s);

    template <class S> const Matrix44& setTranslation(const Imath::Vec3<S>& t);

    const Imath::Vec3<T> translation() const;

    template <class S>
    const Imath::Matrix44<T>& translate(const Imath::Vec3<S>& t);

    template <class S>
    const Imath::Matrix44<T>& setShear(const Imath::Vec3<S>& h);

    template <class S>
    const Imath::Matrix44<T>& setShear(const Imath::Shear6<S>& h) CPPMM_IGNORE;

    template <class S> const Imath::Matrix44<T>& shear(const Imath::Vec3<S>& h);

    static unsigned int dimensions();

    template <class S>
    const Imath::Matrix44<T>& shear(const Imath::Shear6<S>& h) CPPMM_IGNORE;

    static T baseTypeMin();
    static T baseTypeMax();
    static T baseTypeSmallest();
    static T baseTypeEpsilon();

} CPPMM_VALUETYPE;

// explicit instantiation
template class Matrix44<float>;
template class Matrix44<double>;
using M44f = Imath::M44f;
using M44d = Imath::M44d;
} // namespace IMATH_INTERNAL_NAMESPACE

} // namespace cppmm_bind

template class Imath::Matrix33<float>;
template class Imath::Matrix33<double>;

template class Imath::Matrix44<float>;
template class Imath::Matrix44<double>;
