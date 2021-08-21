#include "imath-errors.h"
#include "imath-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* IMATH_CPPMM_API imath_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

