//
#include "tftoken-c.h"
#include <pxr/base/tf/token.h>



namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(pxrInternal_v0_20__pxrReserved__::TfToken, pxrInternal_v0_20__pxrReserved___TfToken)

#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {
static_assert(sizeof(pxrInternal_v0_20__pxrReserved__::TfToken) == sizeof(pxrInternal_v0_20__pxrReserved___TfToken), "sizes do not match");
static_assert(alignof(pxrInternal_v0_20__pxrReserved__::TfToken) == alignof(pxrInternal_v0_20__pxrReserved___TfToken), "alignments do not match");

bool pxrInternal_v0_20__pxrReserved___TfToken_IsEmpty(const pxrInternal_v0_20__pxrReserved___TfToken* self) {
    return to_cpp(self)->IsEmpty();
}



bool pxrInternal_v0_20__pxrReserved___TfToken_neq_string(const pxrInternal_v0_20__pxrReserved___TfToken* self, const char* o) {
    return *to_cpp(self) != o;
}



bool pxrInternal_v0_20__pxrReserved___TfToken_eq_string(const pxrInternal_v0_20__pxrReserved___TfToken* self, const char* o) {
    return *to_cpp(self) == o;
}



bool pxrInternal_v0_20__pxrReserved___TfToken_op_neq(const pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* o) {
    return *to_cpp(self) != *to_cpp(o);
}



bool pxrInternal_v0_20__pxrReserved___TfToken_op_eq(const pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* o) {
    return *to_cpp(self) == *to_cpp(o);
}



const char* pxrInternal_v0_20__pxrReserved___TfToken_data(const pxrInternal_v0_20__pxrReserved___TfToken* self) {
    return to_cpp(self)->data();
}



pxrInternal_v0_20__pxrReserved___TfToken* pxrInternal_v0_20__pxrReserved___TfToken_assign(pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* other) {
    *to_cpp(self) = *to_cpp(other);
    return self;
}



void pxrInternal_v0_20__pxrReserved___TfToken_destruct(pxrInternal_v0_20__pxrReserved___TfToken* self) {
    to_cpp(self)->~TfToken();
}



bool pxrInternal_v0_20__pxrReserved___TfToken_IsImmortal(const pxrInternal_v0_20__pxrReserved___TfToken* self) {
    return to_cpp(self)->IsImmortal();
}



bool pxrInternal_v0_20__pxrReserved___TfToken_op_lt(const pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* r) {
    return *to_cpp(self) < *to_cpp(r);
}



void pxrInternal_v0_20__pxrReserved___TfToken_copy(pxrInternal_v0_20__pxrReserved___TfToken* self, const pxrInternal_v0_20__pxrReserved___TfToken* other) {
    self = to_c(new (self) pxrInternal_v0_20__pxrReserved__::TfToken(*to_cpp(other)));
}



void pxrInternal_v0_20__pxrReserved___TfToken_from_string(pxrInternal_v0_20__pxrReserved___TfToken* self, const char* s) {
    self = to_c(new (self) pxrInternal_v0_20__pxrReserved__::TfToken(s));
}



const char* pxrInternal_v0_20__pxrReserved___TfToken_GetText(const pxrInternal_v0_20__pxrReserved___TfToken* self) {
    return to_cpp(self)->GetText();
}



unsigned long pxrInternal_v0_20__pxrReserved___TfToken_Hash(const pxrInternal_v0_20__pxrReserved___TfToken* self) {
    return to_cpp(self)->Hash();
}



unsigned long pxrInternal_v0_20__pxrReserved___TfToken_size(const pxrInternal_v0_20__pxrReserved___TfToken* self) {
    return to_cpp(self)->size();
}



}
    