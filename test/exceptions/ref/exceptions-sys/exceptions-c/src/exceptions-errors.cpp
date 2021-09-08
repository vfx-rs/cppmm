#include "exceptions-errors.h"
#include "exceptions-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

EXCEPTIONS_CPPMM_API const char* exceptions_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

