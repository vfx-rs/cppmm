#include <OpenEXR/ImfRational.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct Rational {
    using BoundType = Imf::Rational;

    Rational() CPPMM_RENAME(default);
    Rational(int n, int d);

    IMF_EXPORT
    explicit Rational(double x) CPPMM_RENAME(from_f64);

    operator double() const CPPMM_RENAME(as_f64);
} CPPMM_VALUETYPE;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
