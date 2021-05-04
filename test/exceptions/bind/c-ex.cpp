#include <ex.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace ex {

struct Struct {
    using BoundType = ::ex::Struct;

    void m1() CPPMM_THROWS(std::runtime_error, STD_RUNTIME_ERROR);
    float m2(float a) CPPMM_THROWS(std::logic_error, STD_LOGIC_ERROR)
        CPPMM_THROWS(std::runtime_error, STD_RUNTIME_ERROR);
} CPPMM_OPAQUEBYTES;

float f1(int a) CPPMM_THROWS(std::invalid_argument, STD_INVALID_ARGUMENT);
void f2() CPPMM_THROWS(std::invalid_argument, STD_INVALID_ARGUMENT);

} // namespace ex

} // namespace cppmm_bind
