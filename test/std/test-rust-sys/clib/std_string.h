
#pragma once
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

typedef struct { char _private[24]; } std_string CPPMM_ALIGN(8);

void std_string_ctor(std_string* self);
void std_string_from_cstr(std_string* self, const char * str);
void std_string_dtor(std_string* self);
int std_string_size(const std_string* self);
const char * std_string_c_str(const std_string* self);

#ifdef __cplusplus
}
#endif
