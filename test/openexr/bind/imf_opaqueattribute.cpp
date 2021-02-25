#include <OpenEXR/ImfOpaqueAttribute.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct OpaqueAttribute {
    using BoundType = Imf::OpaqueAttribute;

    IMF_EXPORT
    OpaqueAttribute(const char typeName[]);
    IMF_EXPORT
    OpaqueAttribute(const Imf::OpaqueAttribute& other);

    IMF_EXPORT
    virtual ~OpaqueAttribute();

    IMF_EXPORT
    virtual const char* typeName() const;

    IMF_EXPORT
    virtual Imf::Attribute* copy() const;

    IMF_EXPORT
    virtual void writeValueTo(Imf::OStream& os, int version) const;

    IMF_EXPORT
    virtual void readValueFrom(Imf::IStream& is, int size, int version);

    IMF_EXPORT
    virtual void copyValueFrom(const Imf::Attribute& other);

    int dataSize();
    const Imf::Array<char>& data() const;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
