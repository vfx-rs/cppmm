#include <math.h>

// Define the internal versioned namespace
#define MYMATH_INTERNAL_NAMESPACE Mymath_1_1

// Declare everything in the versioned namespace
namespace MYMATH_INTERNAL_NAMESPACE {

// A simple 3d vector type
template <typename T> struct Vec3 {
    T x;
    T y;
    T z;

    // Default 0-initialize
    Vec3() : x(0), y(0), z(0) {}
    // Initialize all members
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    // Initialize all members with a single value
    Vec3(T v) : x(v), y(v), z(v) {}
    // Copy constructor
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}

    T length() const { return sqrt(x * x + y * y + z * z); }
};

} // namespace MYMATH_INTERNAL_NAMESPACE

// Pull all symbols into public namespace
namespace Mymath {
using namespace MYMATH_INTERNAL_NAMESPACE;
}
