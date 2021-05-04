#include "/home/anders/code/cppmm/build/test/exceptions/output/exceptions-c/exceptions-errors.h"
#include "/home/anders/code/cppmm/build/test/exceptions/output/exceptions-c/exceptions-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* exceptions_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

