#include <imath_vec_private.h>

#include <new>


void Imath_2_5__Vec3_float__Vec3(
    Imath_V3f_t * this_)
{
    new (this_) Imath_2_5::Vec3<float>();
}

void Imath_2_5__Vec3_float__Vec3_1(
    Imath_V3f_t * this_
    , Imath_V3f_t const * rhs)
{
    new (this_) Imath_2_5::Vec3<float>(to_cpp_ref(rhs));
}

void Imath_2_5__Vec3_float__setValue(
    Imath_V3f_t * this_
    , float a
    , float b
    , float c)
{
    (to_cpp(this_)) -> setValue(a, b, c);
}

float Imath_2_5__Vec3_float__dot(
    Imath_V3f_t const * this_
    , Imath_V3f_t const * v)
{
    return (to_cpp(this_)) -> dot(to_cpp_ref(v));
}

Imath_V3f_t Imath_2_5__Vec3_float__cross(
    Imath_V3f_t const * this_
    , Imath_V3f_t const * v)
{
    return to_c_copy((to_cpp(this_)) -> cross(to_cpp_ref(v)));
}

Imath_V3f_t const * Imath_2_5__Vec3_float__op_iadd(
    Imath_V3f_t * this_
    , Imath_V3f_t const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

float Imath_2_5__Vec3_float__length(
    Imath_V3f_t const * this_)
{
    return (to_cpp(this_)) -> length();
}

float Imath_2_5__Vec3_float__length2(
    Imath_V3f_t const * this_)
{
    return (to_cpp(this_)) -> length2();
}

Imath_V3f_t const * Imath_2_5__Vec3_float__normalize(
    Imath_V3f_t * this_)
{
    return to_c((to_cpp(this_)) -> normalize());
}

Imath_V3f_t Imath_2_5__Vec3_float__normalized(
    Imath_V3f_t const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalized());
}

void Imath_2_5__Vec3_int__Vec3(
    Imath_V3i_t * this_)
{
    new (this_) Imath_2_5::Vec3<int>();
}

void Imath_2_5__Vec3_int__Vec3_1(
    Imath_V3i_t * this_
    , Imath_V3i_t const * rhs)
{
    new (this_) Imath_2_5::Vec3<int>(to_cpp_ref(rhs));
}

int Imath_2_5__Vec3_int__dot(
    Imath_V3i_t const * this_
    , Imath_V3i_t const * v)
{
    return (to_cpp(this_)) -> dot(to_cpp_ref(v));
}

Imath_V3i_t Imath_2_5__Vec3_int__cross(
    Imath_V3i_t const * this_
    , Imath_V3i_t const * v)
{
    return to_c_copy((to_cpp(this_)) -> cross(to_cpp_ref(v)));
}

Imath_V3i_t const * Imath_2_5__Vec3_int__op_iadd(
    Imath_V3i_t * this_
    , Imath_V3i_t const * v)
{
    return to_c((to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
}

int Imath_2_5__Vec3_int__length(
    Imath_V3i_t const * this_)
{
    return (to_cpp(this_)) -> length();
}

int Imath_2_5__Vec3_int__length2(
    Imath_V3i_t const * this_)
{
    return (to_cpp(this_)) -> length2();
}

Imath_V3i_t const * Imath_2_5__Vec3_int__normalize(
    Imath_V3i_t * this_)
{
    return to_c((to_cpp(this_)) -> normalize());
}

Imath_V3i_t Imath_2_5__Vec3_int__normalized(
    Imath_V3i_t const * this_)
{
    return to_c_copy((to_cpp(this_)) -> normalized());
}
