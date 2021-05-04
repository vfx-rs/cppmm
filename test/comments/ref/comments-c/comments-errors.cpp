#include "/home/anders/code/cppmm/build/test/comments/output/comments-c/comments-errors.h"
#include "/home/anders/code/cppmm/build/test/comments/output/comments-c/comments-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* comments_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

