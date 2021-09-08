#include "c-dtor_private.h"

#include <new>

#include <stdexcept>

DTOR_CPPMM_API unsigned int dtor__Struct_ctor(
    dtor_Struct_t * * this_)
{
    try {
        to_c(this_, new dtor::Struct());
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

DTOR_CPPMM_API unsigned int dtor__Struct_dtor(
    dtor_Struct_t * this_)
{
    try {
        delete to_cpp(this_);
        return 0;
    } catch (std::exception& e) {
        TLG_EXCEPTION_STRING = e.what();
        return -1;
    }
}

