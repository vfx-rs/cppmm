#include <OpenEXR/ImfConvert.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

IMF_EXPORT unsigned int halfToUint(half h);
IMF_EXPORT unsigned int floatToUint(float f);

IMF_EXPORT half uintToHalf(unsigned int ui);
IMF_EXPORT half floatToHalf(float f);

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
