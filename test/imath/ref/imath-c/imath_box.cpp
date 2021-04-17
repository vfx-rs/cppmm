#include <imath_box_private.h>

#include <imath_vec_private.h>


void Imath_2_5__Box_Imath__Vec3_float___extendBy(
    Imath_Box3f_t * this_
    , Imath_V3f_t const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5__Box_Imath__Vec3_float___extendBy_1(
    Imath_Box3f_t * this_
    , Imath_Box3f_t const * box)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(box));
}

void Imath_2_5__Box_Imath__Vec3_int___extendBy(
    Imath_Box3i_t * this_
    , Imath_V3i_t const * point)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5__Box_Imath__Vec3_int___extendBy_1(
    Imath_Box3i_t * this_
    , Imath_Box3i_t const * box)
{
    (to_cpp(this_)) -> extendBy(to_cpp_ref(box));
}
