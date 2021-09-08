#pragma once
#include "comments-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

/** A test class to make sure we can
grab comments to be injected into C and Rust */
typedef struct comments__Class_t_s {
    char _unused;
} COMMENTS_CPPMM_ALIGN(1) comments__Class_t;
typedef comments__Class_t comments_Class_t;


/** This method doesn't do anything interesting at all */
COMMENTS_CPPMM_API unsigned int comments__Class_method(
    comments_Class_t * this_);
#define comments_Class_method comments__Class_method


/** This is a free function that also does nothing interesting */
COMMENTS_CPPMM_API unsigned int comments_function();

#ifdef __cplusplus
}
#endif
