#include <OpenImageIO/typedesc.h>

#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))

namespace cppmm_bind {
namespace OIIO {

struct TypeDesc {
    enum BASETYPE {};
    enum AGGREGATE {};
    enum VECSEMANTICS {};

} CPPMM_VALUETYPE;

} // namespace OIIO
} // namespace cppmm_bind
