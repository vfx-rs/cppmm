#include <OpenEXR/half.h>

namespace cppmm_bind {
namespace IMATH_NAMESPACE {
class half {
    half() noexcept __attribute__((annotate("cppmm:rename:default")));
    half(float f) noexcept __attribute__((annotate("cppmm:rename:from_float")));
    ~half() noexcept __attribute__((annotate("cppmm:rename:delete")));
    half(const IMATH_NAMESPACE::half& other) noexcept
        __attribute__((annotate("cppmm:rename:copy")));
    half(const IMATH_NAMESPACE::half&& other) noexcept
        __attribute__((annotate("cppmm:ignore")));
};
} // namespace IMATH_NAMESPACE
} // namespace cppmm_bind
