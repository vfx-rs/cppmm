#include "std_list_private.h"

#include "std_string_private.h"
#include <new>

#include <stdexcept>

STD_CPPMM_API unsigned int std__list_std__string__ctor(
    std_list_string_t * * this_)
{
    try {
        to_c(this_, new std::list<std::string>());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

STD_CPPMM_API unsigned int std__list_std__string___iterator_op_inc(
    std_list_string_iterator_t * this_
    , std_list_string_iterator_t * * return_)
{
        to_c(return_, (to_cpp(this_)) -> operator++());
        return 0;
}

STD_CPPMM_API unsigned int std__list_std__string___iterator_deref(
    std_list_string_iterator_t const * this_
    , std_string_t const * * return_)
{
    try {
        to_c(return_, (to_cpp(this_)) -> operator*());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

STD_CPPMM_API unsigned int std__list_std__string___iterator_deref_mut(
    std_list_string_iterator_t * this_
    , std_string_t * * return_)
{
    try {
        to_c(return_, (to_cpp(this_)) -> operator*());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

