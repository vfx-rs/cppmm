#include <string>
#include <list>

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

template <typename T>
struct list {
    using BoundType = std::list<T>;
    list();

    struct iterator {
        using BoundType = typename std::list<T>::iterator;

        BoundType& operator++() CPPMM_RENAME(op_inc);
        const T& operator*() const CPPMM_RENAME(deref) CPPMM_MANUAL;
        T& operator*() CPPMM_RENAME(deref_mut) CPPMM_MANUAL;

    } CPPMM_OPAQUEPTR;

} CPPMM_OPAQUEPTR;

template class list<::std::string>;
using list_string CPPMM_FORCE_NAME("std::list<std::string>") = ::std::list<::std::string>;

using list_string_iterator CPPMM_FORCE_NAME("std::list<std::string>::iterator") = ::std::list<::std::string>::iterator;

} // namespace std

} // namespace cppmm_bind

template class std::list<std::string>;
