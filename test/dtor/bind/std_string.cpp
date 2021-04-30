#include <string>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace std {

class basic_string {
public:
    using BoundType = ::std::string;

    basic_string() CPPMM_RENAME(ctor);
    ~basic_string() CPPMM_RENAME(dtor);
    basic_string(const ::std::string& rhs) CPPMM_RENAME(copy);

    ::std::string& assign(const char* s, ::std::string::size_type count);
    const char* c_str() const;

} CPPMM_OPAQUEBYTES CPPMM_IGNORE_UNBOUND;

using string = ::std::string;

} // namespace std

} // namespace cppmm_bind
