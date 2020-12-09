#include "test.hpp"

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm:opaquebytes")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))

namespace cppmm_bind {

namespace test {

class Test
{
public:
    //explicit Test(const std::string & value);
    void set_value(const std::string & value);
    const std::string & get_value() const;
    std::string clone_value() const;
    std::string & edit_value();
};

}

}
