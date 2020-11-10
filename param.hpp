#pragma once

#include <string>

#include "type.hpp"

namespace cppmm {

struct Param {
    std::string name;
    QualifiedType qtype;

    bool is_pod() const { return qtype.is_pod(); }

    std::string create_c_declaration() const;
    std::string create_c_call() const;
};

}
