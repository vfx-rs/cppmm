#pragma once
#include <imath_box_.h>


#include <OpenEXR/ImathBox.h>
#include <cppmm_bind.hpp>
















inline Imath_2_5::Box<Imath_2_5::Vec2<short> > const & to_cpp_ref(
    Imath_2_5_Box2s const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<short> > const * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec2<short> > & to_cpp_ref(
    Imath_2_5_Box2s * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<short> > * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec2<short> > const * to_cpp(
    Imath_2_5_Box2s const * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<short> > const * >(rhs);
}


inline Imath_2_5::Box<Imath_2_5::Vec2<short> > * to_cpp(
    Imath_2_5_Box2s * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<short> > * >(rhs);
}


inline Imath_2_5_Box2s const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<short> > const & rhs)
{
    return reinterpret_cast<Imath_2_5_Box2s const * >(&(rhs));
}


inline Imath_2_5_Box2s const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<short> > const * rhs)
{
    return reinterpret_cast<Imath_2_5_Box2s const * >(rhs);
}


inline Imath_2_5_Box2s * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<short> > & rhs)
{
    return reinterpret_cast<Imath_2_5_Box2s * >(&(rhs));
}


inline Imath_2_5_Box2s * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<short> > * rhs)
{
    return reinterpret_cast<Imath_2_5_Box2s * >(rhs);
}


inline Imath_2_5_Box2s to_c_copy(
    Imath_2_5::Box<Imath_2_5::Vec2<short> > const & rhs)
{
    Imath_2_5_Box2s result;
    Imath_2_5_Box2s_Box_3(&(result), reinterpret_cast<Imath_2_5_Box2s const * >(&(rhs)));
    return result;
}
















inline Imath_2_5::Box<Imath_2_5::Vec2<int> > const & to_cpp_ref(
    Imath_2_5_Box2i const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<int> > const * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec2<int> > & to_cpp_ref(
    Imath_2_5_Box2i * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<int> > * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec2<int> > const * to_cpp(
    Imath_2_5_Box2i const * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<int> > const * >(rhs);
}


inline Imath_2_5::Box<Imath_2_5::Vec2<int> > * to_cpp(
    Imath_2_5_Box2i * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<int> > * >(rhs);
}


inline Imath_2_5_Box2i const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<int> > const & rhs)
{
    return reinterpret_cast<Imath_2_5_Box2i const * >(&(rhs));
}


inline Imath_2_5_Box2i const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<int> > const * rhs)
{
    return reinterpret_cast<Imath_2_5_Box2i const * >(rhs);
}


inline Imath_2_5_Box2i * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<int> > & rhs)
{
    return reinterpret_cast<Imath_2_5_Box2i * >(&(rhs));
}


inline Imath_2_5_Box2i * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<int> > * rhs)
{
    return reinterpret_cast<Imath_2_5_Box2i * >(rhs);
}


inline Imath_2_5_Box2i to_c_copy(
    Imath_2_5::Box<Imath_2_5::Vec2<int> > const & rhs)
{
    Imath_2_5_Box2i result;
    Imath_2_5_Box2i_Box_3(&(result), reinterpret_cast<Imath_2_5_Box2i const * >(&(rhs)));
    return result;
}
















inline Imath_2_5::Box<Imath_2_5::Vec2<float> > const & to_cpp_ref(
    Imath_2_5_Box2f const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<float> > const * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec2<float> > & to_cpp_ref(
    Imath_2_5_Box2f * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<float> > * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec2<float> > const * to_cpp(
    Imath_2_5_Box2f const * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<float> > const * >(rhs);
}


inline Imath_2_5::Box<Imath_2_5::Vec2<float> > * to_cpp(
    Imath_2_5_Box2f * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<float> > * >(rhs);
}


inline Imath_2_5_Box2f const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<float> > const & rhs)
{
    return reinterpret_cast<Imath_2_5_Box2f const * >(&(rhs));
}


inline Imath_2_5_Box2f const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<float> > const * rhs)
{
    return reinterpret_cast<Imath_2_5_Box2f const * >(rhs);
}


inline Imath_2_5_Box2f * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<float> > & rhs)
{
    return reinterpret_cast<Imath_2_5_Box2f * >(&(rhs));
}


inline Imath_2_5_Box2f * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<float> > * rhs)
{
    return reinterpret_cast<Imath_2_5_Box2f * >(rhs);
}


inline Imath_2_5_Box2f to_c_copy(
    Imath_2_5::Box<Imath_2_5::Vec2<float> > const & rhs)
{
    Imath_2_5_Box2f result;
    Imath_2_5_Box2f_Box_3(&(result), reinterpret_cast<Imath_2_5_Box2f const * >(&(rhs)));
    return result;
}
















inline Imath_2_5::Box<Imath_2_5::Vec2<double> > const & to_cpp_ref(
    Imath_2_5_Box2d const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<double> > const * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec2<double> > & to_cpp_ref(
    Imath_2_5_Box2d * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<double> > * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec2<double> > const * to_cpp(
    Imath_2_5_Box2d const * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<double> > const * >(rhs);
}


inline Imath_2_5::Box<Imath_2_5::Vec2<double> > * to_cpp(
    Imath_2_5_Box2d * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec2<double> > * >(rhs);
}


inline Imath_2_5_Box2d const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<double> > const & rhs)
{
    return reinterpret_cast<Imath_2_5_Box2d const * >(&(rhs));
}


inline Imath_2_5_Box2d const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<double> > const * rhs)
{
    return reinterpret_cast<Imath_2_5_Box2d const * >(rhs);
}


inline Imath_2_5_Box2d * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<double> > & rhs)
{
    return reinterpret_cast<Imath_2_5_Box2d * >(&(rhs));
}


inline Imath_2_5_Box2d * to_c(
    Imath_2_5::Box<Imath_2_5::Vec2<double> > * rhs)
{
    return reinterpret_cast<Imath_2_5_Box2d * >(rhs);
}


inline Imath_2_5_Box2d to_c_copy(
    Imath_2_5::Box<Imath_2_5::Vec2<double> > const & rhs)
{
    Imath_2_5_Box2d result;
    Imath_2_5_Box2d_Box_3(&(result), reinterpret_cast<Imath_2_5_Box2d const * >(&(rhs)));
    return result;
}
















inline Imath_2_5::Box<Imath_2_5::Vec3<short> > const & to_cpp_ref(
    Imath_2_5_Box3s const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<short> > const * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec3<short> > & to_cpp_ref(
    Imath_2_5_Box3s * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<short> > * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec3<short> > const * to_cpp(
    Imath_2_5_Box3s const * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<short> > const * >(rhs);
}


inline Imath_2_5::Box<Imath_2_5::Vec3<short> > * to_cpp(
    Imath_2_5_Box3s * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<short> > * >(rhs);
}


inline Imath_2_5_Box3s const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<short> > const & rhs)
{
    return reinterpret_cast<Imath_2_5_Box3s const * >(&(rhs));
}


inline Imath_2_5_Box3s const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<short> > const * rhs)
{
    return reinterpret_cast<Imath_2_5_Box3s const * >(rhs);
}


inline Imath_2_5_Box3s * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<short> > & rhs)
{
    return reinterpret_cast<Imath_2_5_Box3s * >(&(rhs));
}


inline Imath_2_5_Box3s * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<short> > * rhs)
{
    return reinterpret_cast<Imath_2_5_Box3s * >(rhs);
}


inline Imath_2_5_Box3s to_c_copy(
    Imath_2_5::Box<Imath_2_5::Vec3<short> > const & rhs)
{
    Imath_2_5_Box3s result;
    Imath_2_5_Box3s_Box_3(&(result), reinterpret_cast<Imath_2_5_Box3s const * >(&(rhs)));
    return result;
}
















inline Imath_2_5::Box<Imath_2_5::Vec3<int> > const & to_cpp_ref(
    Imath_2_5_Box3i const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<int> > const * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec3<int> > & to_cpp_ref(
    Imath_2_5_Box3i * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<int> > * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec3<int> > const * to_cpp(
    Imath_2_5_Box3i const * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<int> > const * >(rhs);
}


inline Imath_2_5::Box<Imath_2_5::Vec3<int> > * to_cpp(
    Imath_2_5_Box3i * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<int> > * >(rhs);
}


inline Imath_2_5_Box3i const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<int> > const & rhs)
{
    return reinterpret_cast<Imath_2_5_Box3i const * >(&(rhs));
}


inline Imath_2_5_Box3i const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<int> > const * rhs)
{
    return reinterpret_cast<Imath_2_5_Box3i const * >(rhs);
}


inline Imath_2_5_Box3i * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<int> > & rhs)
{
    return reinterpret_cast<Imath_2_5_Box3i * >(&(rhs));
}


inline Imath_2_5_Box3i * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<int> > * rhs)
{
    return reinterpret_cast<Imath_2_5_Box3i * >(rhs);
}


inline Imath_2_5_Box3i to_c_copy(
    Imath_2_5::Box<Imath_2_5::Vec3<int> > const & rhs)
{
    Imath_2_5_Box3i result;
    Imath_2_5_Box3i_Box_3(&(result), reinterpret_cast<Imath_2_5_Box3i const * >(&(rhs)));
    return result;
}
















inline Imath_2_5::Box<Imath_2_5::Vec3<float> > const & to_cpp_ref(
    Imath_2_5_Box3f const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<float> > const * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec3<float> > & to_cpp_ref(
    Imath_2_5_Box3f * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<float> > * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec3<float> > const * to_cpp(
    Imath_2_5_Box3f const * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<float> > const * >(rhs);
}


inline Imath_2_5::Box<Imath_2_5::Vec3<float> > * to_cpp(
    Imath_2_5_Box3f * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<float> > * >(rhs);
}


inline Imath_2_5_Box3f const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<float> > const & rhs)
{
    return reinterpret_cast<Imath_2_5_Box3f const * >(&(rhs));
}


inline Imath_2_5_Box3f const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<float> > const * rhs)
{
    return reinterpret_cast<Imath_2_5_Box3f const * >(rhs);
}


inline Imath_2_5_Box3f * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<float> > & rhs)
{
    return reinterpret_cast<Imath_2_5_Box3f * >(&(rhs));
}


inline Imath_2_5_Box3f * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<float> > * rhs)
{
    return reinterpret_cast<Imath_2_5_Box3f * >(rhs);
}


inline Imath_2_5_Box3f to_c_copy(
    Imath_2_5::Box<Imath_2_5::Vec3<float> > const & rhs)
{
    Imath_2_5_Box3f result;
    Imath_2_5_Box3f_Box_3(&(result), reinterpret_cast<Imath_2_5_Box3f const * >(&(rhs)));
    return result;
}
















inline Imath_2_5::Box<Imath_2_5::Vec3<double> > const & to_cpp_ref(
    Imath_2_5_Box3d const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<double> > const * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec3<double> > & to_cpp_ref(
    Imath_2_5_Box3d * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<double> > * >(rhs));
}


inline Imath_2_5::Box<Imath_2_5::Vec3<double> > const * to_cpp(
    Imath_2_5_Box3d const * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<double> > const * >(rhs);
}


inline Imath_2_5::Box<Imath_2_5::Vec3<double> > * to_cpp(
    Imath_2_5_Box3d * rhs)
{
    return reinterpret_cast<Imath_2_5::Box<Imath_2_5::Vec3<double> > * >(rhs);
}


inline Imath_2_5_Box3d const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<double> > const & rhs)
{
    return reinterpret_cast<Imath_2_5_Box3d const * >(&(rhs));
}


inline Imath_2_5_Box3d const * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<double> > const * rhs)
{
    return reinterpret_cast<Imath_2_5_Box3d const * >(rhs);
}


inline Imath_2_5_Box3d * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<double> > & rhs)
{
    return reinterpret_cast<Imath_2_5_Box3d * >(&(rhs));
}


inline Imath_2_5_Box3d * to_c(
    Imath_2_5::Box<Imath_2_5::Vec3<double> > * rhs)
{
    return reinterpret_cast<Imath_2_5_Box3d * >(rhs);
}


inline Imath_2_5_Box3d to_c_copy(
    Imath_2_5::Box<Imath_2_5::Vec3<double> > const & rhs)
{
    Imath_2_5_Box3d result;
    Imath_2_5_Box3d_Box_3(&(result), reinterpret_cast<Imath_2_5_Box3d const * >(&(rhs)));
    return result;
}
