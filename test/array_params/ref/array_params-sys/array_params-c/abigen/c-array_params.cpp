#include <array_params.hpp>
#include <abigen/c-array_params.hpp>

void abi_gen_c_array_params(std::ostream& os) {
	os << "imath::Matrix44<float>" << "|" << sizeof(imath::Matrix44<float>) << "|" << alignof(imath::Matrix44<float>) << "\n";
}
