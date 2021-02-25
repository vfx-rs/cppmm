#include <OpenEXR/ImfIO.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct OStream {
    using BoundType = Imf::OStream;

    IMF_EXPORT
    virtual ~OStream();

    virtual void write(const char c[/*n*/], int n) = 0;
    virtual Imf::Int64 tellp() = 0;

    virtual void seekp(Imf::Int64 pos) = 0;

    IMF_EXPORT
    const char* fileName() const;

} CPPMM_OPAQUEPTR;

struct IStream {
    using BoundType = Imf::IStream;

    IMF_EXPORT
    virtual ~IStream();

    IMF_EXPORT
    virtual bool isMemoryMapped() const;

    virtual bool read(char c[/*n*/], int n) = 0;

    IMF_EXPORT
    virtual char* readMemoryMapped(int n);

    virtual Imf::Int64 tellg() = 0;

    virtual void seekg(Imf::Int64 pos) = 0;

    IMF_EXPORT
    virtual void clear();
    IMF_EXPORT
    const char* fileName() const;
} CPPMM_OPAQUEPTR;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
