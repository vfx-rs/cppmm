#include "deriveattr-errors.h"
#include "deriveattr-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

DERIVEATTR_CPPMM_API const char* deriveattr_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

