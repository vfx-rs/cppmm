#include "/home/anders/code/cppmm/build/test/deep_namespace/output/deep_namespace-c/deep_namespace-errors.h"
#include "/home/anders/code/cppmm/build/test/deep_namespace/output/deep_namespace-c/deep_namespace-errors-private.h"

thread_local std::string TLG_EXCEPTION_STRING;

const char* deep_namespace_get_exception_string() {
    return TLG_EXCEPTION_STRING.c_str();
}

