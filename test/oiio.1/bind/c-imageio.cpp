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

class ImageSpec {
public:
    using BoundType = OIIO::ImageSpec;

    ImageSpec(OIIO::TypeDesc format) noexcept;

    // ~ImageSpec() __attribute__((annotate("cppmm:manual:delete")));

    ImageSpec(int xres, int yres, int nchans, OIIO::TypeDesc fmt) noexcept
        CPPMM_RENAME(new_with_dimensions);

    // TODO: assign name for copy ctor arg (gets lost)
    ImageSpec(const OIIO::ImageSpec& other) CPPMM_RENAME(copy);

    OIIO::ImageSpec& operator=(const OIIO::ImageSpec& other)
        CPPMM_RENAME(assign);

    ImageSpec(OIIO::ImageSpec&& other) CPPMM_IGNORE;

    OIIO::ImageSpec& operator=(OIIO::ImageSpec&& other) CPPMM_IGNORE;

    void set_format(OIIO::TypeDesc fmt) noexcept;

    size_t channel_bytes() const noexcept;

    size_t channel_bytes(int chan, bool native) const noexcept
        CPPMM_RENAME(channel_bytes_for);

    imagesize_t scanline_bytes(bool native) const noexcept;

    static void auto_stride(stride_t& xstride, stride_t& ystride,
                            stride_t& zstride, stride_t channelsize,
                            int nchannels, int width, int height) noexcept;

    void attribute(string_view name, OIIO::TypeDesc type, const void* value);

    // Declare empty enums to get all variants converted
    enum SerialFormat {};
    enum SerialVerbose {};

    // TODO: returning strings
    std::string serialize(OIIO::ImageSpec::SerialFormat format,
                          OIIO::ImageSpec::SerialVerbose verbose) const;

    // TODO: returning arrays with an out pointer
    void get_channelformats(std::vector<OIIO::TypeDesc>& formats) const;

    void default_channel_names();

} CPPMM_OPAQUEPTR;

class ImageInput {
public:
    using BoundType = OIIO::ImageInput;

    using unique_ptr = OIIO::ImageInput::unique_ptr;

    ImageInput() CPPMM_IGNORE;

    const char* format_name(void) const;

    static unique_ptr open(const std::string& filename,
                           const OIIO::ImageSpec* config,
                           OIIO::Filesystem::IOProxy* ioproxy);

    static unique_ptr
    create(OIIO::string_view, bool, const OIIO::ImageSpec*,
           OIIO::Filesystem::IOProxy*, OIIO::string_view);

    // bool read_image(int subimage, int miplevel, int chbegin, int chend,
    //                 OIIO::TypeDesc format, void* data, stride_t xstride,
    //                 stride_t ystride, stride_t zstride,
    //                 ProgressCallback progress_callback,
    //                 void* progress_callback_data);

    std::string geterror() const;
} CPPMM_OPAQUEPTR;

bool getattribute(OIIO::string_view, OIIO::TypeDesc, void*);

} // namespace OIIO
} // namespace cppmm_bind

