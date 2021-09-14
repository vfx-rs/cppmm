#include "mimpl_private.h"

#include <new>

#include <stdexcept>

MIMPL_CPPMM_API unsigned int mimpl__Number_ctor(
    mimpl_Number_t * * this_)
{
    try {
        to_c(this_, new mimpl::Number());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

MIMPL_CPPMM_API unsigned int mimpl__Number_get_number(
    mimpl_Number_t const * this_
    , int * return_)
{
    try {
        *(return_) = (to_cpp(this_)) -> get_number();
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

inline int Number_do_get_number_impl(const ::mimpl::Number& self)  {
    return self.get_number();
}

MIMPL_CPPMM_API unsigned int Number_do_get_number(
    int * return_
    , mimpl_Number_t const * self)
{
    try {
        *(return_) = Number_do_get_number_impl(to_cpp_ref(self));
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

