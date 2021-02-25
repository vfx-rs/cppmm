#include <OpenEXR/ImfName.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct Name {
    using BoundType = Imf::Name;

    IMF_EXPORT
    Name() CPPMM_RENAME(default);
    IMF_EXPORT
    Name(const char text[]);

    IMF_EXPORT
    Imf::Name& operator=(const char text[]);

    inline const char* text();
    inline const char* operator*();

    static const int SIZE = 256;
    static const int MAX_LENGTH = SIZE - 1;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
