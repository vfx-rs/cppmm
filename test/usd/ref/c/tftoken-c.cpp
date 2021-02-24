#include <tftoken-c.h>

#include <cppmm_bind.hpp>
#include <pxr/base/tf/token.h>
#include <tftoken-c_private.h>


void pxrInternal_v0_20__pxrReserved___TfToken_copy(
    pxrInternal_v0_20__pxrReserved___TfToken * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * rhs)
{
    new (self) pxrInternal_v0_20__pxrReserved__::TfToken(to_cpp_ref(rhs));
}

pxrInternal_v0_20__pxrReserved___TfToken * pxrInternal_v0_20__pxrReserved___TfToken_assign(
    pxrInternal_v0_20__pxrReserved___TfToken * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * rhs)
{
    return to_c((to_cpp(self)) -> operator=(to_cpp_ref(rhs)));
}

void pxrInternal_v0_20__pxrReserved___TfToken_destruct(
    pxrInternal_v0_20__pxrReserved___TfToken * self)
{
    (to_cpp(self)) -> ~TfToken();
}

void pxrInternal_v0_20__pxrReserved___TfToken_from_string(
    pxrInternal_v0_20__pxrReserved___TfToken * self
    , char * s)
{
    new (self) pxrInternal_v0_20__pxrReserved__::TfToken(to_cpp(s));
}

unsigned long pxrInternal_v0_20__pxrReserved___TfToken_Hash(
    pxrInternal_v0_20__pxrReserved___TfToken const * self)
{
    return (to_cpp(self)) -> Hash();
}

unsigned long pxrInternal_v0_20__pxrReserved___TfToken_size(
    pxrInternal_v0_20__pxrReserved___TfToken const * self)
{
    return (to_cpp(self)) -> size();
}

char * pxrInternal_v0_20__pxrReserved___TfToken_GetText(
    pxrInternal_v0_20__pxrReserved___TfToken const * self)
{
    return to_c((to_cpp(self)) -> GetText());
}

char * pxrInternal_v0_20__pxrReserved___TfToken_data(
    pxrInternal_v0_20__pxrReserved___TfToken const * self)
{
    return to_c((to_cpp(self)) -> data());
}

_Bool pxrInternal_v0_20__pxrReserved___TfToken_operator==(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * o)
{
    return (to_cpp(self)) -> operator==(to_cpp_ref(o));
}

_Bool pxrInternal_v0_20__pxrReserved___TfToken_operator!=(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * o)
{
    return (to_cpp(self)) -> operator!=(to_cpp_ref(o));
}

_Bool pxrInternal_v0_20__pxrReserved___TfToken_eq_string(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , char * o)
{
    return (to_cpp(self)) -> operator==(to_cpp(o));
}

_Bool pxrInternal_v0_20__pxrReserved___TfToken_neq_string(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , char * o)
{
    return (to_cpp(self)) -> operator!=(to_cpp(o));
}

_Bool pxrInternal_v0_20__pxrReserved___TfToken_operator_(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * r)
{
    return (to_cpp(self)) -> operator<(to_cpp_ref(r));
}

_Bool pxrInternal_v0_20__pxrReserved___TfToken_IsEmpty(
    pxrInternal_v0_20__pxrReserved___TfToken const * self)
{
    return (to_cpp(self)) -> IsEmpty();
}

_Bool pxrInternal_v0_20__pxrReserved___TfToken_IsImmortal(
    pxrInternal_v0_20__pxrReserved___TfToken const * self)
{
    return (to_cpp(self)) -> IsImmortal();
}
