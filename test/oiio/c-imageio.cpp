#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>

// FIXME: attributes in macros don't work
// #define CPPMM_IGNORE        __attribute__((annotate("cppmm:ignore")))
// #define CPPMM_MANUAL(fn)    __attribute__((annotate("cppmm:manual" # fn)))

namespace cppmm_bind {
namespace OIIO {

using ::OIIO::imagesize_t;
using ::OIIO::stride_t;
using ::OIIO::string_view;
using ::OIIO::ProgressCallback;

class ImageSpec {
    ImageSpec(::OIIO::TypeDesc format) noexcept
        __attribute__((annotate("cppmm:manual:new")));

    ~ImageSpec() __attribute__((annotate("cppmm:manual:delete")));

    ImageSpec(int xres, int yres, int nchans, ::OIIO::TypeDesc fmt) noexcept
        __attribute__((annotate("cppmm:manual:new_with_dimensions")));

    explicit ImageSpec(const ::OIIO::ROI& roi, ::OIIO::TypeDesc fmt) noexcept
        __attribute__((annotate("cppmm:manual:new_from_roi")));

    // TODO: assign name for copy ctor arg (gets lost)
    ImageSpec(const ::OIIO::ImageSpec& other)
        __attribute__((annotate("cppmm:rename:copy")));

    ::OIIO::ImageSpec& operator=(const ::OIIO::ImageSpec& other)
        __attribute__((annotate("cppmm:rename:assign")));

    ImageSpec(::OIIO::ImageSpec&& other)
        __attribute__((annotate("cppmm:ignore")));

    ::OIIO::ImageSpec& operator=(::OIIO::ImageSpec&& other)
        __attribute__((annotate("cppmm:ignore")));

    void set_format(::OIIO::TypeDesc fmt) noexcept;

    size_t channel_bytes() const noexcept;

    size_t channel_bytes(int chan, bool native) const noexcept
        __attribute__((annotate("cppmm:rename:channel_bytes_for")));

    size_t pixel_bytes(bool native) const noexcept;

    size_t pixel_bytes(int chbegin, int chend, bool native) const noexcept
        __attribute__((annotate("cppmm:rename:pixel_bytes_for")));

    imagesize_t scanline_bytes(bool native) const noexcept;

    imagesize_t tile_pixels() const noexcept;

    imagesize_t tile_bytes(bool native) const noexcept;

    imagesize_t image_pixels() const noexcept;

    imagesize_t image_bytes(bool native) const noexcept;

    bool size_t_safe() const noexcept;

    static void auto_stride(stride_t& xstride, stride_t& ystride,
                            stride_t& zstride, stride_t channelsize,
                            int nchannels, int width, int height) noexcept;

    static void auto_stride(stride_t& xstride, stride_t& ystride,
                            stride_t& zstride, ::OIIO::TypeDesc format,
                            int nchannels, int width, int height) noexcept
        __attribute__((annotate("cppmm:ignore")));

    static void auto_stride(::OIIO::stride_t& xstride, ::OIIO::TypeDesc format,
                            int nchannels) noexcept
        __attribute__((annotate("cppmm:rename:auto_stride_x")));

    void attribute(string_view name, ::OIIO::TypeDesc type, const void* value);

    void attribute(string_view name, unsigned int value)
        __attribute__((annotate("cppmm:ignore")));

    void attribute(string_view name, int value)
        __attribute__((annotate("cppmm:ignore")));

    void attribute(string_view name, float value)
        __attribute__((annotate("cppmm:ignore")));

    void attribute(string_view name, string_view value)
        __attribute__((annotate("cppmm:ignore")));

    void attribute(string_view name, ::OIIO::TypeDesc type, string_view value)
        __attribute__((annotate("cppmm:ignore")));

    void erase_attribute(string_view name, ::OIIO::TypeDesc searchtype,
                         bool casesensitive);

    ::OIIO::ParamValue* find_attribute(string_view name,
                                       ::OIIO::TypeDesc searchtype,
                                       bool casesensitive);

    const ::OIIO::ParamValue* find_attribute(string_view name,
                                             ::OIIO::TypeDesc searchtype,
                                             bool casesensitive) const
        __attribute__((annotate("cppmm:ignore")));

    const ::OIIO::ParamValue*
    find_attribute(string_view name, ::OIIO::ParamValue& tmpparam,
                   ::OIIO::TypeDesc searchtype, bool casesensitive) const
        __attribute__((annotate("cppmm:rename:find_attribute_or")));

    ::OIIO::TypeDesc getattributetype(string_view name,
                                      bool casesensitive) const;

    bool getattribute(string_view name, ::OIIO::TypeDesc type, void* value,
                      bool casesensitive) const;

    // These overloads are better implemented in Rust
    int get_int_attribute(string_view name, int defaultval) const
        __attribute__((annotate("cppmm:ignore")));
    float get_float_attribute(string_view name, float defaultval) const
        __attribute__((annotate("cppmm:ignore")));
    string_view get_string_attribute(string_view name,
                                     string_view defaultval) const
        __attribute__((annotate("cppmm:ignore")));

    // TODO: enums
    enum SerialFormat {};
    enum SerialVerbose {};

    // TODO: returning strings
    static std::string metadata_val(const ::OIIO::ParamValue& p, bool human);
    std::string serialize(::OIIO::ImageSpec::SerialFormat format,
                          ::OIIO::ImageSpec::SerialVerbose verbose) const;
    std::string to_xml() const;
    void from_xml(const char* xml);
    std::pair<string_view, int>
    decode_compression_metadata(string_view defaultcomp, int defaultqual) const
        __attribute__((annotate("cppmm:manual")));

    bool valid_tile_range(int xbegin, int xend, int ybegin, int yend,
                          int zbegin, int zend) noexcept;
    ::OIIO::TypeDesc channelformat(int chan) const;
    string_view channel_name(int chan) const;

    // TODO: returning arrays with an out pointer
    void get_channelformats(std::vector<::OIIO::TypeDesc>& formats) const;

    int channelindex(string_view name) const;

    ::OIIO::ROI roi() const noexcept;
    ::OIIO::ROI roi_full() const noexcept;
    void set_roi(const ::OIIO::ROI& r) noexcept;
    void set_roi_full(const ::OIIO::ROI& r) noexcept;
    void copy_dimensions(const ::OIIO::ImageSpec& other);
    bool undefined() const noexcept;

    ::OIIO::AttrDelegate<::OIIO::ImageSpec> operator[](string_view name)
        __attribute__((annotate("cppmm:ignore")));

    ::OIIO::AttrDelegate<const ::OIIO::ImageSpec>
    operator[](string_view name) const
        __attribute__((annotate("cppmm:ignore")));

    void default_channel_names();
    };

class ImageInput {

    using unique_ptr = ::OIIO::ImageInput::unique_ptr;

    ImageInput() __attribute__((annotate("cppmm:ignore")));
    ImageInput(const ::OIIO::ImageInput& other)
        __attribute__((annotate("cppmm:rename:copy")));

    ::OIIO::ImageInput& operator=(const ::OIIO::ImageInput& other)
        __attribute__((annotate("cppmm:rename:assign")));

    ~ImageInput() __attribute__((annotate("cppmm:ignore")));

    const char* format_name(void) const;

    static unique_ptr open(const std::string& filename,
                           const ::OIIO::ImageSpec* config,
                           ::OIIO::Filesystem::IOProxy* ioproxy);

    static std::unique_ptr<::OIIO::ImageInput>
    create(::OIIO::string_view, bool, const ::OIIO::ImageSpec*,
           ::OIIO::Filesystem::IOProxy*, ::OIIO::string_view);

    // deprecated versions
    static std::unique_ptr<::OIIO::ImageInput>
    create(const std::string& filename, bool do_open,
           const ::OIIO::ImageSpec* config,
           ::OIIO::string_view plugin_searchpath)
        __attribute__((annotate("cppmm:ignore")));

    static std::unique_ptr<::OIIO::ImageInput>
    create(const std::string& filename, const std::string& plugin_searchpath)
        __attribute__((annotate("cppmm:ignore")));

    static void destroy(::OIIO::ImageInput* x)
        __attribute__((annotate("cppmm:ignore")));

    int supports(::OIIO::string_view feature) const;

    bool valid_file(const std::string& filename) const;

    bool open(const std::string& name, ::OIIO::ImageSpec& newspec);
    bool open(const std::string& name, ::OIIO::ImageSpec& newspec,
              const ::OIIO::ImageSpec& config)
        __attribute__((annotate("cppmm:ignore")));

    const ::OIIO::ImageSpec& spec() const;

    ::OIIO::ImageSpec spec(int subimage, int miplevel)
        __attribute__((annotate("cppmm:rename:spec_copy")));

    ::OIIO::ImageSpec spec_dimensions(int subimage, int miplevel);

    bool close();

    int current_subimage() const;
    int current_miplevel() const;

    bool seek_subimage(int subimage, int miplevel);
    bool seek_subimage(int subimage, int miplevel, ::OIIO::ImageSpec& newspec)
        __attribute__((annotate("cppmm:ignore")));
    bool seek_subimage(int subimage, ::OIIO::ImageSpec& newspec)
        __attribute__((annotate("cppmm:ignore")));

    bool read_scanline(int y, int z, ::OIIO::TypeDesc format, void* data,
                       stride_t xstride);
    bool read_scanline(int y, int z, float* data)
        __attribute__((annotate("cppmm:ignore")));

    bool read_scanlines(int subimage, int miplevel, int ybegin, int yend, int z,
                        int chbegin, int chend, ::OIIO::TypeDesc format,
                        void* data, stride_t xstride, stride_t ystride);

    // deprecrated versions
    bool read_scanlines(int ybegin, int yend, int z, ::OIIO::TypeDesc format,
                        void* data, stride_t xstrid, stride_t ystrid)
        __attribute__((annotate("cppmm:ignore")));
    bool read_scanlines(int ybegin, int yend, int z, int chbegin, int chend,
                        ::OIIO::TypeDesc format, void* data, stride_t xstride,
                        stride_t ystride)
        __attribute__((annotate("cppmm:ignore")));

    bool read_tile(int x, int y, int z, ::OIIO::TypeDesc format, void* data,
                   stride_t xstride, stride_t ystride, stride_t zstride);

    bool read_tile(int x, int y, int z, float* data)
        __attribute__((annotate("cppmm:ignore")));

    bool read_tiles(int subimage, int miplevel, int xbegin, int xend,
                    int ybegin, int yend, int zbegin, int zend, int chbegin,
                    int chend, ::OIIO::TypeDesc format, void* data,
                    stride_t xstride, stride_t ystride, stride_t zstride);

    // Deprecated versions
    bool read_tiles(int xbegin, int xend, int ybegin, int yend, int zbegin,
                    int zend, ::OIIO::TypeDesc format, void* data,
                    stride_t xstride, stride_t ystride, stride_t zstride)
        __attribute__((annotate("cppmm:ignore")));
    bool read_tiles(int xbegin, int xend, int ybegin, int yend, int zbegin,
                    int zend, int chbegin, int chend, ::OIIO::TypeDesc format,
                    void* data, stride_t xstride, stride_t ystride,
                    stride_t zstride) __attribute__((annotate("cppmm:ignore")));

    bool read_image(int subimage, int miplevel, int chbegin, int chend,
                    ::OIIO::TypeDesc format, void* data, stride_t xstride,
                    stride_t ystride, stride_t zstride,
                    ProgressCallback progress_callback,
                    void* progress_callback_data);

    // DEPRECATED versions of read_image (pre-1.9 OIIO).
    bool read_image(::OIIO::TypeDesc format, void* data, stride_t xstride,
                    stride_t ystride, stride_t zstride,
                    ProgressCallback progress_callback,
                    void* progress_callback_data)
        __attribute__((annotate("cppmm:ignore")));
    bool read_image(int chbegin, int chend, ::OIIO::TypeDesc format, void* data,
                    stride_t xstride, stride_t ystride, stride_t zstride,
                    ProgressCallback progress_callback,
                    void* progress_callback_data)
        __attribute__((annotate("cppmm:ignore")));
    bool read_image(float* data) __attribute__((annotate("cppmm:ignore")));

    bool read_native_deep_scanlines(int subimage, int miplevel, int ybegin,
                                    int yend, int z, int chbegin, int chend,
                                    ::OIIO::DeepData& deepdata);
    bool read_native_deep_tiles(int subimage, int miplevel, int xbegin,
                                int xend, int ybegin, int yend, int zbegin,
                                int zend, int chbegin, int chend,
                                ::OIIO::DeepData& deepdata);
    bool read_native_deep_image(int subimage, int miplevel,
                                ::OIIO::DeepData& deepdata);

    // deprecated
    bool read_native_deep_scanlines(int ybegin, int yend, int z, int chbegin,
                                    int chend, ::OIIO::DeepData& deepdata)
        __attribute__((annotate("cppmm:ignore")));

    bool read_native_deep_tiles(int xbegin, int xend, int ybegin, int yend,
                                int zbegin, int zend, int chbegin, int chend,
                                ::OIIO::DeepData& deepdata)
        __attribute__((annotate("cppmm:ignore")));

    bool read_native_deep_image(::OIIO::DeepData& deepdata)
        __attribute__((annotate("cppmm:ignore")));

    bool read_native_scanline(int subimage, int miplevel, int y, int z,
                              void* data)
        __attribute__((annotate("cppmm:ignore")));

    bool read_native_scanlines(int subimage, int miplevel, int ybegin, int yend,
                               int z, void* data)
        __attribute__((annotate("cppmm:ignore")));

    bool read_native_scanlines(int subimage, int miplevel, int ybegin, int yend,
                               int z, int chbegin, int chend, void* data)
        __attribute__((annotate("cppmm:ignore")));

    bool read_native_tile(int subimage, int miplevel, int x, int y, int z,
                          void* data) __attribute__((annotate("cppmm:ignore")));

    bool read_native_tiles(int subimage, int miplevel, int xbegin, int xend,
                           int ybegin, int yend, int zbegin, int zend,
                           void* data)
        __attribute__((annotate("cppmm:ignore")));

    bool read_native_tiles(int subimage, int miplevel, int xbegin, int xend,
                           int ybegin, int yend, int zbegin, int zend,
                           int chbegin, int chend, void* data)
        __attribute__((annotate("cppmm:ignore")));

    int send_to_input(const char* format, ...)
        __attribute__((annotate("cppmm:ignore")));
    int send_to_client(const char* format, ...)
        __attribute__((annotate("cppmm:ignore")));

    bool set_ioproxy(::OIIO::Filesystem::IOProxy* ioproxy);

    template <typename... Args>
    void error(const char* fmt, const Args&... args) const
        __attribute__((annotate("cppmm:ignore")));

    template <typename... Args>
    void errorf(const char* fmt, const Args&... args) const
        __attribute__((annotate("cppmm:ignore")));

    template <typename... Args>
    void errorfmt(const char* fmt, const Args&... args) const
        __attribute__((annotate("cppmm:ignore")));

    template <typename... Args>
    void fmterror(const char* fmt, const Args&... args) const
        __attribute__((annotate("cppmm:ignore")));

    void threads(int n) __attribute__((annotate("cppmm:rename:set_threads")));
    int threads() const;

    void lock();
    bool try_lock();
    void unlock();

    void* operator new(size_t size) __attribute__((annotate("cppmm:ignore")));
    void operator delete(void* ptr) __attribute__((annotate("cppmm:ignore")));

    std::string geterror() const
        __attribute__((annotate("cppmm:manual:geterror")));
};

bool getattribute(::OIIO::string_view, ::OIIO::TypeDesc, void*);
} // namespace OIIO
} // namespace cppmm_bind

namespace cppmm_manual {
// FIXME: doing this doesn't work great because it will cause errors as the
// types we're using having been generated yet...
/*
using OIIO_ImageInput = OIIO::ImageInput;
void OIIO_ImageInput_geterror(OIIO_ImageInput* self, char* errormsg, int len,
                          bool clear) {
const std::string errmsg = to_cpp(self)->geterror(clear);
OIIO::Strutil::safe_strcpy(errormsg, errmsg.c_str(), len);
}
*/
} // namespace cppmm_manual
