#include <OpenEXR/ImathBox.h>
#include <abigen/imath_box.hpp>

void abi_gen_imath_box(std::ostream& os) {
	os << "Imath_2_5::Box<Imath::Vec3<float> >" << "|" << sizeof(Imath_2_5::Box<Imath::Vec3<float> >) << "|" << alignof(Imath_2_5::Box<Imath::Vec3<float> >) << "\n";
	os << "Imath_2_5::Box<Imath::Vec3<int> >" << "|" << sizeof(Imath_2_5::Box<Imath::Vec3<int> >) << "|" << alignof(Imath_2_5::Box<Imath::Vec3<int> >) << "\n";
}
