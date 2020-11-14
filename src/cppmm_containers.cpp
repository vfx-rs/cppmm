#include "cppmm_containers.h"
#include <string>
#include <vector>

namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(std::vector<std::string>, cppmm_Vector_string);


#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {

const char* cppmm_Vector_string_get(const cppmm_Vector_string* vec, int index) {
    return *to_cpp(vec))[index].c_str();
}

int cppmm_Vector_string_size(const cppmm_Vector_string* vec) {
    return to_cpp(vec)->size();
}


}
