#pragma once
#include "opaquebytes-api-export.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct obyte__Foo_t_s {
    char data[%SIZEobyte::Foo%];
} OPAQUEBYTES_CPPMM_ALIGN(%ALIGNobyte::Foo%) obyte__Foo_t;
typedef obyte__Foo_t obyte_Foo_t;


/** returns the size of this type in bytes */
OPAQUEBYTES_CPPMM_API unsigned int obyte__Foo_sizeof();
#define obyte_Foo_sizeof obyte__Foo_sizeof


/** returns the size of this type in bytes */
OPAQUEBYTES_CPPMM_API unsigned int obyte__Foo_alignof();
#define obyte_Foo_alignof obyte__Foo_alignof


#ifdef __cplusplus
}
#endif
