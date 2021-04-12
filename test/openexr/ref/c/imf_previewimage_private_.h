#pragma once
#include <imf_previewimage_.h>


#include <OpenEXR/ImfPreviewImage.h>
#include <cppmm_bind.hpp>



inline Imf_2_5::PreviewRgba const & to_cpp_ref(
    Imf_2_5_PreviewRgba const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::PreviewRgba const * >(rhs));
}


inline Imf_2_5::PreviewRgba & to_cpp_ref(
    Imf_2_5_PreviewRgba * rhs)
{
    return *(reinterpret_cast<Imf_2_5::PreviewRgba * >(rhs));
}


inline Imf_2_5::PreviewRgba const * to_cpp(
    Imf_2_5_PreviewRgba const * rhs)
{
    return reinterpret_cast<Imf_2_5::PreviewRgba const * >(rhs);
}


inline Imf_2_5::PreviewRgba * to_cpp(
    Imf_2_5_PreviewRgba * rhs)
{
    return reinterpret_cast<Imf_2_5::PreviewRgba * >(rhs);
}


inline Imf_2_5_PreviewRgba const * to_c(
    Imf_2_5::PreviewRgba const & rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewRgba const * >(&(rhs));
}


inline Imf_2_5_PreviewRgba const * to_c(
    Imf_2_5::PreviewRgba const * rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewRgba const * >(rhs);
}


inline Imf_2_5_PreviewRgba * to_c(
    Imf_2_5::PreviewRgba & rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewRgba * >(&(rhs));
}


inline Imf_2_5_PreviewRgba * to_c(
    Imf_2_5::PreviewRgba * rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewRgba * >(rhs);
}












inline Imf_2_5::PreviewImage const & to_cpp_ref(
    Imf_2_5_PreviewImage const * rhs)
{
    return *(reinterpret_cast<Imf_2_5::PreviewImage const * >(rhs));
}


inline Imf_2_5::PreviewImage & to_cpp_ref(
    Imf_2_5_PreviewImage * rhs)
{
    return *(reinterpret_cast<Imf_2_5::PreviewImage * >(rhs));
}


inline Imf_2_5::PreviewImage const * to_cpp(
    Imf_2_5_PreviewImage const * rhs)
{
    return reinterpret_cast<Imf_2_5::PreviewImage const * >(rhs);
}


inline Imf_2_5::PreviewImage * to_cpp(
    Imf_2_5_PreviewImage * rhs)
{
    return reinterpret_cast<Imf_2_5::PreviewImage * >(rhs);
}


inline Imf_2_5_PreviewImage const * to_c(
    Imf_2_5::PreviewImage const & rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewImage const * >(&(rhs));
}


inline Imf_2_5_PreviewImage const * to_c(
    Imf_2_5::PreviewImage const * rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewImage const * >(rhs);
}


inline Imf_2_5_PreviewImage * to_c(
    Imf_2_5::PreviewImage & rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewImage * >(&(rhs));
}


inline Imf_2_5_PreviewImage * to_c(
    Imf_2_5::PreviewImage * rhs)
{
    return reinterpret_cast<Imf_2_5_PreviewImage * >(rhs);
}


inline Imf_2_5_PreviewImage to_c_copy(
    Imf_2_5::PreviewImage const & rhs)
{
    Imf_2_5_PreviewImage result;
    Imf_2_5_PreviewImage_PreviewImage_1(&(result), reinterpret_cast<Imf_2_5_PreviewImage const * >(&(rhs)));
    return result;
}
