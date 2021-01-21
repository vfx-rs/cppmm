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

typedef struct {
    int x;
    int y;
    int z;
} Imath_3_0_V3i;

typedef struct {
    float x;
    float y;
    float z;
} Imath_3_0_V3f;



int Imath_3_0_V3i_baseTypeEpsilon();


int Imath_3_0_V3i_baseTypeSmallest();


int Imath_3_0_V3i_baseTypeMax();


Imath_3_0_V3i Imath_3_0_V3i_op_add(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


int Imath_3_0_V3i_dot(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


Imath_3_0_V3i Imath_3_0_V3i_div_t(const Imath_3_0_V3i* self, int a);


Imath_3_0_V3i Imath_3_0_V3i_cross(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


int Imath_3_0_V3i_length2(const Imath_3_0_V3i* self);


bool Imath_3_0_V3i_equalWithAbsError(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v, int e);


const Imath_3_0_V3i* Imath_3_0_V3i_op_add_assign(Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


bool Imath_3_0_V3i_equalWithRelError(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v, int e);


Imath_3_0_V3i Imath_3_0_V3i_normalized(const Imath_3_0_V3i* self);


Imath_3_0_V3i Imath_3_0_V3i_op_div(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


const Imath_3_0_V3i* Imath_3_0_V3i_op_sub_assign(Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


Imath_3_0_V3i Imath_3_0_V3i_op_sub(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


Imath_3_0_V3i Imath_3_0_V3i_op_neg(const Imath_3_0_V3i* self);


const Imath_3_0_V3i* Imath_3_0_V3i_op_div_assign(Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


int Imath_3_0_V3i_baseTypeMin();


unsigned int Imath_3_0_V3i_dimensions();


int Imath_3_0_V3i_length(const Imath_3_0_V3i* self);


const Imath_3_0_V3i* Imath_3_0_V3i_op_mul_assign(Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


const Imath_3_0_V3i* Imath_3_0_V3i_mul_assign_t(Imath_3_0_V3i* self, int a);


Imath_3_0_V3i Imath_3_0_V3i_op_mul(const Imath_3_0_V3i* self, const Imath_3_0_V3i* v);


const Imath_3_0_V3i* Imath_3_0_V3i_normalize(Imath_3_0_V3i* self);


Imath_3_0_V3i Imath_3_0_V3i_mul_t(const Imath_3_0_V3i* self, int a);


const Imath_3_0_V3i* Imath_3_0_V3i_div_assign_t(Imath_3_0_V3i* self, int a);


float Imath_3_0_V3f_baseTypeEpsilon();


float Imath_3_0_V3f_baseTypeSmallest();


float Imath_3_0_V3f_baseTypeMax();


Imath_3_0_V3f Imath_3_0_V3f_op_add(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


float Imath_3_0_V3f_dot(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


Imath_3_0_V3f Imath_3_0_V3f_div_t(const Imath_3_0_V3f* self, float a);


Imath_3_0_V3f Imath_3_0_V3f_cross(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


float Imath_3_0_V3f_length2(const Imath_3_0_V3f* self);


bool Imath_3_0_V3f_equalWithAbsError(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v, float e);


const Imath_3_0_V3f* Imath_3_0_V3f_op_add_assign(Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


bool Imath_3_0_V3f_equalWithRelError(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v, float e);


Imath_3_0_V3f Imath_3_0_V3f_normalized(const Imath_3_0_V3f* self);


Imath_3_0_V3f Imath_3_0_V3f_op_div(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


const Imath_3_0_V3f* Imath_3_0_V3f_op_sub_assign(Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


Imath_3_0_V3f Imath_3_0_V3f_op_sub(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


Imath_3_0_V3f Imath_3_0_V3f_op_neg(const Imath_3_0_V3f* self);


const Imath_3_0_V3f* Imath_3_0_V3f_op_div_assign(Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


float Imath_3_0_V3f_baseTypeMin();


unsigned int Imath_3_0_V3f_dimensions();


float Imath_3_0_V3f_length(const Imath_3_0_V3f* self);


const Imath_3_0_V3f* Imath_3_0_V3f_op_mul_assign(Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


const Imath_3_0_V3f* Imath_3_0_V3f_mul_assign_t(Imath_3_0_V3f* self, float a);


Imath_3_0_V3f Imath_3_0_V3f_op_mul(const Imath_3_0_V3f* self, const Imath_3_0_V3f* v);


const Imath_3_0_V3f* Imath_3_0_V3f_normalize(Imath_3_0_V3f* self);


Imath_3_0_V3f Imath_3_0_V3f_mul_t(const Imath_3_0_V3f* self, float a);


const Imath_3_0_V3f* Imath_3_0_V3f_div_assign_t(Imath_3_0_V3f* self, float a);


#undef CPPMM_ALIGN

#define Imath_V3i Imath_3_0_V3i
#define Imath_V3f Imath_3_0_V3f
#define Imath_V3i_baseTypeEpsilon Imath_3_0_V3i_baseTypeEpsilon
#define Imath_V3i_baseTypeSmallest Imath_3_0_V3i_baseTypeSmallest
#define Imath_V3i_baseTypeMax Imath_3_0_V3i_baseTypeMax
#define Imath_V3i_op_add Imath_3_0_V3i_op_add
#define Imath_V3i_dot Imath_3_0_V3i_dot
#define Imath_V3i_div_t Imath_3_0_V3i_div_t
#define Imath_V3i_cross Imath_3_0_V3i_cross
#define Imath_V3i_length2 Imath_3_0_V3i_length2
#define Imath_V3i_equalWithAbsError Imath_3_0_V3i_equalWithAbsError
#define Imath_V3i_op_add_assign Imath_3_0_V3i_op_add_assign
#define Imath_V3i_equalWithRelError Imath_3_0_V3i_equalWithRelError
#define Imath_V3i_normalized Imath_3_0_V3i_normalized
#define Imath_V3i_op_div Imath_3_0_V3i_op_div
#define Imath_V3i_op_sub_assign Imath_3_0_V3i_op_sub_assign
#define Imath_V3i_op_sub Imath_3_0_V3i_op_sub
#define Imath_V3i_op_neg Imath_3_0_V3i_op_neg
#define Imath_V3i_op_div_assign Imath_3_0_V3i_op_div_assign
#define Imath_V3i_baseTypeMin Imath_3_0_V3i_baseTypeMin
#define Imath_V3i_dimensions Imath_3_0_V3i_dimensions
#define Imath_V3i_length Imath_3_0_V3i_length
#define Imath_V3i_op_mul_assign Imath_3_0_V3i_op_mul_assign
#define Imath_V3i_mul_assign_t Imath_3_0_V3i_mul_assign_t
#define Imath_V3i_op_mul Imath_3_0_V3i_op_mul
#define Imath_V3i_normalize Imath_3_0_V3i_normalize
#define Imath_V3i_mul_t Imath_3_0_V3i_mul_t
#define Imath_V3i_div_assign_t Imath_3_0_V3i_div_assign_t
#define Imath_V3f_baseTypeEpsilon Imath_3_0_V3f_baseTypeEpsilon
#define Imath_V3f_baseTypeSmallest Imath_3_0_V3f_baseTypeSmallest
#define Imath_V3f_baseTypeMax Imath_3_0_V3f_baseTypeMax
#define Imath_V3f_op_add Imath_3_0_V3f_op_add
#define Imath_V3f_dot Imath_3_0_V3f_dot
#define Imath_V3f_div_t Imath_3_0_V3f_div_t
#define Imath_V3f_cross Imath_3_0_V3f_cross
#define Imath_V3f_length2 Imath_3_0_V3f_length2
#define Imath_V3f_equalWithAbsError Imath_3_0_V3f_equalWithAbsError
#define Imath_V3f_op_add_assign Imath_3_0_V3f_op_add_assign
#define Imath_V3f_equalWithRelError Imath_3_0_V3f_equalWithRelError
#define Imath_V3f_normalized Imath_3_0_V3f_normalized
#define Imath_V3f_op_div Imath_3_0_V3f_op_div
#define Imath_V3f_op_sub_assign Imath_3_0_V3f_op_sub_assign
#define Imath_V3f_op_sub Imath_3_0_V3f_op_sub
#define Imath_V3f_op_neg Imath_3_0_V3f_op_neg
#define Imath_V3f_op_div_assign Imath_3_0_V3f_op_div_assign
#define Imath_V3f_baseTypeMin Imath_3_0_V3f_baseTypeMin
#define Imath_V3f_dimensions Imath_3_0_V3f_dimensions
#define Imath_V3f_length Imath_3_0_V3f_length
#define Imath_V3f_op_mul_assign Imath_3_0_V3f_op_mul_assign
#define Imath_V3f_mul_assign_t Imath_3_0_V3f_mul_assign_t
#define Imath_V3f_op_mul Imath_3_0_V3f_op_mul
#define Imath_V3f_normalize Imath_3_0_V3f_normalize
#define Imath_V3f_mul_t Imath_3_0_V3f_mul_t
#define Imath_V3f_div_assign_t Imath_3_0_V3f_div_assign_t

#ifdef __cplusplus
}
#endif
    