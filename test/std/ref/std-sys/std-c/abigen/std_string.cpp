#include <string>
#include <vector>
#include <abigen/std_string.hpp>

void abi_gen_std_string(std::ostream& os) {
	os << "std::string" << "|" << sizeof(std::string) << "|" << alignof(std::string) << "\n";
	os << "std::vector<std::string>" << "|" << sizeof(std::vector<std::string>) << "|" << alignof(std::vector<std::string>) << "\n";
}
