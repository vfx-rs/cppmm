#include <string>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace std {

class basic_string {
public:
    using BoundType = ::std::string;

    basic_string();
    basic_string(const ::std::string & rhs);

    ::std::string& assign(const char* s, ::std::string::size_type count);
    const char* c_str() const;

} CPPMM_OPAQUEBYTES;

using string = ::std::string;

} // namespace std

} // namespace cppmm_bind
