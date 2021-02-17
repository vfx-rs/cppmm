#include <imath_box.h>

#include <OpenEXR/ImathBox.h>
#include <cppmm_bind.hpp>
#include <imath_vec.h>

void Imath_2_5_Box3f_extendBy(
    Imath_2_5_Box3f *self
    , Imath_2_5_V3f const *point)
{
    (reinterpret_cast<Imath_2_5::Box<Imath::Vec3<float> > *>(self)) -> 
        extendBy(
             *(reinterpret_cast<Imath_2_5::Vec3<float> const *>(point))
            );
}
void Imath_2_5_Box3f_extendBy(
    Imath_2_5_Box3f *self
    , Imath_2_5_Box3f const *box)
{
    (reinterpret_cast<Imath_2_5::Box<Imath::Vec3<float> > *>(self)) -> 
        extendBy(
             *(reinterpret_cast<Imath_2_5::Box<Imath::Vec3<float> > const *>(box))
            );
}
void Imath_2_5_Box3i_extendBy(
    Imath_2_5_Box3i *self
    , Imath_2_5_Box3i const *box)
{
    (reinterpret_cast<Imath_2_5::Box<Imath::Vec3<int> > *>(self)) -> 
        extendBy(
             *(reinterpret_cast<Imath_2_5::Box<Imath::Vec3<int> > const *>(box))
            );
}
