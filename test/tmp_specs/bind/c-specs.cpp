#include <tmp_specs.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace specs {

template <typename T> struct Attribute {
    using BoundType = ::specs::Attribute<T>;
    T t;

    const T& value();
};

template class Attribute<int>;
template class Attribute<float>;
using IntAttribute = ::specs::Attribute<int>;
using FloatAttribute = ::specs::Attribute<float>;

struct Specs {
    using BoundType = ::specs::Specs;
    void do_something(int);
    template <typename T> T* findAttribute(const char* name);
    template <typename T> const T* findAttribute(const char* name) const;
};

extern template ::specs::IntAttribute* Specs::findAttribute(const char* name);

extern template const ::specs::IntAttribute*
Specs::findAttribute(const char* name) const;

extern template ::specs::FloatAttribute* Specs::findAttribute(const char* name);
extern template const ::specs::FloatAttribute*
Specs::findAttribute(const char* name) const;

::specs::Attribute<int>* (Specs::*findAttribute_int)(const char*) =
    &Specs::findAttribute<::specs::IntAttribute>;

const ::specs::Attribute<int>* (Specs::*findAttribute_int_const)(
    const char*) const = &Specs::findAttribute<::specs::IntAttribute>;

::specs::Attribute<float>* (Specs::*findAttribute_float)(const char*) =
    &Specs::findAttribute<::specs::FloatAttribute>;

const ::specs::Attribute<float>* (Specs::*findAttribute_float_const)(
    const char*) const = &Specs::findAttribute<::specs::FloatAttribute>;

} // namespace specs

} // namespace cppmm_bind

template class ::specs::Attribute<int>;
template class ::specs::Attribute<float>;

extern template ::specs::IntAttribute*
specs::Specs::findAttribute(const char* name);

extern template const ::specs::IntAttribute*
specs::Specs::findAttribute(const char* name) const;

extern template ::specs::FloatAttribute*
specs::Specs::findAttribute(const char* name);

extern template const ::specs::FloatAttribute*
specs::Specs::findAttribute(const char* name) const;
