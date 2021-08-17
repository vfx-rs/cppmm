#pragma once
#include <uptr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct foo__Foo_t_s {
    char _unused;
} __attribute__((aligned(1))) foo__Foo_t;
typedef foo__Foo_t foo_Foo_t;


unsigned int foo__Foo_ctor(
    foo_Foo_t * * this_);
#define foo_Foo_ctor foo__Foo_ctor


unsigned int foo__Foo_dtor(
    foo_Foo_t * this_);
#define foo_Foo_dtor foo__Foo_dtor


unsigned int foo__Foo_create(
    std_FooPtr_t * * return_);
#define foo_Foo_create foo__Foo_create


#ifdef __cplusplus
}
#endif
