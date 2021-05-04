#include <imath_vec_private.h>

#include <new>

#include <stdexcept>

unsigned int Imath_2_5__Vec3_float__Vec3(
    Imath_V3f_t * this_)
{
    try {
        new (this_) Imath_2_5::Vec3<float>();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_float__Vec3_1(
    Imath_V3f_t * this_
    , Imath_V3f_t const * rhs)
{
    try {
        new (this_) Imath_2_5::Vec3<float>(to_cpp_ref(rhs));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_float__setValue(
    Imath_V3f_t * this_
    , float a
    , float b
    , float c)
{
    try {
        (to_cpp(this_)) -> setValue<float>(a, b, c);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_float__dot(
    Imath_V3f_t const * this_
    , float * return_
    , Imath_V3f_t const * v)
{
    try {
        *(return_) = (to_cpp(this_)) -> dot(to_cpp_ref(v));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_float__cross(
    Imath_V3f_t const * this_
    , Imath_V3f_t * return_
    , Imath_V3f_t const * v)
{
    try {
        to_c_copy(return_, (to_cpp(this_)) -> cross(to_cpp_ref(v)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_float__op_iadd(
    Imath_V3f_t * this_
    , Imath_V3f_t const * * return_
    , Imath_V3f_t const * v)
{
    try {
        to_c(return_, (to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_float__length(
    Imath_V3f_t const * this_
    , float * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> length();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_float__length2(
    Imath_V3f_t const * this_
    , float * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> length2();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_float__normalize(
    Imath_V3f_t * this_
    , Imath_V3f_t const * * return_)
{
    try {
        to_c(return_, (to_cpp(this_)) -> normalize());
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_float__normalized(
    Imath_V3f_t const * this_
    , Imath_V3f_t * return_)
{
    try {
        to_c_copy(return_, (to_cpp(this_)) -> normalized());
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_int__Vec3(
    Imath_V3i_t * this_)
{
    try {
        new (this_) Imath_2_5::Vec3<int>();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_int__Vec3_1(
    Imath_V3i_t * this_
    , Imath_V3i_t const * rhs)
{
    try {
        new (this_) Imath_2_5::Vec3<int>(to_cpp_ref(rhs));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_int__dot(
    Imath_V3i_t const * this_
    , int * return_
    , Imath_V3i_t const * v)
{
    try {
        *(return_) = (to_cpp(this_)) -> dot(to_cpp_ref(v));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_int__cross(
    Imath_V3i_t const * this_
    , Imath_V3i_t * return_
    , Imath_V3i_t const * v)
{
    try {
        to_c_copy(return_, (to_cpp(this_)) -> cross(to_cpp_ref(v)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_int__op_iadd(
    Imath_V3i_t * this_
    , Imath_V3i_t const * * return_
    , Imath_V3i_t const * v)
{
    try {
        to_c(return_, (to_cpp(this_)) -> operator+=(to_cpp_ref(v)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_int__length(
    Imath_V3i_t const * this_
    , int * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> length();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_int__length2(
    Imath_V3i_t const * this_
    , int * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> length2();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_int__normalize(
    Imath_V3i_t * this_
    , Imath_V3i_t const * * return_)
{
    try {
        to_c(return_, (to_cpp(this_)) -> normalize());
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int Imath_2_5__Vec3_int__normalized(
    Imath_V3i_t const * this_
    , Imath_V3i_t * return_)
{
    try {
        to_c_copy(return_, (to_cpp(this_)) -> normalized());
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
