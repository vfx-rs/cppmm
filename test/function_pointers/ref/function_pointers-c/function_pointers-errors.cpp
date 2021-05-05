#include "function_pointers-errors.h"
#include "function_pointers-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* function_pointers_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

