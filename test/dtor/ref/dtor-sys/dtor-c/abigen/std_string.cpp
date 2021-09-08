#include <string>
#include <abigen/std_string.hpp>

void abi_gen_std_string(std::ostream& os) {
	os << "std::__cxx11::basic_string<char>" << "|" << sizeof(std::__cxx11::basic_string<char>) << "|" << alignof(std::__cxx11::basic_string<char>) << "\n";
}
