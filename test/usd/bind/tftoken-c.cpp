#include <pxr/base/tf/token.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace PXR_INTERNAL_NS {

namespace pxr = ::PXR_INTERNAL_NS;

class TfToken {
public:
    using BoundType = pxr::TfToken;

    TfToken(pxr::TfToken const& rhs) CPPMM_RENAME(copy);
    pxr::TfToken& operator=(pxr::TfToken const& rhs) CPPMM_RENAME(assign);
    ~TfToken() CPPMM_RENAME(destruct);

    explicit TfToken(char const* s) CPPMM_RENAME(from_string);

    size_t Hash() const;
    size_t size() const;
    char const* GetText() const;
    char const* data() const;
    bool operator==(pxr::TfToken const& o) const;
    bool operator!=(pxr::TfToken const& o) const;
    bool operator==(const char* o) const CPPMM_RENAME(eq_string);
    bool operator!=(const char* o) const CPPMM_RENAME(neq_string);
    bool operator<(pxr::TfToken const& r) const;

    bool IsEmpty() const;
    bool IsImmortal() const;

} CPPMM_OPAQUEBYTES;

} // namespace PXR_INTERNAL_NS

} // namespace cppmm_bind
