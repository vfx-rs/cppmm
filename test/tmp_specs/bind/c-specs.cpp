#include <tmp_specs.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace specs {

template <typename T> struct Attribute {
    using BoundType = ::specs::Attribute<T>;
    T t;
};

template class Attribute<int>;
template class Attribute<float>;
using IntAttribute = ::specs::Attribute<int>;
using FloatAttribute = ::specs::Attribute<float>;

struct Specs {
    using BoundType = ::specs::Specs;
    template <typename T> T* findAttribute(const char* name);
};

extern template ::specs::IntAttribute* Specs::findAttribute(const char* name)
    CPPMM_RENAME(findAttribute_int);
extern template ::specs::FloatAttribute* Specs::findAttribute(const char* name)
    CPPMM_RENAME(findAttribute_float);

auto findAttribute_int = &Specs::findAttribute<::specs::IntAttribute>;
auto findAttribute_float = &Specs::findAttribute<::specs::FloatAttribute>;

} // namespace specs

} // namespace cppmm_bind

template class ::specs::Attribute<int>;
template class ::specs::Attribute<float>;

extern template ::specs::IntAttribute*
specs::Specs::findAttribute(const char* name);
extern template ::specs::FloatAttribute*
specs::Specs::findAttribute(const char* name);
