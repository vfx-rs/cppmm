#include <imath_vec.h>

#include <OpenEXR/ImathVec.h>
#include <cppmm_bind.hpp>
#include <vector>

Imath_2_5_V3f const *Imath_2_5_V3f_normalize(
    Imath_2_5_V3f *self)
{
    return reinterpret_cast<Imath_2_5_V3f const *>((reinterpret_cast<Imath_2_5::Vec3<float> *>(self)) -> 
        normalize());
}
Imath_2_5_V3f Imath_2_5_V3f_normalized(
    Imath_2_5_V3f const *self)
{
    return *(reinterpret_cast<Imath_2_5_V3f *>(&((reinterpret_cast<Imath_2_5::Vec3<float> const *>(self)) -> 
        normalized())));
}
