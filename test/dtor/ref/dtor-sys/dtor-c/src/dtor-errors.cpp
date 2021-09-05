#include "dtor-errors.h"
#include "dtor-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

DTOR_CPPMM_API const char* dtor_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

