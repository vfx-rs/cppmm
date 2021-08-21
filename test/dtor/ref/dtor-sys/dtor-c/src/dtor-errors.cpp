#include "dtor-errors.h"
#include "dtor-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* DTOR_CPPMM_API dtor_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

