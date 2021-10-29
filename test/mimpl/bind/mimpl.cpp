#include <mimpl.hpp>
#include <cppmm_bind.hpp>

namespace cppmm_bind {
namespace mimpl {

struct Number {
    using BoundType = ::mimpl::Number;

    int _number;

    Number();
    int get_number() const;

} CPPMM_OPAQUEPTR;

}

int Number_do_get_number(const ::mimpl::Number& self) CPPMM_IMPL {
    return self.get_number();
}

}
