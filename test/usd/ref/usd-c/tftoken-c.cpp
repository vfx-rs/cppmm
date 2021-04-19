#include <tftoken-c_private.h>

#include <new>

void pxrInternal_v0_20__pxrReserved____TfToken_copy(
    pxr_TfToken_t * this_
    , pxr_TfToken_t const * rhs)
{
    new (this_) pxrInternal_v0_20__pxrReserved__::TfToken(to_cpp_ref(rhs));
}
pxr_TfToken_t * pxrInternal_v0_20__pxrReserved____TfToken_assign(
    pxr_TfToken_t * this_
    , pxr_TfToken_t const * rhs)
{
    return to_c((to_cpp(this_)) -> operator=(to_cpp_ref(rhs)));
}
void pxrInternal_v0_20__pxrReserved____TfToken_destruct(
    pxr_TfToken_t * this_)
{
    (to_cpp(this_)) -> pxrInternal_v0_20__pxrReserved__::TfToken::~TfToken();
}
void pxrInternal_v0_20__pxrReserved____TfToken_from_string(
    pxr_TfToken_t * this_
    , char const * s)
{
    new (this_) pxrInternal_v0_20__pxrReserved__::TfToken(s);
}
unsigned long pxrInternal_v0_20__pxrReserved____TfToken_Hash(
    pxr_TfToken_t const * this_)
{
    return (to_cpp(this_)) -> Hash();
}
unsigned long pxrInternal_v0_20__pxrReserved____TfToken_size(
    pxr_TfToken_t const * this_)
{
    return (to_cpp(this_)) -> size();
}
char const * pxrInternal_v0_20__pxrReserved____TfToken_GetText(
    pxr_TfToken_t const * this_)
{
    return (to_cpp(this_)) -> GetText();
}
char const * pxrInternal_v0_20__pxrReserved____TfToken_data(
    pxr_TfToken_t const * this_)
{
    return (to_cpp(this_)) -> data();
}
_Bool pxrInternal_v0_20__pxrReserved____TfToken__eq(
    pxr_TfToken_t const * this_
    , pxr_TfToken_t const * o)
{
    return (to_cpp(this_)) -> operator==(to_cpp_ref(o));
}
_Bool pxrInternal_v0_20__pxrReserved____TfToken__ne(
    pxr_TfToken_t const * this_
    , pxr_TfToken_t const * o)
{
    return (to_cpp(this_)) -> operator!=(to_cpp_ref(o));
}
_Bool pxrInternal_v0_20__pxrReserved____TfToken_eq_string(
    pxr_TfToken_t const * this_
    , char const * o)
{
    return (to_cpp(this_)) -> operator==(o);
}
_Bool pxrInternal_v0_20__pxrReserved____TfToken_neq_string(
    pxr_TfToken_t const * this_
    , char const * o)
{
    return (to_cpp(this_)) -> operator!=(o);
}
_Bool pxrInternal_v0_20__pxrReserved____TfToken_operator_(
    pxr_TfToken_t const * this_
    , pxr_TfToken_t const * r)
{
    return (to_cpp(this_)) -> operator<(to_cpp_ref(r));
}
_Bool pxrInternal_v0_20__pxrReserved____TfToken_IsEmpty(
    pxr_TfToken_t const * this_)
{
    return (to_cpp(this_)) -> IsEmpty();
}
_Bool pxrInternal_v0_20__pxrReserved____TfToken_IsImmortal(
    pxr_TfToken_t const * this_)
{
    return (to_cpp(this_)) -> IsImmortal();
}
