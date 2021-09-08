#include <string>
#include <vector>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace std {

#if defined(_GLIBCXX_USE_CXX11_ABI)
#if _GLIBCXX_USE_CXX11_ABI
namespace std = ::std::__cxx11;
#else
namespace std = ::std;
#endif
#elif defined(_LIBCPP_VERSION)
namespace std = ::std::_LIBCPP_ABI_NAMESPACE;
#else
namespace std = ::std;
#endif

class basic_string {
public:
    using BoundType = std::basic_string<char>;

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

using string CPPMM_FORCE_NAME("std::string") = ::std::string;
} // namespace std

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
