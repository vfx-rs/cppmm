#include "std-errors.h"
#include "std-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* std_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

