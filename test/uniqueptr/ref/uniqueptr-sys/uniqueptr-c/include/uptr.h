#pragma once
#include "uniqueptr-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct foo__Foo_t_s foo__Foo_t;
typedef foo__Foo_t foo_Foo_t;

typedef struct std__unique_ptr_foo__Foo__t_s {
    char _unused;
} UNIQUEPTR_CPPMM_ALIGN(8) std__unique_ptr_foo__Foo__t;
typedef std__unique_ptr_foo__Foo__t std_FooPtr_t;


UNIQUEPTR_CPPMM_API unsigned int std__unique_ptr_foo__Foo__ctor(
    std_FooPtr_t * * this_
    , foo_Foo_t * p);
#define std_FooPtr_ctor std__unique_ptr_foo__Foo__ctor


UNIQUEPTR_CPPMM_API unsigned int std__unique_ptr_foo__Foo__dtor(
    std_FooPtr_t * this_);
#define std_FooPtr_dtor std__unique_ptr_foo__Foo__dtor


UNIQUEPTR_CPPMM_API unsigned int std__unique_ptr_foo__Foo__get(
    std_FooPtr_t const * this_
    , foo_Foo_t * * return_);
#define std_FooPtr_get std__unique_ptr_foo__Foo__get


#ifdef __cplusplus
}
#endif
