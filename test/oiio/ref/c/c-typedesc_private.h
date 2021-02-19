

inline OpenImageIO_v2_2::TypeDesc const & to_cpp_ref(
    OpenImageIO_v2_2_TypeDesc const * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc const * >(rhs));
}


inline OpenImageIO_v2_2::TypeDesc & to_cpp_ref(
    OpenImageIO_v2_2_TypeDesc * rhs)
{
    return *(reinterpret_cast<OpenImageIO_v2_2::TypeDesc * >(rhs));
}


inline OpenImageIO_v2_2::TypeDesc const * to_cpp(
    OpenImageIO_v2_2_TypeDesc const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::TypeDesc const * >(rhs);
}


inline OpenImageIO_v2_2::TypeDesc * to_cpp(
    OpenImageIO_v2_2_TypeDesc * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2::TypeDesc * >(rhs);
}


inline OpenImageIO_v2_2_TypeDesc const * to_c(
    OpenImageIO_v2_2::TypeDesc const & rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2_TypeDesc const * >(&(rhs));
}


inline OpenImageIO_v2_2_TypeDesc const * to_c(
    OpenImageIO_v2_2::TypeDesc const * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2_TypeDesc const * >(rhs);
}


inline OpenImageIO_v2_2_TypeDesc * to_c(
    OpenImageIO_v2_2::TypeDesc & rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2_TypeDesc * >(&(rhs));
}


inline OpenImageIO_v2_2_TypeDesc * to_c(
    OpenImageIO_v2_2::TypeDesc * rhs)
{
    return reinterpret_cast<OpenImageIO_v2_2_TypeDesc * >(rhs);
}
