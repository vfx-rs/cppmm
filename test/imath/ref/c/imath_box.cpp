#include <imath_box.h>

#include <OpenEXR/ImathBox.h>
#include <cppmm_bind.hpp>
#include <imath_vec.h>
#include <imath_vec_private.h>
#include <imath_box_private.h>


void Imath_2_5_Box3f_extendBy(
    Imath_2_5_Box3f * self
    , Imath_2_5_V3f const * point)
{
    (to_cpp(self)) -> extendBy(to_cpp_ref(point));
}

void Imath_2_5_Box3f_extendBy(
    Imath_2_5_Box3f * self
    , Imath_2_5_Box3f const * box)
{
    (to_cpp(self)) -> extendBy(to_cpp_ref(box));
}

void Imath_2_5_Box3i_extendBy(
    Imath_2_5_Box3i * self
    , Imath_2_5_Box3i const * box)
{
    (to_cpp(self)) -> extendBy(to_cpp_ref(box));
}
