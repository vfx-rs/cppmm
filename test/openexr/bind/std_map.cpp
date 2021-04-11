#include <map>
#include <string>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace std {

template <class K, class V> class map {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::std::map<K, V>;

    map();
    ~map();

} CPPMM_OPAQUEBYTES;

// explicit instantiation
template class map<::std::string, ::std::string>;

using map_string_string = ::std::map<::std::string, ::std::string>;

} // namespace std

} // namespace cppmm_bind

template class std::map<std::string, std::string>;
