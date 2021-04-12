#pragma once
#include <c-imageio.h>


#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>
#include <cstring>



inline OpenImageIO_v2_2::ImageSpec::SerialFormat const & OIIO_ImageSpec_SerialFormat_to_cpp_ref(
    OIIO_ImageSpec_SerialFormat const * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialFormat const * >(rhs));
}


inline OpenImageIO_v2_2::ImageSpec::SerialFormat & OIIO_ImageSpec_SerialFormat_to_cpp_ref(
    OIIO_ImageSpec_SerialFormat * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialFormat * >(rhs));
}


inline OpenImageIO_v2_2::ImageSpec::SerialFormat const * OIIO_ImageSpec_SerialFormat_to_cpp(
    OIIO_ImageSpec_SerialFormat const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialFormat const * >(rhs);
}


inline OpenImageIO_v2_2::ImageSpec::SerialFormat * OIIO_ImageSpec_SerialFormat_to_cpp(
    OIIO_ImageSpec_SerialFormat * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialFormat * >(rhs);
}


inline OIIO_ImageSpec_SerialFormat const * to_c(
    OpenImageIO_v2_2::ImageSpec::SerialFormat const & rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_SerialFormat const * >(&(rhs));
}


inline OIIO_ImageSpec_SerialFormat const * to_c(
    OpenImageIO_v2_2::ImageSpec::SerialFormat const * rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_SerialFormat const * >(rhs);
}


inline OIIO_ImageSpec_SerialFormat * to_c(
    OpenImageIO_v2_2::ImageSpec::SerialFormat & rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_SerialFormat * >(&(rhs));
}


inline OIIO_ImageSpec_SerialFormat * to_c(
    OpenImageIO_v2_2::ImageSpec::SerialFormat * rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_SerialFormat * >(rhs);
}


inline OIIO_ImageSpec_SerialFormat to_c_copy(
    OpenImageIO_v2_2::ImageSpec::SerialFormat const & rhs)
{
    OIIO_ImageSpec_SerialFormat result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}


inline OpenImageIO_v2_2::ImageSpec::SerialVerbose const & OIIO_ImageSpec_SerialVerbose_to_cpp_ref(
    OIIO_ImageSpec_SerialVerbose const * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialVerbose const * >(rhs));
}


inline OpenImageIO_v2_2::ImageSpec::SerialVerbose & OIIO_ImageSpec_SerialVerbose_to_cpp_ref(
    OIIO_ImageSpec_SerialVerbose * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialVerbose * >(rhs));
}


inline OpenImageIO_v2_2::ImageSpec::SerialVerbose const * OIIO_ImageSpec_SerialVerbose_to_cpp(
    OIIO_ImageSpec_SerialVerbose const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialVerbose const * >(rhs);
}


inline OpenImageIO_v2_2::ImageSpec::SerialVerbose * OIIO_ImageSpec_SerialVerbose_to_cpp(
    OIIO_ImageSpec_SerialVerbose * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialVerbose * >(rhs);
}


inline OIIO_ImageSpec_SerialVerbose const * to_c(
    OpenImageIO_v2_2::ImageSpec::SerialVerbose const & rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_SerialVerbose const * >(&(rhs));
}


inline OIIO_ImageSpec_SerialVerbose const * to_c(
    OpenImageIO_v2_2::ImageSpec::SerialVerbose const * rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_SerialVerbose const * >(rhs);
}


inline OIIO_ImageSpec_SerialVerbose * to_c(
    OpenImageIO_v2_2::ImageSpec::SerialVerbose & rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_SerialVerbose * >(&(rhs));
}


inline OIIO_ImageSpec_SerialVerbose * to_c(
    OpenImageIO_v2_2::ImageSpec::SerialVerbose * rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_SerialVerbose * >(rhs);
}


inline OIIO_ImageSpec_SerialVerbose to_c_copy(
    OpenImageIO_v2_2::ImageSpec::SerialVerbose const & rhs)
{
    OIIO_ImageSpec_SerialVerbose result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}









inline OpenImageIO_v2_2::ROI const & to_cpp_ref(
    OIIO_ROI_t const * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ROI const * >(rhs));
}


inline OpenImageIO_v2_2::ROI & to_cpp_ref(
    OIIO_ROI_t * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ROI * >(rhs));
}


inline OpenImageIO_v2_2::ROI const * to_cpp(
    OIIO_ROI_t const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ROI const * >(rhs);
}


inline OpenImageIO_v2_2::ROI * to_cpp(
    OIIO_ROI_t * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ROI * >(rhs);
}


inline OIIO_ROI_t const * to_c(
    OpenImageIO_v2_2::ROI const & rhs)
{
    return reinterpret_cast<OIIO_ROI_t const * >(&(rhs));
}


inline OIIO_ROI_t const * to_c(
    OpenImageIO_v2_2::ROI const * rhs)
{
    return reinterpret_cast<OIIO_ROI_t const * >(rhs);
}


inline OIIO_ROI_t * to_c(
    OpenImageIO_v2_2::ROI & rhs)
{
    return reinterpret_cast<OIIO_ROI_t * >(&(rhs));
}


inline OIIO_ROI_t * to_c(
    OpenImageIO_v2_2::ROI * rhs)
{
    return reinterpret_cast<OIIO_ROI_t * >(rhs);
}


inline OIIO_ROI_t to_c_copy(
    OpenImageIO_v2_2::ROI const & rhs)
{
    OIIO_ROI_t result;
    memcpy(&(result), &(rhs), sizeof(result));
    return result;
}











inline OpenImageIO_v2_2::ImageSpec const & to_cpp_ref(
    OIIO_ImageSpec_t const * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec const * >(rhs));
}


inline OpenImageIO_v2_2::ImageSpec & to_cpp_ref(
    OIIO_ImageSpec_t * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec * >(rhs));
}


inline OpenImageIO_v2_2::ImageSpec const * to_cpp(
    OIIO_ImageSpec_t const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ImageSpec const * >(rhs);
}


inline OpenImageIO_v2_2::ImageSpec * to_cpp(
    OIIO_ImageSpec_t * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ImageSpec * >(rhs);
}


inline OIIO_ImageSpec_t const * to_c(
    OpenImageIO_v2_2::ImageSpec const & rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_t const * >(&(rhs));
}


inline OIIO_ImageSpec_t const * to_c(
    OpenImageIO_v2_2::ImageSpec const * rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_t const * >(rhs);
}


inline OIIO_ImageSpec_t * to_c(
    OpenImageIO_v2_2::ImageSpec & rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_t * >(&(rhs));
}


inline OIIO_ImageSpec_t * to_c(
    OpenImageIO_v2_2::ImageSpec * rhs)
{
    return reinterpret_cast<OIIO_ImageSpec_t * >(rhs);
}


inline OIIO_ImageSpec_t to_c_copy(
    OpenImageIO_v2_2::ImageSpec const & rhs)
{
    OIIO_ImageSpec_t result;
    OpenImageIO_v2_2__ImageSpec_copy(&(result), reinterpret_cast<OIIO_ImageSpec_t const * >(&(rhs)));
    return result;
}



inline OpenImageIO_v2_2::ImageInput const & to_cpp_ref(
    OIIO_ImageInput_t const * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ImageInput const * >(rhs));
}


inline OpenImageIO_v2_2::ImageInput & to_cpp_ref(
    OIIO_ImageInput_t * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::ImageInput * >(rhs));
}


inline OpenImageIO_v2_2::ImageInput const * to_cpp(
    OIIO_ImageInput_t const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ImageInput const * >(rhs);
}


inline OpenImageIO_v2_2::ImageInput * to_cpp(
    OIIO_ImageInput_t * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::ImageInput * >(rhs);
}


inline OIIO_ImageInput_t const * to_c(
    OpenImageIO_v2_2::ImageInput const & rhs)
{
    return reinterpret_cast<OIIO_ImageInput_t const * >(&(rhs));
}


inline OIIO_ImageInput_t const * to_c(
    OpenImageIO_v2_2::ImageInput const * rhs)
{
    return reinterpret_cast<OIIO_ImageInput_t const * >(rhs);
}


inline OIIO_ImageInput_t * to_c(
    OpenImageIO_v2_2::ImageInput & rhs)
{
    return reinterpret_cast<OIIO_ImageInput_t * >(&(rhs));
}


inline OIIO_ImageInput_t * to_c(
    OpenImageIO_v2_2::ImageInput * rhs)
{
    return reinterpret_cast<OIIO_ImageInput_t * >(rhs);
}


