#include <cassert>

#include "type.hpp"
#include "record.hpp"

namespace cppmm {

bool Type::is_pod() const {
    if (is_builtin || is_enum || is_func_proto) {
        return true;
    }

    if (record) {
        return record->is_pod();
    }

    assert(false && "TYPE POD FALLTHROUGH");
    return false;
}
}
