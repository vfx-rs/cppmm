#include <optr.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace optr {

struct PubCtor {
    using BoundType = ::optr::PubCtor;

    PubCtor() CPPMM_RENAME(ctor);
    ~PubCtor();

    void doit();

} CPPMM_OPAQUEPTR;

struct PrvCtor {
    using BoundType = ::optr::PrvCtor;
    void doit();
};

struct AllPrv {
    using BoundType = ::optr::AllPrv;
};

struct Opaque {
    using BoundType = ::optr::Opaque;
} CPPMM_OPAQUETYPE;

} // namespace optr

} // namespace cppmm_bind
