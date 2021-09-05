#include "nested-errors.h"
#include "nested-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

NESTED_CPPMM_API const char* nested_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

