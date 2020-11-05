#include <Imath/half.h>

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))

namespace cppmm_bind {
namespace Imath {
class half {
    half() CPPMM_RENAME(create_default);
    half(float f) CPPMM_RENAME(create_from_float);
    ~half() CPPMM_RENAME(delete);
    half(const ::Imath::half& other) CPPMM_RENAME(copy);
    half(::Imath::half&& other) CPPMM_IGNORE;
    operator float() const CPPMM_RENAME(to_float);

    // NOTE: Not binding
    ::Imath::half operator-() const CPPMM_RENAME(unary_minus);
    ::Imath::half& operator=(const ::Imath::half& h) CPPMM_RENAME(assign);
    ::Imath::half& operator=(::Imath::half&& h) noexcept CPPMM_IGNORE;
    ::Imath::half& operator=(float f) CPPMM_IGNORE;
    ::Imath::half& operator+=(::Imath::half h)
        CPPMM_RENAME(add_in_place_from_half);
    ::Imath::half& operator+=(float f) CPPMM_RENAME(add_in_place_from_float);
    ::Imath::half& operator-=(::Imath::half h)
        CPPMM_RENAME(subtract_in_place_from_half);
    ::Imath::half& operator-=(float f)
        CPPMM_RENAME(subtract_in_place_from_float);
    ::Imath::half& operator*=(::Imath::half h)
        CPPMM_RENAME(multiply_in_place_from_half);
    ::Imath::half& operator*=(float f)
        CPPMM_RENAME(multiply_in_place_from_float);
    ::Imath::half& operator/=(::Imath::half h)
        CPPMM_RENAME(divide_in_place_from_half);
    ::Imath::half& operator/=(float f) CPPMM_RENAME(divide_in_place_from_float);
    ::Imath::half round(unsigned int n) const CPPMM_RENAME(round);
    // END NOTE

    bool isFinite() const;
    bool isNormalized() const;
    bool isDenormalized() const;
    bool isZero() const;
    bool isNan() const;
    bool isInfinity() const;
    bool isNegative() const;

    // NOTE: Not binding
    static ::Imath::half posInf();
    static ::Imath::half negInf();
    static ::Imath::half qNan();
    static ::Imath::half sNan();
    // END NOTE

    unsigned short bits() const;
    void setBits(unsigned short bits);
};
} // namespace Imath
} // namespace cppmm_bind
