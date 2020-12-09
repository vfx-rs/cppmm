#include <string>

namespace test {

class Test
{
public:
    explicit Test(const std::string & value)
        : m_value(value)
    {}
    
    void set_value(const std::string & value){ m_value = value; };
    const std::string & get_value() const{ return m_value; }
    std::string clone_value() const { return m_value; }
    std::string & edit_value() { return m_value; }
private:
    std::string m_value;
};

}
