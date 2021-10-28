#include <cma.hpp>
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace foo {

class PublicDerived { using BoundType = ::foo::PublicDerived; };
class PrivateDerived { using BoundType = ::foo::PrivateDerived; };
class DeletedDerived { using BoundType = ::foo::DeletedDerived; };

}

}

