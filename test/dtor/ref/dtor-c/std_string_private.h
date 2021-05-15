#pragma once
#include <std_string.h>


#include "dtor-errors-private.h"

#include <cstring>
#include <string>


/** returns the size of this type in bytes */

/** returns the size of this type in bytes */






inline std::__cxx11::basic_string<char> const & to_cpp_ref(
    std___cxx11_string_t const * rhs)
{
        return *(reinterpret_cast<std::__cxx11::basic_string<char> const * >(rhs));
}

inline std::__cxx11::basic_string<char> & to_cpp_ref(
    std___cxx11_string_t * rhs)
{
        return *(reinterpret_cast<std::__cxx11::basic_string<char> * >(rhs));
}

inline std::__cxx11::basic_string<char> const * to_cpp(
    std___cxx11_string_t const * rhs)
{
        return reinterpret_cast<std::__cxx11::basic_string<char> const * >(rhs);
}

inline std::__cxx11::basic_string<char> * to_cpp(
    std___cxx11_string_t * rhs)
{
        return reinterpret_cast<std::__cxx11::basic_string<char> * >(rhs);
}

inline void to_c(
    std___cxx11_string_t const * * lhs
    , std::__cxx11::basic_string<char> const & rhs)
{
        *(lhs) = reinterpret_cast<std___cxx11_string_t const * >(&(rhs));
}

inline void to_c(
    std___cxx11_string_t const * * lhs
    , std::__cxx11::basic_string<char> const * rhs)
{
        *(lhs) = reinterpret_cast<std___cxx11_string_t const * >(rhs);
}

inline void to_c(
    std___cxx11_string_t * * lhs
    , std::__cxx11::basic_string<char> & rhs)
{
        *(lhs) = reinterpret_cast<std___cxx11_string_t * >(&(rhs));
}

inline void to_c(
    std___cxx11_string_t * * lhs
    , std::__cxx11::basic_string<char> * rhs)
{
        *(lhs) = reinterpret_cast<std___cxx11_string_t * >(rhs);
}

inline void to_c_copy(
    std___cxx11_string_t * lhs
    , std::__cxx11::basic_string<char> const & rhs)
{
        std____cxx11__basic_string_char__copy(lhs, reinterpret_cast<std___cxx11_string_t const * >(&(rhs)));
}
