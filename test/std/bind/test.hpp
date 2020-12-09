#include <string>

namespace test {

class Test
{
public:
    explicit Test(const std::string & value);
    void set_value(const std::string & value);
    const std::string & get_value() const;
    std::string & edit_value();
};

}
