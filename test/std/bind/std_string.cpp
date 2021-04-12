#include <string>
#include <vector>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace std {

class basic_string {
public:
    using BoundType = ::std::string;

    // We can't match against the constructor without specifying an allocator
    // parameter, but we definitely don't want to be passing that from C so
    // we could use CPPMM_IGNORE here to indicate that we allow this
    // parameter
    // to be defaulted in the bindings. We'll want to check that there is in
    // fact a default supplied in the library of course...
    basic_string(const char* s, ::std::string::size_type count,
                 const ::std::string::allocator_type& alloc CPPMM_IGNORE);
    ::std::string& assign(const char* s, ::std::string::size_type count);
    const char* c_str() const;

} CPPMM_OPAQUEBYTES;

using string = ::std::string;

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
