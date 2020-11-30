#include <pxr/base/tf/token.h>

#define CPPMM_IGNORE __attribute__((annotate("cppmm:ignore")))
#define CPPMM_RENAME(x) __attribute__((annotate("cppmm:rename:" #x)))
#define CPPMM_OPAQUEBYTES __attribute__((annotate("cppmm:opaquebytes")))
#define CPPMM_VALUETYPE __attribute__((annotate("cppmm:valuetype")))

namespace cppmm_bind {

namespace PXR_INTERNAL_NS {

namespace pxr = PXR_INTERNAL_NS;

class TfToken {
    TfToken(pxr::TfToken const& rhs) CPPMM_RENAME(copy);
    TfToken& operator= (pxr::TfToken const& rhs) CPPMM_RENAME(assign);
    ~TfToken() CPPMM_RENAME(destruct);

    explicit TfToken(char const* s) CPPMM_RENAME(from_string);

    size_t Hash() const;
    size_t size() const;
    char const* GetText() const;
    char const *data() const;
    bool operator==(TfToken const& o) const;
    bool operator!=(TfToken const& o) const;
    bool operator==(const char * o) const CPPMM_RENAME(eq_string);
    bool operator!=(const char * o) const CPPMM_RENAME(neq_string);
    bool operator<(TfToken const& r) const;

    bool IsEmpty() const;
    bool IsImmortal() const;

} CPPMM_OPAQUEBYTES;

}

}
