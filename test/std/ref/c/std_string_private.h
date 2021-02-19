



inline std::__cxx11::basic_string<char> const & to_cpp_ref(
    std___cxx11_string const * rhs)
{
    return *(reinterpret_cast<std::__cxx11::basic_string<char> const * >(rhs));
}


inline std::__cxx11::basic_string<char> & to_cpp_ref(
    std___cxx11_string * rhs)
{
    return *(reinterpret_cast<std::__cxx11::basic_string<char> * >(rhs));
}


inline std::__cxx11::basic_string<char> const * to_cpp(
    std___cxx11_string const * rhs)
{
    return reinterpret_cast<std::__cxx11::basic_string<char> const * >(rhs);
}


inline std::__cxx11::basic_string<char> * to_cpp(
    std___cxx11_string * rhs)
{
    return reinterpret_cast<std::__cxx11::basic_string<char> * >(rhs);
}


inline std___cxx11_string const * to_c(
    std::__cxx11::basic_string<char> const & rhs)
{
    return reinterpret_cast<std___cxx11_string const * >(&(rhs));
}


inline std___cxx11_string const * to_c(
    std::__cxx11::basic_string<char> const * rhs)
{
    return reinterpret_cast<std___cxx11_string const * >(rhs);
}


inline std___cxx11_string * to_c(
    std::__cxx11::basic_string<char> & rhs)
{
    return reinterpret_cast<std___cxx11_string * >(&(rhs));
}


inline std___cxx11_string * to_c(
    std::__cxx11::basic_string<char> * rhs)
{
    return reinterpret_cast<std___cxx11_string * >(rhs);
}
