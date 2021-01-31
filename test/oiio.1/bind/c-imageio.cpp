#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {
namespace OIIO_NAMESPACE {

// alias the main library namespace with a convenient short form here
namespace OIIO = ::OIIO_NAMESPACE;

using OIIO::imagesize_t;
using OIIO::ProgressCallback;
using OIIO::stride_t;
using OIIO::string_view;

struct ROI {
    using BoundType = OIIO::ROI;
    constexpr ROI() noexcept CPPMM_RENAME(default);
    constexpr bool defined() const noexcept;

    constexpr int width () const noexcept;
    constexpr int height () const noexcept;
    constexpr int depth () const noexcept;
    constexpr int nchannels () const noexcept;
    constexpr imagesize_t npixels () const noexcept;

    static constexpr OIIO::ROI All () noexcept;

    // FIXME: how do we match these?
    friend constexpr bool operator== (const OIIO::ROI &a, const OIIO::ROI &b) noexcept;
    friend constexpr bool operator!= (const OIIO::ROI &a, const OIIO::ROI &b) noexcept;
} CPPMM_VALUETYPE;

constexpr OIIO::ROI roi_union (const OIIO::ROI &A, const OIIO::ROI &B) noexcept;
constexpr OIIO::ROI roi_intersection (const OIIO::ROI &A, const OIIO::ROI &B) noexcept;


} // namespace OIIO
} // namespace cppmm_bind

