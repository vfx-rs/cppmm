#pragma once
#include "std-api-export.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std__string_t_s std__string_t;
typedef std__string_t std_string_t;

typedef struct std___Rb_tree_node_base_t_s {
    char _unused;
} STD_CPPMM_ALIGN(8) std___Rb_tree_node_base_t;
typedef std___Rb_tree_node_base_t std__Rb_tree_node_base_t;

typedef struct std__set_std__string__t_s {
    char data[%SIZEstd::set<std::string>%];
} STD_CPPMM_ALIGN(%ALIGNstd::set<std::string>%) std__set_std__string__t;
typedef std__set_std__string__t std_set_string_t;

typedef struct std__set_std__string___const_iterator_t_s {
    std__Rb_tree_node_base_t const * _M_node;
} STD_CPPMM_ALIGN(8) std__set_std__string___const_iterator_t;
typedef std__set_std__string___const_iterator_t std_set_string_iterator_t;


/** returns the size of this type in bytes */
STD_CPPMM_API unsigned int std__set_std__string__sizeof();
#define std_set_string_sizeof std__set_std__string__sizeof


/** returns the size of this type in bytes */
STD_CPPMM_API unsigned int std__set_std__string__alignof();
#define std_set_string_alignof std__set_std__string__alignof


STD_CPPMM_API unsigned int std__set_std__string__ctor(
    std_set_string_t * this_);
#define std_set_string_ctor std__set_std__string__ctor


STD_CPPMM_API unsigned int std__set_std__string__dtor(
    std_set_string_t * this_);
#define std_set_string_dtor std__set_std__string__dtor


STD_CPPMM_API unsigned int std__set_std__string__cbegin(
    std_set_string_t const * this_
    , std_set_string_iterator_t * return_);
#define std_set_string_cbegin std__set_std__string__cbegin


STD_CPPMM_API unsigned int std__set_std__string__cend(
    std_set_string_t const * this_
    , std_set_string_iterator_t * return_);
#define std_set_string_cend std__set_std__string__cend


STD_CPPMM_API unsigned int std__set_std__string__size(
    std_set_string_t const * this_
    , size_t * return_);
#define std_set_string_size std__set_std__string__size


STD_CPPMM_API unsigned int std__set_std__string___const_iterator_deref(
    std_set_string_iterator_t const * this_
    , std_string_t const * * return_);
#define std_set_string_iterator_deref std__set_std__string___const_iterator_deref


STD_CPPMM_API unsigned int std__set_std__string___const_iterator_inc(
    std_set_string_iterator_t * this_
    , std_set_string_iterator_t * * return_);
#define std_set_string_iterator_inc std__set_std__string___const_iterator_inc


STD_CPPMM_API unsigned int std_set_string_const_iterator_eq(
    _Bool * return_
    , std_set_string_iterator_t const * __x
    , std_set_string_iterator_t const * __y);

#ifdef __cplusplus
}
#endif
