#include <OpenEXR/ImathMatrix.h>

#include <vector>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

template <class T> class Matrix33 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::Imath::Matrix33<T>;

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

} CPPMM_VALUETYPE;

// explicit instantiation
template class Matrix44<float>;
template class Matrix44<double>;
using M44f = Imath::M44f;
using M44d = Imath::M44d;

} // namespace cppmm_bind

template class Imath::Matrix33<float>;
template class Imath::Matrix33<double>;

template class Imath::Matrix44<float>;
template class Imath::Matrix44<double>;
