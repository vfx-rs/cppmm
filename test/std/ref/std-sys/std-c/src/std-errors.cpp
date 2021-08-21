#include "std-errors.h"
#include "std-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* STD_CPPMM_API std_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

