#pragma once

#include <string>
#include <vector>

#include "tagged_pointer.hpp"

namespace cppmm {

enum RecordKind { OpaquePtr = 0, OpaqueBytes = 1, ValueType = 2 };

class Record;
class Enum;
class Vec;
class Builtin {};
class FuncProto {};

extern Builtin builtin_int;

struct TypeVariant
    : public TaggedPointer<Builtin, FuncProto, Record, Enum, Vec> {
    using TaggedPointer::TaggedPointer;
};

struct Type {
    template <typename T>
    Type(const std::string& name, T* t,
         std::vector<std::string> namespaces = {})
        : name(name), var(t), namespaces(namespaces) {}

    std::string name;
    std::vector<std::string> namespaces = {};
    TypeVariant var;

    bool is_pod() const;
};

struct QualifiedType {
    Type type;
    bool is_ptr = false;
    bool is_uptr = false;
    bool is_ref = false;
    bool is_const = false;
    bool requires_cast = false;

    bool is_pod() const { return type.is_pod(); }
    std::string create_c_declaration() const;
};

} // namespace cppmm

namespace fmt {
std::ostream& operator<<(std::ostream& os, const cppmm::RecordKind& kind);
std::ostream& operator<<(std::ostream& os, const cppmm::QualifiedType& qtype);
}
