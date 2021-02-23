











inline Imath_2_5::Vec3<float> const & to_cpp_ref(
    Imath_2_5_V3f const * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<float> const * >(rhs));
}


inline Imath_2_5::Vec3<float> & to_cpp_ref(
    Imath_2_5_V3f * rhs)
{
    return *(reinterpret_cast<Imath_2_5::Vec3<float> * >(rhs));
}


inline Imath_2_5::Vec3<float> const * to_cpp(
    Imath_2_5_V3f const * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<float> const * >(rhs);
}


inline Imath_2_5::Vec3<float> * to_cpp(
    Imath_2_5_V3f * rhs)
{
    return reinterpret_cast<Imath_2_5::Vec3<float> * >(rhs);
}


inline Imath_2_5_V3f const * to_c(
    Imath_2_5::Vec3<float> const & rhs)
{
    return reinterpret_cast<Imath_2_5_V3f const * >(&(rhs));
}


inline Imath_2_5_V3f const * to_c(
    Imath_2_5::Vec3<float> const * rhs)
{
    return reinterpret_cast<Imath_2_5_V3f const * >(rhs);
}


inline Imath_2_5_V3f * to_c(
    Imath_2_5::Vec3<float> & rhs)
{
    return reinterpret_cast<Imath_2_5_V3f * >(&(rhs));
}


inline Imath_2_5_V3f * to_c(
    Imath_2_5::Vec3<float> * rhs)
{
    return reinterpret_cast<Imath_2_5_V3f * >(rhs);
}
