#include <dtor.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace dtor {

struct Struct {
    using BoundType = ::dtor::Struct;
    Struct();
    ~Struct();
} CPPMM_OPAQUEPTR;

} // namespace dtor

} // namespace cppmm_bind
