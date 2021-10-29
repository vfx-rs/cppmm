#include <cma.hpp>
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace foo {

struct PublicDerived { 
    using BoundType = ::foo::PublicDerived; 

    PublicDerived(const ::foo::PublicDerived&) CPPMM_MANUAL CPPMM_COPY_CTOR;
};

// class PrivateDerived { using BoundType = ::foo::PrivateDerived; };
// class DeletedDerived { using BoundType = ::foo::DeletedDerived; };

}

}

