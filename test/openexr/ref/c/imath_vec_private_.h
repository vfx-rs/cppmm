#pragma once
#include <imath_vec_.h>


#include <OpenEXR/ImathVec.h>
#include <cppmm_bind.hpp>
#include <vector>








































inline Imath_2_5::Vec2<short> const & to_cpp_ref(
    Imath_2_5_V2s const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec2<short> const * >(rhs));
}


inline Imath_2_5::Vec2<short> & to_cpp_ref(
    Imath_2_5_V2s * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec2<short> * >(rhs));
}


inline Imath_2_5::Vec2<short> const * to_cpp(
    Imath_2_5_V2s const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec2<short> const * >(rhs);
}


inline Imath_2_5::Vec2<short> * to_cpp(
    Imath_2_5_V2s * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec2<short> * >(rhs);
}


inline Imath_2_5_V2s const * to_c(
    Imath_2_5::Vec2<short> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V2s const * >(&(rhs));
}


inline Imath_2_5_V2s const * to_c(
    Imath_2_5::Vec2<short> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V2s const * >(rhs);
}


inline Imath_2_5_V2s * to_c(
    Imath_2_5::Vec2<short> & rhs)
{
    return reinterpret_cast<Imath_2_5_V2s * >(&(rhs));
}


inline Imath_2_5_V2s * to_c(
    Imath_2_5::Vec2<short> * rhs)
{
    return reinterpret_cast<Imath_2_5_V2s * >(rhs);
}


inline Imath_2_5_V2s to_c_copy(
    Imath_2_5::Vec2<short> const & rhs)
{
    Imath_2_5_V2s result;
    Imath_2_5_V2s_Vec2_3(&(result), reinterpret_cast<Imath_2_5_V2s const * >(&(rhs)));
    return result;
}








































inline Imath_2_5::Vec2<int> const & to_cpp_ref(
    Imath_2_5_V2i const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec2<int> const * >(rhs));
}


inline Imath_2_5::Vec2<int> & to_cpp_ref(
    Imath_2_5_V2i * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec2<int> * >(rhs));
}


inline Imath_2_5::Vec2<int> const * to_cpp(
    Imath_2_5_V2i const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec2<int> const * >(rhs);
}


inline Imath_2_5::Vec2<int> * to_cpp(
    Imath_2_5_V2i * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec2<int> * >(rhs);
}


inline Imath_2_5_V2i const * to_c(
    Imath_2_5::Vec2<int> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V2i const * >(&(rhs));
}


inline Imath_2_5_V2i const * to_c(
    Imath_2_5::Vec2<int> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V2i const * >(rhs);
}


inline Imath_2_5_V2i * to_c(
    Imath_2_5::Vec2<int> & rhs)
{
    return reinterpret_cast<Imath_2_5_V2i * >(&(rhs));
}


inline Imath_2_5_V2i * to_c(
    Imath_2_5::Vec2<int> * rhs)
{
    return reinterpret_cast<Imath_2_5_V2i * >(rhs);
}


inline Imath_2_5_V2i to_c_copy(
    Imath_2_5::Vec2<int> const & rhs)
{
    Imath_2_5_V2i result;
    Imath_2_5_V2i_Vec2_3(&(result), reinterpret_cast<Imath_2_5_V2i const * >(&(rhs)));
    return result;
}








































inline Imath_2_5::Vec2<float> const & to_cpp_ref(
    Imath_2_5_V2f const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec2<float> const * >(rhs));
}


inline Imath_2_5::Vec2<float> & to_cpp_ref(
    Imath_2_5_V2f * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec2<float> * >(rhs));
}


inline Imath_2_5::Vec2<float> const * to_cpp(
    Imath_2_5_V2f const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec2<float> const * >(rhs);
}


inline Imath_2_5::Vec2<float> * to_cpp(
    Imath_2_5_V2f * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec2<float> * >(rhs);
}


inline Imath_2_5_V2f const * to_c(
    Imath_2_5::Vec2<float> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V2f const * >(&(rhs));
}


inline Imath_2_5_V2f const * to_c(
    Imath_2_5::Vec2<float> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V2f const * >(rhs);
}


inline Imath_2_5_V2f * to_c(
    Imath_2_5::Vec2<float> & rhs)
{
    return reinterpret_cast<Imath_2_5_V2f * >(&(rhs));
}


inline Imath_2_5_V2f * to_c(
    Imath_2_5::Vec2<float> * rhs)
{
    return reinterpret_cast<Imath_2_5_V2f * >(rhs);
}


inline Imath_2_5_V2f to_c_copy(
    Imath_2_5::Vec2<float> const & rhs)
{
    Imath_2_5_V2f result;
    Imath_2_5_V2f_Vec2_3(&(result), reinterpret_cast<Imath_2_5_V2f const * >(&(rhs)));
    return result;
}








































inline Imath_2_5::Vec2<double> const & to_cpp_ref(
    Imath_2_5_V2d const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec2<double> const * >(rhs));
}


inline Imath_2_5::Vec2<double> & to_cpp_ref(
    Imath_2_5_V2d * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec2<double> * >(rhs));
}


inline Imath_2_5::Vec2<double> const * to_cpp(
    Imath_2_5_V2d const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec2<double> const * >(rhs);
}


inline Imath_2_5::Vec2<double> * to_cpp(
    Imath_2_5_V2d * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec2<double> * >(rhs);
}


inline Imath_2_5_V2d const * to_c(
    Imath_2_5::Vec2<double> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V2d const * >(&(rhs));
}


inline Imath_2_5_V2d const * to_c(
    Imath_2_5::Vec2<double> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V2d const * >(rhs);
}


inline Imath_2_5_V2d * to_c(
    Imath_2_5::Vec2<double> & rhs)
{
    return reinterpret_cast<Imath_2_5_V2d * >(&(rhs));
}


inline Imath_2_5_V2d * to_c(
    Imath_2_5::Vec2<double> * rhs)
{
    return reinterpret_cast<Imath_2_5_V2d * >(rhs);
}


inline Imath_2_5_V2d to_c_copy(
    Imath_2_5::Vec2<double> const & rhs)
{
    Imath_2_5_V2d result;
    Imath_2_5_V2d_Vec2_3(&(result), reinterpret_cast<Imath_2_5_V2d const * >(&(rhs)));
    return result;
}




inline Imath_2_5::Vec3<short> const & to_cpp_ref(
    Imath_2_5_V3s const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<short> const * >(rhs));
}


inline Imath_2_5::Vec3<short> & to_cpp_ref(
    Imath_2_5_V3s * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<short> * >(rhs));
}


inline Imath_2_5::Vec3<short> const * to_cpp(
    Imath_2_5_V3s const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<short> const * >(rhs);
}


inline Imath_2_5::Vec3<short> * to_cpp(
    Imath_2_5_V3s * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<short> * >(rhs);
}


inline Imath_2_5_V3s const * to_c(
    Imath_2_5::Vec3<short> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V3s const * >(&(rhs));
}


inline Imath_2_5_V3s const * to_c(
    Imath_2_5::Vec3<short> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V3s const * >(rhs);
}


inline Imath_2_5_V3s * to_c(
    Imath_2_5::Vec3<short> & rhs)
{
    return reinterpret_cast<Imath_2_5_V3s * >(&(rhs));
}


inline Imath_2_5_V3s * to_c(
    Imath_2_5::Vec3<short> * rhs)
{
    return reinterpret_cast<Imath_2_5_V3s * >(rhs);
}


inline Imath_2_5_V3s to_c_copy(
    Imath_2_5::Vec3<short> const & rhs)
{
    Imath_2_5_V3s result;
    Imath_2_5_V3s_Vec3_1(&(result), reinterpret_cast<Imath_2_5_V3s const * >(&(rhs)));
    return result;
}




inline Imath_2_5::Vec3<int> const & to_cpp_ref(
    Imath_2_5_V3i const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<int> const * >(rhs));
}


inline Imath_2_5::Vec3<int> & to_cpp_ref(
    Imath_2_5_V3i * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<int> * >(rhs));
}


inline Imath_2_5::Vec3<int> const * to_cpp(
    Imath_2_5_V3i const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<int> const * >(rhs);
}


inline Imath_2_5::Vec3<int> * to_cpp(
    Imath_2_5_V3i * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<int> * >(rhs);
}


inline Imath_2_5_V3i const * to_c(
    Imath_2_5::Vec3<int> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V3i const * >(&(rhs));
}


inline Imath_2_5_V3i const * to_c(
    Imath_2_5::Vec3<int> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V3i const * >(rhs);
}


inline Imath_2_5_V3i * to_c(
    Imath_2_5::Vec3<int> & rhs)
{
    return reinterpret_cast<Imath_2_5_V3i * >(&(rhs));
}


inline Imath_2_5_V3i * to_c(
    Imath_2_5::Vec3<int> * rhs)
{
    return reinterpret_cast<Imath_2_5_V3i * >(rhs);
}


inline Imath_2_5_V3i to_c_copy(
    Imath_2_5::Vec3<int> const & rhs)
{
    Imath_2_5_V3i result;
    Imath_2_5_V3i_Vec3_1(&(result), reinterpret_cast<Imath_2_5_V3i const * >(&(rhs)));
    return result;
}




inline Imath_2_5::Vec3<float> const & to_cpp_ref(
    Imath_2_5_V3f const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<float> const * >(rhs));
}


inline Imath_2_5::Vec3<float> & to_cpp_ref(
    Imath_2_5_V3f * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<float> * >(rhs));
}


inline Imath_2_5::Vec3<float> const * to_cpp(
    Imath_2_5_V3f const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<float> const * >(rhs);
}


inline Imath_2_5::Vec3<float> * to_cpp(
    Imath_2_5_V3f * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<float> * >(rhs);
}


inline Imath_2_5_V3f const * to_c(
    Imath_2_5::Vec3<float> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V3f const * >(&(rhs));
}


inline Imath_2_5_V3f const * to_c(
    Imath_2_5::Vec3<float> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V3f const * >(rhs);
}


inline Imath_2_5_V3f * to_c(
    Imath_2_5::Vec3<float> & rhs)
{
    return reinterpret_cast<Imath_2_5_V3f * >(&(rhs));
}


inline Imath_2_5_V3f * to_c(
    Imath_2_5::Vec3<float> * rhs)
{
    return reinterpret_cast<Imath_2_5_V3f * >(rhs);
}


inline Imath_2_5_V3f to_c_copy(
    Imath_2_5::Vec3<float> const & rhs)
{
    Imath_2_5_V3f result;
    Imath_2_5_V3f_Vec3_1(&(result), reinterpret_cast<Imath_2_5_V3f const * >(&(rhs)));
    return result;
}




inline Imath_2_5::Vec3<double> const & to_cpp_ref(
    Imath_2_5_V3d const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<double> const * >(rhs));
}


inline Imath_2_5::Vec3<double> & to_cpp_ref(
    Imath_2_5_V3d * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<double> * >(rhs));
}


inline Imath_2_5::Vec3<double> const * to_cpp(
    Imath_2_5_V3d const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<double> const * >(rhs);
}


inline Imath_2_5::Vec3<double> * to_cpp(
    Imath_2_5_V3d * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<double> * >(rhs);
}


inline Imath_2_5_V3d const * to_c(
    Imath_2_5::Vec3<double> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V3d const * >(&(rhs));
}


inline Imath_2_5_V3d const * to_c(
    Imath_2_5::Vec3<double> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V3d const * >(rhs);
}


inline Imath_2_5_V3d * to_c(
    Imath_2_5::Vec3<double> & rhs)
{
    return reinterpret_cast<Imath_2_5_V3d * >(&(rhs));
}


inline Imath_2_5_V3d * to_c(
    Imath_2_5::Vec3<double> * rhs)
{
    return reinterpret_cast<Imath_2_5_V3d * >(rhs);
}


inline Imath_2_5_V3d to_c_copy(
    Imath_2_5::Vec3<double> const & rhs)
{
    Imath_2_5_V3d result;
    Imath_2_5_V3d_Vec3_1(&(result), reinterpret_cast<Imath_2_5_V3d const * >(&(rhs)));
    return result;
}




inline Imath_2_5::Vec4<short> const & to_cpp_ref(
    Imath_2_5_V4s const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec4<short> const * >(rhs));
}


inline Imath_2_5::Vec4<short> & to_cpp_ref(
    Imath_2_5_V4s * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec4<short> * >(rhs));
}


inline Imath_2_5::Vec4<short> const * to_cpp(
    Imath_2_5_V4s const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec4<short> const * >(rhs);
}


inline Imath_2_5::Vec4<short> * to_cpp(
    Imath_2_5_V4s * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec4<short> * >(rhs);
}


inline Imath_2_5_V4s const * to_c(
    Imath_2_5::Vec4<short> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V4s const * >(&(rhs));
}


inline Imath_2_5_V4s const * to_c(
    Imath_2_5::Vec4<short> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V4s const * >(rhs);
}


inline Imath_2_5_V4s * to_c(
    Imath_2_5::Vec4<short> & rhs)
{
    return reinterpret_cast<Imath_2_5_V4s * >(&(rhs));
}


inline Imath_2_5_V4s * to_c(
    Imath_2_5::Vec4<short> * rhs)
{
    return reinterpret_cast<Imath_2_5_V4s * >(rhs);
}


inline Imath_2_5_V4s to_c_copy(
    Imath_2_5::Vec4<short> const & rhs)
{
    Imath_2_5_V4s result;
    Imath_2_5_V4s_Vec4_1(&(result), reinterpret_cast<Imath_2_5_V4s const * >(&(rhs)));
    return result;
}




inline Imath_2_5::Vec4<int> const & to_cpp_ref(
    Imath_2_5_V4i const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec4<int> const * >(rhs));
}


inline Imath_2_5::Vec4<int> & to_cpp_ref(
    Imath_2_5_V4i * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec4<int> * >(rhs));
}


inline Imath_2_5::Vec4<int> const * to_cpp(
    Imath_2_5_V4i const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec4<int> const * >(rhs);
}


inline Imath_2_5::Vec4<int> * to_cpp(
    Imath_2_5_V4i * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec4<int> * >(rhs);
}


inline Imath_2_5_V4i const * to_c(
    Imath_2_5::Vec4<int> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V4i const * >(&(rhs));
}


inline Imath_2_5_V4i const * to_c(
    Imath_2_5::Vec4<int> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V4i const * >(rhs);
}


inline Imath_2_5_V4i * to_c(
    Imath_2_5::Vec4<int> & rhs)
{
    return reinterpret_cast<Imath_2_5_V4i * >(&(rhs));
}


inline Imath_2_5_V4i * to_c(
    Imath_2_5::Vec4<int> * rhs)
{
    return reinterpret_cast<Imath_2_5_V4i * >(rhs);
}


inline Imath_2_5_V4i to_c_copy(
    Imath_2_5::Vec4<int> const & rhs)
{
    Imath_2_5_V4i result;
    Imath_2_5_V4i_Vec4_1(&(result), reinterpret_cast<Imath_2_5_V4i const * >(&(rhs)));
    return result;
}




inline Imath_2_5::Vec4<float> const & to_cpp_ref(
    Imath_2_5_V4f const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec4<float> const * >(rhs));
}


inline Imath_2_5::Vec4<float> & to_cpp_ref(
    Imath_2_5_V4f * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec4<float> * >(rhs));
}


inline Imath_2_5::Vec4<float> const * to_cpp(
    Imath_2_5_V4f const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec4<float> const * >(rhs);
}


inline Imath_2_5::Vec4<float> * to_cpp(
    Imath_2_5_V4f * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec4<float> * >(rhs);
}


inline Imath_2_5_V4f const * to_c(
    Imath_2_5::Vec4<float> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V4f const * >(&(rhs));
}


inline Imath_2_5_V4f const * to_c(
    Imath_2_5::Vec4<float> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V4f const * >(rhs);
}


inline Imath_2_5_V4f * to_c(
    Imath_2_5::Vec4<float> & rhs)
{
    return reinterpret_cast<Imath_2_5_V4f * >(&(rhs));
}


inline Imath_2_5_V4f * to_c(
    Imath_2_5::Vec4<float> * rhs)
{
    return reinterpret_cast<Imath_2_5_V4f * >(rhs);
}


inline Imath_2_5_V4f to_c_copy(
    Imath_2_5::Vec4<float> const & rhs)
{
    Imath_2_5_V4f result;
    Imath_2_5_V4f_Vec4_1(&(result), reinterpret_cast<Imath_2_5_V4f const * >(&(rhs)));
    return result;
}




inline Imath_2_5::Vec4<double> const & to_cpp_ref(
    Imath_2_5_V4d const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec4<double> const * >(rhs));
}


inline Imath_2_5::Vec4<double> & to_cpp_ref(
    Imath_2_5_V4d * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec4<double> * >(rhs));
}


inline Imath_2_5::Vec4<double> const * to_cpp(
    Imath_2_5_V4d const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec4<double> const * >(rhs);
}


inline Imath_2_5::Vec4<double> * to_cpp(
    Imath_2_5_V4d * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec4<double> * >(rhs);
}


inline Imath_2_5_V4d const * to_c(
    Imath_2_5::Vec4<double> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V4d const * >(&(rhs));
}


inline Imath_2_5_V4d const * to_c(
    Imath_2_5::Vec4<double> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V4d const * >(rhs);
}


inline Imath_2_5_V4d * to_c(
    Imath_2_5::Vec4<double> & rhs)
{
    return reinterpret_cast<Imath_2_5_V4d * >(&(rhs));
}


inline Imath_2_5_V4d * to_c(
    Imath_2_5::Vec4<double> * rhs)
{
    return reinterpret_cast<Imath_2_5_V4d * >(rhs);
}


inline Imath_2_5_V4d to_c_copy(
    Imath_2_5::Vec4<double> const & rhs)
{
    Imath_2_5_V4d result;
    Imath_2_5_V4d_Vec4_1(&(result), reinterpret_cast<Imath_2_5_V4d const * >(&(rhs)));
    return result;
}
