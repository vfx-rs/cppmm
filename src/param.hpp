#pragma once

#include <string>
#include <iostream>

#include "type.hpp"

namespace cppmm {

struct Param {
    Param(std::string name, Type type) : name(name), qtype(QualifiedType{type}) {}

    std::string name;
    QualifiedType qtype;

    bool is_pod() const { return qtype.is_pod(); }

    std::string create_c_declaration() const;
    std::string create_c_call() const;
};

} // namespace cppmm

namespace fmt {
std::ostream& operator<<(std::ostream& os, const cppmm::Param& param);
}
