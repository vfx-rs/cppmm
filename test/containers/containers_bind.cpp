#include "containers.hpp"

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_MANUAL(x) __attribute__((annotate("cppmm:manual:" #x)))

#define CPPMM_OPAQUEPTR __attribute__((annotate("cppmm:opaqueptr")))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm:opaquebytes")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))

namespace cppmm_bind {

namespace containers {

class CustomVT {
} CPPMM_VALUETYPE;

class CustomOB {
} CPPMM_OPAQUEBYTES;

class CustomOP {
} CPPMM_OPAQUEPTR;

class CustomElement {
} CPPMM_OPAQUEBYTES;

class Containers {
    // void takes_const_vec_string_ref(const std::vector<std::string>& vec);
    void takes_const_vec_custom_ref(const std::vector<::containers::CustomElement>& vec);
    void testint(int a);

} CPPMM_OPAQUEPTR;

} // namespace containers

} // namespace cppmm_bind
