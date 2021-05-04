#include "/home/anders/code/cppmm/build/test/opaqueptr/output/opaqueptr-c/opaqueptr-errors.h"
#include "/home/anders/code/cppmm/build/test/opaqueptr/output/opaqueptr-c/opaqueptr-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* opaqueptr_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

