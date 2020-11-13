#pragma once

#include <string>
#include <vector>

#include "tagged_pointer.hpp"

namespace cppmm {

enum RecordKind { OpaquePtr = 0, OpaqueBytes = 1, ValueType = 2 };

class Record;
class Enum;
class Vector;
class Builtin {};
class FuncProto {};
class String {};

extern Builtin builtin_int;
extern String builtin_string;

struct TypeVariant
    : public TaggedPointer<Builtin, FuncProto, Record, Enum, Vector, String> {
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
    const char* get_c_qname() const;
    std::string get_cpp_qname() const;
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
