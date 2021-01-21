#include <OpenImageIO/typedesc.h>

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_MANUAL(x) __attribute__((annotate("cppmm:manual:" #x)))

#define CPPMM_OPAQUEPTR __attribute__((annotate("cppmm:opaqueptr")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))

namespace cppmm_bind {
namespace OIIO_NAMESPACE {

// alias the main library namespace with a convenient short form here
namespace OIIO = ::OIIO_NAMESPACE;

struct TypeDesc {
    enum BASETYPE {};
    enum AGGREGATE {};
    enum VECSEMANTICS {};

} CPPMM_VALUETYPE;

} // namespace OIIO
} // namespace cppmm_bind
