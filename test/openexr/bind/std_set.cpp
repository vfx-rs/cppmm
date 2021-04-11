#include <set>
#include <string>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace std {

template <class T> class set {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::std::set<T>;

    set();
    ~set();

} CPPMM_OPAQUEBYTES;

// explicit instantiation
template class set<::std::string>;

using set_string = ::std::set<::std::string>;

} // namespace std

} // namespace cppmm_bind

template class std::set<std::string>;
