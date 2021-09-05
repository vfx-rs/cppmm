#include "comments-errors.h"
#include "comments-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

COMMENTS_CPPMM_API const char* comments_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

