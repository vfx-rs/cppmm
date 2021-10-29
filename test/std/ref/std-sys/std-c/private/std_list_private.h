#pragma once
#include <std_list.h>


#include "std-errors-private.h"

#include <cstring>
#include <list>
#include <string>

inline std::list<std::string> const & to_cpp_ref(
    std_list_string_t const * rhs)
{
        return *(reinterpret_cast<std::list<std::string> const * >(rhs));
}

inline std::list<std::string> & to_cpp_ref(
    std_list_string_t * rhs)
{
        return *(reinterpret_cast<std::list<std::string> * >(rhs));
}

inline std::list<std::string> const * to_cpp(
    std_list_string_t const * rhs)
{
        return reinterpret_cast<std::list<std::string> const * >(rhs);
}

inline std::list<std::string> * to_cpp(
    std_list_string_t * rhs)
{
        return reinterpret_cast<std::list<std::string> * >(rhs);
}

inline void to_c(
    std_list_string_t const * * lhs
    , std::list<std::string> const & rhs)
{
        *(lhs) = reinterpret_cast<std_list_string_t const * >(&(rhs));
}

inline void to_c(
    std_list_string_t const * * lhs
    , std::list<std::string> const * rhs)
{
        *(lhs) = reinterpret_cast<std_list_string_t const * >(rhs);
}

inline void to_c(
    std_list_string_t * * lhs
    , std::list<std::string> & rhs)
{
        *(lhs) = reinterpret_cast<std_list_string_t * >(&(rhs));
}

inline void to_c(
    std_list_string_t * * lhs
    , std::list<std::string> * rhs)
{
        *(lhs) = reinterpret_cast<std_list_string_t * >(rhs);
}

inline void to_c_move(
    std_list_string_t * lhs
    , std::list<std::string> rhs)
{
        new (lhs) std::list<std::string>(std::move(rhs));
}

inline std::list<std::string>::iterator const & to_cpp_ref(
    std_list_string_iterator_t const * rhs)
{
        return *(reinterpret_cast<std::list<std::string>::iterator const * >(rhs));
}

inline std::list<std::string>::iterator & to_cpp_ref(
    std_list_string_iterator_t * rhs)
{
        return *(reinterpret_cast<std::list<std::string>::iterator * >(rhs));
}

inline std::list<std::string>::iterator const * to_cpp(
    std_list_string_iterator_t const * rhs)
{
        return reinterpret_cast<std::list<std::string>::iterator const * >(rhs);
}

inline std::list<std::string>::iterator * to_cpp(
    std_list_string_iterator_t * rhs)
{
        return reinterpret_cast<std::list<std::string>::iterator * >(rhs);
}

inline void to_c(
    std_list_string_iterator_t const * * lhs
    , std::list<std::string>::iterator const & rhs)
{
        *(lhs) = reinterpret_cast<std_list_string_iterator_t const * >(&(rhs));
}

inline void to_c(
    std_list_string_iterator_t const * * lhs
    , std::list<std::string>::iterator const * rhs)
{
        *(lhs) = reinterpret_cast<std_list_string_iterator_t const * >(rhs);
}

inline void to_c(
    std_list_string_iterator_t * * lhs
    , std::list<std::string>::iterator & rhs)
{
        *(lhs) = reinterpret_cast<std_list_string_iterator_t * >(&(rhs));
}

inline void to_c(
    std_list_string_iterator_t * * lhs
    , std::list<std::string>::iterator * rhs)
{
        *(lhs) = reinterpret_cast<std_list_string_iterator_t * >(rhs);
}

inline void to_c_copy(
    std_list_string_iterator_t * lhs
    , std::list<std::string>::iterator const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

