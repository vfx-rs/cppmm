#include "templates.hpp"

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_MANUAL(x) __attribute__((annotate("cppmm:manual:" #x)))

#define CPPMM_OPAQUEPTR __attribute__((annotate("cppmm:opaqueptr")))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm:opaquebytes")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))

namespace cppmm_bind {

namespace templates {

template <typename T>
struct Vector3 { } CPPMM_VALUETYPE;

// struct Vector2 {} CPPMM_VALUETYPE;

using V3f = Vector3<float>;
// using V3i = Vector3<int>;

// void takes_spec_short(::templates::Vector3<short> v);

// template <typename T>
// void takes_vector3(::templates::Vector3<T>& v){}

// template <>
// void takes_vector3(::templates::Vector3<float>& v){std::cout << "float" << std::endl;}

}

}
