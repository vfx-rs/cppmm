#include <OpenEXR/ImathVec.h>

#include <vector>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

template <class T> class Vec2 {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::Imath::Vec2<T>;

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
    using BoundType = ::Imath::Vec3<T>;

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
    using BoundType = ::Imath::Vec4<T>;

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
