#include <OpenEXR/ImfKeyCode.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct KeyCode {
    using BoundType = Imf::KeyCode;

    IMF_EXPORT
    KeyCode(int filmMfcCode = 0, int filmType = 0, int prefix = 0,
            int count = 0, int perfOffset = 0, int perfsPerFrame = 4,
            int perfsPerCount = 64);

    IMF_EXPORT
    KeyCode(const Imf::KeyCode& other);
    IMF_EXPORT
    ~KeyCode();
    IMF_EXPORT
    Imf::KeyCode& operator=(const Imf::KeyCode& other);

    //----------------------------
    // Access to individual fields
    //----------------------------

    IMF_EXPORT
    int filmMfcCode() const;
    IMF_EXPORT
    void setFilmMfcCode(int filmMfcCode);

    IMF_EXPORT
    int filmType() const;
    IMF_EXPORT
    void setFilmType(int filmType);

    IMF_EXPORT
    int prefix() const;
    IMF_EXPORT
    void setPrefix(int prefix);

    IMF_EXPORT
    int count() const;
    IMF_EXPORT
    void setCount(int count);

    IMF_EXPORT
    int perfOffset() const;
    IMF_EXPORT
    void setPerfOffset(int perfOffset);

    IMF_EXPORT
    int perfsPerFrame() const;
    IMF_EXPORT
    void setPerfsPerFrame(int perfsPerFrame);

    IMF_EXPORT
    int perfsPerCount() const;
    IMF_EXPORT
    void setPerfsPerCount(int perfsPerCount);

} CPPMM_VALUETYPE;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
