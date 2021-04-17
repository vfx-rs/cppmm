#pragma once
#include <std_vector.h>


#include <string>
#include <vector>





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


inline std_vector_string_t const * to_c(
    std::vector<std::string> const & rhs)
{
    return reinterpret_cast<std_vector_string_t const * >(&(rhs));
}


inline std_vector_string_t const * to_c(
    std::vector<std::string> const * rhs)
{
    return reinterpret_cast<std_vector_string_t const * >(rhs);
}


inline std_vector_string_t * to_c(
    std::vector<std::string> & rhs)
{
    return reinterpret_cast<std_vector_string_t * >(&(rhs));
}


inline std_vector_string_t * to_c(
    std::vector<std::string> * rhs)
{
    return reinterpret_cast<std_vector_string_t * >(rhs);
}
