#include <string>

namespace test_std_string {

class Test
{
public:
    Test(std::string & value);
    void set_value(std::string & value);
    std::string get_value() const;
};

}
