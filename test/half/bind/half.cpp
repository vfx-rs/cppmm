#include <Imath/half.h>

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm:opaquebytes")))

namespace cppmm_bind {
namespace IMATH_INTERNAL_NAMESPACE {

namespace Imath = IMATH_INTERNAL_NAMESPACE;

class half {
    half() CPPMM_RENAME(ctor);
    half(float f) CPPMM_RENAME(from_float);
    ~half() CPPMM_RENAME(dtor);
    half(const ::Imath::half& other) CPPMM_RENAME(copy);
    half(::Imath::half&& other) CPPMM_IGNORE;
    operator float() const CPPMM_RENAME(to_float);

    ::Imath::half operator-() const CPPMM_RENAME(neg);
    // ::Imath::half operator-() const CPPMM_IGNORE;
    ::Imath::half& operator=(const ::Imath_3_0::half& h) CPPMM_RENAME(assign);
    ::Imath::half& operator=(::Imath_3_0::half&& h) noexcept CPPMM_IGNORE;
    ::Imath::half& operator=(float f) CPPMM_IGNORE;
    ::Imath::half& operator+=(::Imath_3_0::half h) CPPMM_RENAME(add_assign);
    ::Imath::half& operator+=(float f) CPPMM_RENAME(add_assign_float);
    ::Imath::half& operator-=(::Imath_3_0::half h) CPPMM_RENAME(sub_assign);
    ::Imath::half& operator-=(float f) CPPMM_RENAME(sub_assign_float);
    ::Imath::half& operator*=(::Imath_3_0::half h) CPPMM_RENAME(mul_assign);
    ::Imath::half& operator*=(float f) CPPMM_RENAME(mul_assign_float);
    ::Imath::half& operator/=(::Imath_3_0::half h) CPPMM_RENAME(div_assign);
    ::Imath::half& operator/=(float f) CPPMM_RENAME(div_assign_float);

    ::Imath::half round(unsigned int n) const;

    bool isFinite() const;
    bool isNormalized() const;
    bool isDenormalized() const;
    bool isZero() const;
    bool isNan() const;
    bool isInfinity() const;
    bool isNegative() const;

    static ::Imath::half posInf();
    static ::Imath::half negInf();
    static ::Imath::half qNan();
    static ::Imath::half sNan();

    unsigned short bits() const;
    void setBits(unsigned short bits);
} CPPMM_OPAQUEBYTES;
} // namespace Imath
} // namespace cppmm_bind
