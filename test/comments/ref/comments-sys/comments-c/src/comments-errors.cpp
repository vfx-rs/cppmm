#include "comments-errors.h"
#include "comments-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* COMMENTS_CPPMM_API comments_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

