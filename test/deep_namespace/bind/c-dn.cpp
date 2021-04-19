#include <cppmm_bind.hpp>
#include <dn.hpp>

namespace cppmm_bind {

namespace DN {

namespace v2_2 {

namespace DN = ::DN::v2_2;

class Class {
public:
    using BoundType = DN::Class;
    enum Enum { One, Two, Three };

    struct Struct {
        using BoundType = DN::Class::Struct;
        void structMethod();
    } CPPMM_VALUETYPE;
};

void someFunction();

} // namespace v2_2

} // namespace DN

} // namespace cppmm_bind
