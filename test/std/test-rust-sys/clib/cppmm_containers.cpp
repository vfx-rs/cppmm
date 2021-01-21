
#include "cppmm_containers.h"
#include <string>
#include <vector>

namespace {
#include "casts.h"

CPPMM_DEFINE_POINTER_CASTS(std::vector<std::string>, cppmm_string_vector);


#undef CPPMM_DEFINE_POINTER_CASTS
}

extern "C" {

const char* cppmm_string_vector_get(const cppmm_string_vector* vec, int index) {
    return (*to_cpp(vec))[index].c_str();
}

int cppmm_string_vector_size(const cppmm_string_vector* vec) {
    return to_cpp(vec)->size();
}

}
    