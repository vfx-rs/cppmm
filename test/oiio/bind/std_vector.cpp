#include <vector>
#include <string>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace std {

template <class T> class vector {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::std::vector<T>;

    vector();
    ~vector();

} CPPMM_OPAQUEBYTES;

// explicit instantiation
template class vector<::std::string>;

using vector_string = ::std::vector<::std::string>;

} // namespace std

} // namespace cppmm_bind

template class std::vector<std::string>;
