#include <set>
#include <string>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace std {

#if defined(_LIBCPP_VERSION)
namespace std = ::std::_LIBCPP_ABI_NAMESPACE;
#else
namespace std = ::std;
#endif

struct _Rb_tree_node_base {
    using BoundType = ::std::_Rb_tree_node_base;
} CPPMM_OPAQUEPTR CPPMM_IGNORE_UNBOUND;

template <class T> class set {
public:
    // This allows us to see through to the type in Imath
    using BoundType = ::std::set<T>;

    set() CPPMM_RENAME(ctor);
    ~set();

    size_t size() const;

    typename ::std::set<T>::const_iterator cbegin() const noexcept;
    typename ::std::set<T>::const_iterator cend() const noexcept;

    struct iterator {
        using BoundType = typename ::std::set<T>::const_iterator;

        typename ::std::set<T>::const_iterator& operator++() CPPMM_RENAME(inc);
        const T& operator*() const CPPMM_RENAME(deref);

        friend bool operator==(const typename std::set<T>::const_iterator& a,
                               const typename std::set<T>::const_iterator& b)
            CPPMM_RENAME(set_string_const_iterator_eq);
    } CPPMM_VALUETYPE CPPMM_IGNORE_UNBOUND;

} CPPMM_OPAQUEBYTES CPPMM_IGNORE_UNBOUND;

// explicit instantiation
template class set<::std::string>;

using set_string CPPMM_FORCE_NAME("std::set<std::string>") = ::std::set<::std::string>;
using set_string_iterator CPPMM_FORCE_NAME("std::set<std::string>::const_iterator") = ::std::set<::std::string>::const_iterator;

} // namespace std

} // namespace cppmm_bind

template class std::set<std::string>;
