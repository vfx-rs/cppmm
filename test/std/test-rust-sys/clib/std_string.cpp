#include "std_string.h"

#include <string>

namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(std::string, std_string)

#undef CPPMM_DEFINE_POINTER_CASTS
}

void std_string_ctor(std_string* self){
    new (self) std::string();
}

void std_string_from_cstr(std_string* self, const char * str){
    new (self) std::string(str);
}

void std_string_dtor(std_string* self){
    to_cpp(self)->~basic_string();
}

int std_string_size(const std_string* self){ // TODO: Should this be unsigned long int to match size_t?
    return to_cpp(self)->size();
}

const char * std_string_c_str(const std_string* self){
    return to_cpp(self)->c_str();
}
