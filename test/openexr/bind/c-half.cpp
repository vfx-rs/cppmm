#include <OpenEXR/half.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

class half {
public:
    using BoundType = ::half;

    half();
    half(float f) CPPMM_RENAME(from_float);
    ~half();
    half(const ::half& rhs) CPPMM_RENAME(copy);
    half(::half&&) CPPMM_IGNORE;

    operator float() const;

    ::half operator-() const;
    ::half& operator=(const ::half& h);
    ::half& operator=(::half&& h) CPPMM_IGNORE;
    ::half& operator=(float f);

    ::half& operator+=(::half h);
    ::half& operator+=(float f);

    ::half& operator-=(::half h);
    ::half& operator-=(float f);

    ::half& operator*=(::half h);
    ::half& operator*=(float f);

    ::half& operator/=(::half h);
    ::half& operator/=(float f);

    ::half round(unsigned int n) const;

    bool isFinite() const;
    bool isNormalized() const;
    bool isDenormalized() const;
    bool isZero() const;
    bool isNan() const;
    bool isInfinity() const;
    bool isNegative() const;

    static ::half posInf();
    static ::half negInf();
    static ::half qNan();
    static ::half sNan();

    HALF_EXPORT unsigned short bits() const;
    HALF_EXPORT void setBits(unsigned short bits);

} CPPMM_OPAQUEBYTES;

} // namespace cppmm_bind
