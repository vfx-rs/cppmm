#include <OpenEXR/ImathVec.h>
#include <vector>
#include <abigen/imath_vec.hpp>

void abi_gen_imath_vec(std::ostream& os) {
	os << "Imath_2_5::Vec3<float>" << "|" << sizeof(Imath_2_5::Vec3<float>) << "|" << alignof(Imath_2_5::Vec3<float>) << "\n";
	os << "Imath_2_5::Vec3<int>" << "|" << sizeof(Imath_2_5::Vec3<int>) << "|" << alignof(Imath_2_5::Vec3<int>) << "\n";
}
