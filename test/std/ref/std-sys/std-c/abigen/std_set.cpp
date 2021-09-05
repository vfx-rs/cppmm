#include <set>
#include <string>
#include <abigen/std_set.hpp>

void abi_gen_std_set(std::ostream& os) {
	os << "std::set<std::string>" << "|" << sizeof(std::set<std::string>) << "|" << alignof(std::set<std::string>) << "\n";
	os << "std::set<std::string>::const_iterator" << "|" << sizeof(std::set<std::string>::const_iterator) << "|" << alignof(std::set<std::string>::const_iterator) << "\n";
}
