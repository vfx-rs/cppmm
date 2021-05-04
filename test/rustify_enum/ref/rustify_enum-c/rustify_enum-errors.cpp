#include "/home/anders/code/cppmm/build/test/rustify_enum/output/rustify_enum-c/rustify_enum-errors.h"
#include "/home/anders/code/cppmm/build/test/rustify_enum/output/rustify_enum-c/rustify_enum-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* rustify_enum_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

