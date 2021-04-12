#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct pxrInternal_v0_20__pxrReserved____TfToken_t_s {
    char data[8];
} __attribute__((aligned(8))) pxrInternal_v0_20__pxrReserved____TfToken_t;
typedef pxrInternal_v0_20__pxrReserved____TfToken_t pxr_TfToken_t;




void pxrInternal_v0_20__pxrReserved____TfToken_copy(
    pxr_TfToken_t * this_
    , pxr_TfToken_t const * rhs);

#define pxr_TfToken_copy pxrInternal_v0_20__pxrReserved____TfToken_copy



pxr_TfToken_t * pxrInternal_v0_20__pxrReserved____TfToken_assign(
    pxr_TfToken_t * this_
    , pxr_TfToken_t const * rhs);

#define pxr_TfToken_assign pxrInternal_v0_20__pxrReserved____TfToken_assign



void pxrInternal_v0_20__pxrReserved____TfToken_destruct(
    pxr_TfToken_t * this_);

#define pxr_TfToken_destruct pxrInternal_v0_20__pxrReserved____TfToken_destruct



void pxrInternal_v0_20__pxrReserved____TfToken_from_string(
    pxr_TfToken_t * this_
    , char const * s);

#define pxr_TfToken_from_string pxrInternal_v0_20__pxrReserved____TfToken_from_string



unsigned long pxrInternal_v0_20__pxrReserved____TfToken_Hash(
    pxr_TfToken_t const * this_);

#define pxr_TfToken_Hash pxrInternal_v0_20__pxrReserved____TfToken_Hash



unsigned long pxrInternal_v0_20__pxrReserved____TfToken_size(
    pxr_TfToken_t const * this_);

#define pxr_TfToken_size pxrInternal_v0_20__pxrReserved____TfToken_size



char const * pxrInternal_v0_20__pxrReserved____TfToken_GetText(
    pxr_TfToken_t const * this_);

#define pxr_TfToken_GetText pxrInternal_v0_20__pxrReserved____TfToken_GetText



char const * pxrInternal_v0_20__pxrReserved____TfToken_data(
    pxr_TfToken_t const * this_);

#define pxr_TfToken_data pxrInternal_v0_20__pxrReserved____TfToken_data



_Bool pxrInternal_v0_20__pxrReserved____TfToken__eq(
    pxr_TfToken_t const * this_
    , pxr_TfToken_t const * o);

#define pxr_TfToken__eq pxrInternal_v0_20__pxrReserved____TfToken__eq



_Bool pxrInternal_v0_20__pxrReserved____TfToken__ne(
    pxr_TfToken_t const * this_
    , pxr_TfToken_t const * o);

#define pxr_TfToken__ne pxrInternal_v0_20__pxrReserved____TfToken__ne



_Bool pxrInternal_v0_20__pxrReserved____TfToken_eq_string(
    pxr_TfToken_t const * this_
    , char const * o);

#define pxr_TfToken_eq_string pxrInternal_v0_20__pxrReserved____TfToken_eq_string



_Bool pxrInternal_v0_20__pxrReserved____TfToken_neq_string(
    pxr_TfToken_t const * this_
    , char const * o);

#define pxr_TfToken_neq_string pxrInternal_v0_20__pxrReserved____TfToken_neq_string



_Bool pxrInternal_v0_20__pxrReserved____TfToken_operator_(
    pxr_TfToken_t const * this_
    , pxr_TfToken_t const * r);

#define pxr_TfToken_operator_ pxrInternal_v0_20__pxrReserved____TfToken_operator_



_Bool pxrInternal_v0_20__pxrReserved____TfToken_IsEmpty(
    pxr_TfToken_t const * this_);

#define pxr_TfToken_IsEmpty pxrInternal_v0_20__pxrReserved____TfToken_IsEmpty



_Bool pxrInternal_v0_20__pxrReserved____TfToken_IsImmortal(
    pxr_TfToken_t const * this_);

#define pxr_TfToken_IsImmortal pxrInternal_v0_20__pxrReserved____TfToken_IsImmortal










#ifdef __cplusplus
}
#endif
