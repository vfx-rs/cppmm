#pragma once

#include "cppmm_containers.h"


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

typedef struct containers_Containers containers_Containers;

typedef struct { char _private[8]; } containers_CustomElement CPPMM_ALIGN(4);

typedef struct { char _private[24]; } containers_CustomElement_vector CPPMM_ALIGN(8);

void containers_CustomElement_vector_ctor(containers_CustomElement_vector* vec);
void containers_CustomElement_vector_dtor(const containers_CustomElement_vector* vec);
int containers_CustomElement_vector_size(const containers_CustomElement_vector* vec);
containers_CustomElement* containers_CustomElement_vector_data(containers_CustomElement_vector* vec);

void containers_CustomElement_vector_get(const containers_CustomElement_vector* vec, int index, containers_CustomElement* element);
void containers_CustomElement_vector_set(containers_CustomElement_vector* vec, int index, containers_CustomElement* element);
typedef struct containers_CustomOP containers_CustomOP;

typedef struct {
    int a;
    int b;
} containers_CustomVT;

typedef struct { char _private[4]; } containers_CustomOB CPPMM_ALIGN(4);


void containers_Containers_testint(containers_Containers* self, int a);


void containers_Containers_takes_const_vec_custom_ref(containers_Containers* self, const containers_CustomElement_vector* vec);


void containers_Containers_takes_mut_vec_string_ref(cppmm_string_vector* vec);


void containers_Containers_takes_const_vec_string_ref(const cppmm_string_vector* vec);


cppmm_string_vector containers_Containers_returns_vec_string();


#undef CPPMM_ALIGN

#ifdef __cplusplus
}
#endif
    