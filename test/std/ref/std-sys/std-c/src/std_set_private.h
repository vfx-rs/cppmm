#pragma once
#include <std_set.h>


#include "std-errors-private.h"

#include <cstring>
#include <set>
#include <string>

inline std::_Rb_tree_node_base const & to_cpp_ref(
    std__Rb_tree_node_base_t const * rhs)
{
        return *(reinterpret_cast<std::_Rb_tree_node_base const * >(rhs));
}

inline std::_Rb_tree_node_base & to_cpp_ref(
    std__Rb_tree_node_base_t * rhs)
{
        return *(reinterpret_cast<std::_Rb_tree_node_base * >(rhs));
}

inline std::_Rb_tree_node_base const * to_cpp(
    std__Rb_tree_node_base_t const * rhs)
{
        return reinterpret_cast<std::_Rb_tree_node_base const * >(rhs);
}

inline std::_Rb_tree_node_base * to_cpp(
    std__Rb_tree_node_base_t * rhs)
{
        return reinterpret_cast<std::_Rb_tree_node_base * >(rhs);
}

inline void to_c(
    std__Rb_tree_node_base_t const * * lhs
    , std::_Rb_tree_node_base const & rhs)
{
        *(lhs) = reinterpret_cast<std__Rb_tree_node_base_t const * >(&(rhs));
}

inline void to_c(
    std__Rb_tree_node_base_t const * * lhs
    , std::_Rb_tree_node_base const * rhs)
{
        *(lhs) = reinterpret_cast<std__Rb_tree_node_base_t const * >(rhs);
}

inline void to_c(
    std__Rb_tree_node_base_t * * lhs
    , std::_Rb_tree_node_base & rhs)
{
        *(lhs) = reinterpret_cast<std__Rb_tree_node_base_t * >(&(rhs));
}

inline void to_c(
    std__Rb_tree_node_base_t * * lhs
    , std::_Rb_tree_node_base * rhs)
{
        *(lhs) = reinterpret_cast<std__Rb_tree_node_base_t * >(rhs);
}

inline void to_c_copy(
    std__Rb_tree_node_base_t * lhs
    , std::_Rb_tree_node_base const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

inline std::set<std::string> const & to_cpp_ref(
    std_set_string_t const * rhs)
{
        return *(reinterpret_cast<std::set<std::string> const * >(rhs));
}

inline std::set<std::string> & to_cpp_ref(
    std_set_string_t * rhs)
{
        return *(reinterpret_cast<std::set<std::string> * >(rhs));
}

inline std::set<std::string> const * to_cpp(
    std_set_string_t const * rhs)
{
        return reinterpret_cast<std::set<std::string> const * >(rhs);
}

inline std::set<std::string> * to_cpp(
    std_set_string_t * rhs)
{
        return reinterpret_cast<std::set<std::string> * >(rhs);
}

inline void to_c(
    std_set_string_t const * * lhs
    , std::set<std::string> const & rhs)
{
        *(lhs) = reinterpret_cast<std_set_string_t const * >(&(rhs));
}

inline void to_c(
    std_set_string_t const * * lhs
    , std::set<std::string> const * rhs)
{
        *(lhs) = reinterpret_cast<std_set_string_t const * >(rhs);
}

inline void to_c(
    std_set_string_t * * lhs
    , std::set<std::string> & rhs)
{
        *(lhs) = reinterpret_cast<std_set_string_t * >(&(rhs));
}

inline void to_c(
    std_set_string_t * * lhs
    , std::set<std::string> * rhs)
{
        *(lhs) = reinterpret_cast<std_set_string_t * >(rhs);
}

inline void to_c_move(
    std_set_string_t * lhs
    , std::set<std::string> rhs)
{
        new (lhs) std::set<std::string>(std::move(rhs));
}

inline std::set<std::string>::const_iterator const & to_cpp_ref(
    std_set_string_iterator_t const * rhs)
{
        return *(reinterpret_cast<std::set<std::string>::const_iterator const * >(rhs));
}

inline std::set<std::string>::const_iterator & to_cpp_ref(
    std_set_string_iterator_t * rhs)
{
        return *(reinterpret_cast<std::set<std::string>::const_iterator * >(rhs));
}

inline std::set<std::string>::const_iterator const * to_cpp(
    std_set_string_iterator_t const * rhs)
{
        return reinterpret_cast<std::set<std::string>::const_iterator const * >(rhs);
}

inline std::set<std::string>::const_iterator * to_cpp(
    std_set_string_iterator_t * rhs)
{
        return reinterpret_cast<std::set<std::string>::const_iterator * >(rhs);
}

inline void to_c(
    std_set_string_iterator_t const * * lhs
    , std::set<std::string>::const_iterator const & rhs)
{
        *(lhs) = reinterpret_cast<std_set_string_iterator_t const * >(&(rhs));
}

inline void to_c(
    std_set_string_iterator_t const * * lhs
    , std::set<std::string>::const_iterator const * rhs)
{
        *(lhs) = reinterpret_cast<std_set_string_iterator_t const * >(rhs);
}

inline void to_c(
    std_set_string_iterator_t * * lhs
    , std::set<std::string>::const_iterator & rhs)
{
        *(lhs) = reinterpret_cast<std_set_string_iterator_t * >(&(rhs));
}

inline void to_c(
    std_set_string_iterator_t * * lhs
    , std::set<std::string>::const_iterator * rhs)
{
        *(lhs) = reinterpret_cast<std_set_string_iterator_t * >(rhs);
}

inline void to_c_copy(
    std_set_string_iterator_t * lhs
    , std::set<std::string>::const_iterator const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

