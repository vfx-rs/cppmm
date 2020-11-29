#include <Imath/ImathVec.h>

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm:opaquebytes")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))

namespace cppmm_bind {

namespace IMATH_INTERNAL_NAMESPACE {

namespace Imath = IMATH_INTERNAL_NAMESPACE;

template <class T>
class Vec3 {
public:

    bool equalWithAbsError(const Vec3<T>& v, T e) const;
    bool equalWithRelError(const Vec3<T>& v, T e) const;

    T dot(const Vec3& v) const;

    Vec3 cross(const Vec3& v) const;

    const Vec3& operator+= (const Vec3& v);
    Vec3 operator+ (const Vec3& v) const;

} CPPMM_VALUETYPE;

using V3f = Vec3<float>;
using V3i = Vec3<int>;

}

} // namespace cppmm_bind
