#include <tftoken-c_private.h>

#include <new>

unsigned int pxrInternal_v0_20__pxrReserved____TfToken_copy(
    pxr_TfToken_t * * this_
    , pxr_TfToken_t const * rhs)
{
    try {
        to_c(this_, new pxrInternal_v0_20__pxrReserved__::TfToken(to_cpp_ref(rhs)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_assign(
    pxr_TfToken_t * this_
    , pxr_TfToken_t * * return_
    , pxr_TfToken_t const * rhs)
{
    try {
        to_c(return_, (to_cpp(this_)) -> operator=(to_cpp_ref(rhs)));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_destruct(
    pxr_TfToken_t * this_)
{
    try {
        delete to_cpp(this_);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_from_string(
    pxr_TfToken_t * * this_
    , char const * s)
{
    try {
        to_c(this_, new pxrInternal_v0_20__pxrReserved__::TfToken(s));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_Hash(
    pxr_TfToken_t const * this_
    , unsigned long * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> Hash();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_size(
    pxr_TfToken_t const * this_
    , unsigned long * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> size();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_GetText(
    pxr_TfToken_t const * this_
    , char const * * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> GetText();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_data(
    pxr_TfToken_t const * this_
    , char const * * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> data();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken__eq(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , pxr_TfToken_t const * o)
{
    try {
        *(return_) = (to_cpp(this_)) -> operator==(to_cpp_ref(o));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken__ne(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , pxr_TfToken_t const * o)
{
    try {
        *(return_) = (to_cpp(this_)) -> operator!=(to_cpp_ref(o));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_eq_string(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , char const * o)
{
    try {
        *(return_) = (to_cpp(this_)) -> operator==(o);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_neq_string(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , char const * o)
{
    try {
        *(return_) = (to_cpp(this_)) -> operator!=(o);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_operator_(
    pxr_TfToken_t const * this_
    , _Bool * return_
    , pxr_TfToken_t const * r)
{
    try {
        *(return_) = (to_cpp(this_)) -> operator<(to_cpp_ref(r));
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_IsEmpty(
    pxr_TfToken_t const * this_
    , _Bool * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> IsEmpty();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int pxrInternal_v0_20__pxrReserved____TfToken_IsImmortal(
    pxr_TfToken_t const * this_
    , _Bool * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> IsImmortal();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
