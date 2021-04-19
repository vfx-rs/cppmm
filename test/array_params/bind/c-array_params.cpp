#include <array_params.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace imath {

template <typename T> struct Matrix44 {
    using BoundType = ::imath::Matrix44<T>;

    Matrix44(const T a[4][4]) CPPMM_RENAME(from_array);
} CPPMM_VALUETYPE;

template class Matrix44<float>;
using M44f = ::imath::Matrix44<float>;

} // namespace imath

} // namespace cppmm_bind

template class imath::Matrix44<float>;
