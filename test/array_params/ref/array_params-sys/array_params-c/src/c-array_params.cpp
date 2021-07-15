#include "c-array_params_private.h"

#include <new>

#include <stdexcept>

unsigned int imath__Matrix44_float__from_array(
    imath_M44f_t * this_
    , float const a[4][4])
{
    try {
        new (this_) imath::Matrix44<float>(a);
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

