#include <OpenEXR/ImfPartType.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

IMF_EXPORT bool isImage(const std::string& name);

IMF_EXPORT bool isTiled(const std::string& name);

IMF_EXPORT bool isDeepData(const std::string& name);

IMF_EXPORT bool isSupportedType(const std::string& name);

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
