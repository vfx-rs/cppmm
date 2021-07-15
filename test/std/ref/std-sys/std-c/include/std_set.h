#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std____cxx11__basic_string_char__t_s std____cxx11__basic_string_char__t;
typedef std____cxx11__basic_string_char__t std_string_t;

typedef struct std___Rb_tree_node_base_t_s {
    char _unused;
} __attribute__((aligned(8))) std___Rb_tree_node_base_t;
typedef std___Rb_tree_node_base_t std__Rb_tree_node_base_t;

typedef struct std__set_std__string__t_s {
    char data[48];
} __attribute__((aligned(8))) std__set_std__string__t;
typedef std__set_std__string__t std_set_string_t;

typedef struct std___Rb_tree_const_iterator_std____cxx11__basic_string_char___t_s {
    std__Rb_tree_node_base_t const * _M_node;
} __attribute__((aligned(8))) std___Rb_tree_const_iterator_std____cxx11__basic_string_char___t;
typedef std___Rb_tree_const_iterator_std____cxx11__basic_string_char___t std_set_string_iterator_t;


/** returns the size of this type in bytes */
unsigned int std__set_std__string__sizeof();
#define std_set_string_sizeof std__set_std__string__sizeof


/** returns the size of this type in bytes */
unsigned int std__set_std__string__alignof();
#define std_set_string_alignof std__set_std__string__alignof


unsigned int std__set_std__string__ctor(
    std_set_string_t * this_);
#define std_set_string_ctor std__set_std__string__ctor


unsigned int std__set_std__string__dtor(
    std_set_string_t * this_);
#define std_set_string_dtor std__set_std__string__dtor


unsigned int std__set_std__string__cbegin(
    std_set_string_t const * this_
    , std_set_string_iterator_t * return_);
#define std_set_string_cbegin std__set_std__string__cbegin


unsigned int std__set_std__string__cend(
    std_set_string_t const * this_
    , std_set_string_iterator_t * return_);
#define std_set_string_cend std__set_std__string__cend


unsigned int std__set_std__string__size(
    std_set_string_t const * this_
    , unsigned long * return_);
#define std_set_string_size std__set_std__string__size


unsigned int std___Rb_tree_const_iterator_std____cxx11__basic_string_char___deref(
    std_set_string_iterator_t const * this_
    , std_string_t const * * return_);
#define std_set_string_iterator_deref std___Rb_tree_const_iterator_std____cxx11__basic_string_char___deref


unsigned int std___Rb_tree_const_iterator_std____cxx11__basic_string_char___inc(
    std_set_string_iterator_t * this_
    , std_set_string_iterator_t * * return_);
#define std_set_string_iterator_inc std___Rb_tree_const_iterator_std____cxx11__basic_string_char___inc


unsigned int std_set_string_const_iterator_eq(
    _Bool * return_
    , std_set_string_iterator_t const * __x
    , std_set_string_iterator_t const * __y);

#ifdef __cplusplus
}
#endif
