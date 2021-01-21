#pragma once

#include "cppmm_containers.h"
#include "std_string.h"


#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#define CPPMM_ALIGN(x) __declspec(align(x))
#else
#define CPPMM_ALIGN(x) __attribute__((aligned(x)))
#endif

typedef struct test_Test test_Test;



std_string* test_Test_edit_value(test_Test* self);


const std_string* test_Test_get_value(const test_Test* self);


void test_Test_set_value(test_Test* self, const std_string* value);


std_string test_Test_clone_value(const test_Test* self);


test_Test* test_Test_Test(const std_string* value);


#undef CPPMM_ALIGN

#define test_Test test_Test
#define test_Test_edit_value test_Test_edit_value
#define test_Test_get_value test_Test_get_value
#define test_Test_set_value test_Test_set_value
#define test_Test_clone_value test_Test_clone_value
#define test_Test_Test test_Test_Test

#ifdef __cplusplus
}
#endif
    