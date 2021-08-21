#include "nested-errors.h"
#include "nested-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* NESTED_CPPMM_API nested_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

