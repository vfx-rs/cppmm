#pragma once
#include <std_string.h>


#include "std-errors-private.h"

#include <cstring>
#include <string>
#include <vector>




inline std::__cxx11::basic_string<char> const & to_cpp_ref(
    std_string_t const * rhs)
{
        return *(reinterpret_cast<std::__cxx11::basic_string<char> const * >(rhs));
}

inline std::__cxx11::basic_string<char> & to_cpp_ref(
    std_string_t * rhs)
{
        return *(reinterpret_cast<std::__cxx11::basic_string<char> * >(rhs));
}

inline std::__cxx11::basic_string<char> const * to_cpp(
    std_string_t const * rhs)
{
        return reinterpret_cast<std::__cxx11::basic_string<char> const * >(rhs);
}

inline std::__cxx11::basic_string<char> * to_cpp(
    std_string_t * rhs)
{
        return reinterpret_cast<std::__cxx11::basic_string<char> * >(rhs);
}

inline void to_c(
    std_string_t const * * lhs
    , std::__cxx11::basic_string<char> const & rhs)
{
        *(lhs) = reinterpret_cast<std_string_t const * >(&(rhs));
}

inline void to_c(
    std_string_t const * * lhs
    , std::__cxx11::basic_string<char> const * rhs)
{
        *(lhs) = reinterpret_cast<std_string_t const * >(rhs);
}

inline void to_c(
    std_string_t * * lhs
    , std::__cxx11::basic_string<char> & rhs)
{
        *(lhs) = reinterpret_cast<std_string_t * >(&(rhs));
}

inline void to_c(
    std_string_t * * lhs
    , std::__cxx11::basic_string<char> * rhs)
{
        *(lhs) = reinterpret_cast<std_string_t * >(rhs);
}



inline std::vector<std::string> const & to_cpp_ref(
    std_vector_string_t const * rhs)
{
        return *(reinterpret_cast<std::vector<std::string> const * >(rhs));
}

inline std::vector<std::string> & to_cpp_ref(
    std_vector_string_t * rhs)
{
        return *(reinterpret_cast<std::vector<std::string> * >(rhs));
}

inline std::vector<std::string> const * to_cpp(
    std_vector_string_t const * rhs)
{
        return reinterpret_cast<std::vector<std::string> const * >(rhs);
}

inline std::vector<std::string> * to_cpp(
    std_vector_string_t * rhs)
{
        return reinterpret_cast<std::vector<std::string> * >(rhs);
}

inline void to_c(
    std_vector_string_t const * * lhs
    , std::vector<std::string> const & rhs)
{
        *(lhs) = reinterpret_cast<std_vector_string_t const * >(&(rhs));
}

inline void to_c(
    std_vector_string_t const * * lhs
    , std::vector<std::string> const * rhs)
{
        *(lhs) = reinterpret_cast<std_vector_string_t const * >(rhs);
}

inline void to_c(
    std_vector_string_t * * lhs
    , std::vector<std::string> & rhs)
{
        *(lhs) = reinterpret_cast<std_vector_string_t * >(&(rhs));
}

inline void to_c(
    std_vector_string_t * * lhs
    , std::vector<std::string> * rhs)
{
        *(lhs) = reinterpret_cast<std_vector_string_t * >(rhs);
}
