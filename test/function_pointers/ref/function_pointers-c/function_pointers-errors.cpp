#include "/home/anders/code/cppmm/build/test/function_pointers/output/function_pointers-c/function_pointers-errors.h"
#include "/home/anders/code/cppmm/build/test/function_pointers/output/function_pointers-c/function_pointers-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* function_pointers_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

