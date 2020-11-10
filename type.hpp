#pragma once

#include <string>
#include <vector>

namespace cppmm {

enum TypeKind { OpaquePtr = 0, OpaqueBytes = 1, ValueType = 2 };

class Record;
class Enum;
class Vec;

struct Type {
    std::string name;
    std::vector<std::string> namespaces = {};
    bool is_builtin = false;
    bool is_enum = false;
    bool is_func_proto = false;
    Record* record = nullptr;
    const Enum* enm = nullptr;
    Vec* vec = nullptr;

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
};

} // namespace cppmm
