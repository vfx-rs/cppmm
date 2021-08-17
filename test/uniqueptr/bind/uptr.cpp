#include <memory>

#include <foo.hpp>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace std {

#if defined(_LIBCPP_VERSION)
namespace std = ::std::_LIBCPP_ABI_NAMESPACE;
#else
namespace std = ::std;
#endif

template <class T> class unique_ptr {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::std::unique_ptr<T>;

    unique_ptr(T* p) CPPMM_RENAME(ctor);
    ~unique_ptr() CPPMM_RENAME(dtor);

    T* get() const;
} CPPMM_OPAQUEPTR;

// explicit instantiation
template class unique_ptr<foo::Foo>;
using FooPtr = ::std::unique_ptr<foo::Foo>;

} // namespace std

} // namespace cppmm_bind

template class std::unique_ptr<foo::Foo>;
