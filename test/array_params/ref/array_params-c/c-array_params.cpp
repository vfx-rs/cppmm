#include <c-array_params_private.h>

#include <new>

void imath__Matrix44_float__from_array(
    imath_M44f_t * this_
    , float const a[4][4])
{
    new (this_) imath::Matrix44<float>(a);
}
