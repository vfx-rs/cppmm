#include <imath_vec.h>

#include <OpenEXR/ImathVec.h>
#include <cppmm_bind.hpp>
#include <vector>
#include <imath_vec_private.h>


void Imath_2_5_V3f_Vec3(
    Imath_2_5_V3f * self)
{
    new (self) Vec3();
}

void Imath_2_5_V3f_Vec3(
    Imath_2_5_V3f * self
    , Imath_2_5_V3f const * v)
{
    new (self) Vec3(to_cpp_ref(v));
}

void Imath_2_5_V3f_setValue(
    Imath_2_5_V3f * self
    , float a
    , float b
    , float c)
{
    (to_cpp(self)) -> setValue(a, b, c);
}

float Imath_2_5_V3f_dot(
    Imath_2_5_V3f const * self
    , Imath_2_5_V3f const * v)
{
    return (to_cpp(self)) -> dot(to_cpp_ref(v));
}

Imath_2_5_V3f Imath_2_5_V3f_cross(
    Imath_2_5_V3f const * self
    , Imath_2_5_V3f const * v)
{
    return to_c_copy((to_cpp(self)) -> cross(to_cpp_ref(v)));
}

Imath_2_5_V3f const * Imath_2_5_V3f_op_iadd(
    Imath_2_5_V3f * self
    , Imath_2_5_V3f const * v)
{
    return to_c((to_cpp(self)) -> operator+=(to_cpp_ref(v)));
}

float Imath_2_5_V3f_length(
    Imath_2_5_V3f const * self)
{
    return (to_cpp(self)) -> length();
}

float Imath_2_5_V3f_length2(
    Imath_2_5_V3f const * self)
{
    return (to_cpp(self)) -> length2();
}

Imath_2_5_V3f const * Imath_2_5_V3f_normalize(
    Imath_2_5_V3f * self)
{
    return to_c((to_cpp(self)) -> normalize());
}

Imath_2_5_V3f Imath_2_5_V3f_normalized(
    Imath_2_5_V3f const * self)
{
    return to_c_copy((to_cpp(self)) -> normalized());
}
