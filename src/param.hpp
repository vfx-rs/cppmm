#pragma once

#include <string>
#include <iostream>

#include "type.hpp"

namespace cppmm {

struct Param {
    Param(std::string name, QualifiedType qtype) : name(name), qtype(qtype) {}

    std::string name;
    QualifiedType qtype;

    bool is_pod() const { return qtype.is_pod(); }

    std::string create_c_declaration() const;
    std::string create_c_call() const;
};

std::ostream& operator<<(std::ostream& os, const Param& param);

} // namespace cppmm

