#pragma once
#include <imf_keycode_.h>


#include <OpenEXR/ImfKeyCode.h>
#include <cppmm_bind.hpp>




















inline Imf_2_5::KeyCode const & to_cpp_ref(
    Imf_2_5_KeyCode const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::KeyCode const * >(rhs));
}


inline Imf_2_5::KeyCode & to_cpp_ref(
    Imf_2_5_KeyCode * rhs)
{
    return *(reinterpret_cast<Imf_2_5::KeyCode * >(rhs));
}


inline Imf_2_5::KeyCode const * to_cpp(
    Imf_2_5_KeyCode const * rhs)
{
    return reinterpret_cast<Imf_2_5::KeyCode const * >(rhs);
}


inline Imf_2_5::KeyCode * to_cpp(
    Imf_2_5_KeyCode * rhs)
{
    return reinterpret_cast<Imf_2_5::KeyCode * >(rhs);
}


inline Imf_2_5_KeyCode const * to_c(
    Imf_2_5::KeyCode const & rhs)
{
    return reinterpret_cast<Imf_2_5_KeyCode const * >(&(rhs));
}


inline Imf_2_5_KeyCode const * to_c(
    Imf_2_5::KeyCode const * rhs)
{
    return reinterpret_cast<Imf_2_5_KeyCode const * >(rhs);
}


inline Imf_2_5_KeyCode * to_c(
    Imf_2_5::KeyCode & rhs)
{
    return reinterpret_cast<Imf_2_5_KeyCode * >(&(rhs));
}


inline Imf_2_5_KeyCode * to_c(
    Imf_2_5::KeyCode * rhs)
{
    return reinterpret_cast<Imf_2_5_KeyCode * >(rhs);
}


inline Imf_2_5_KeyCode to_c_copy(
    Imf_2_5::KeyCode const & rhs)
{
    Imf_2_5_KeyCode result;
    Imf_2_5_KeyCode_KeyCode_1(&(result), reinterpret_cast<Imf_2_5_KeyCode const * >(&(rhs)));
    return result;
}
