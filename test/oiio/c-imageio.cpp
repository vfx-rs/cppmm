#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>

// FIXME: attributes in macros don't work
// #define CPPMM_IGNORE        __attribute__((annotate("cppmm:ignore")))
// #define CPPMM_MANUAL(fn)    __attribute__((annotate("cppmm:manual" # fn)))

namespace cppmm_bind {
namespace OIIO {

class ImageSpec {
    void default_channel_names();
};

class ImageInput {
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

    int supports(::OIIO::string_view feature) const;

    bool valid_file(const std::string& filename) const;

    bool open(const std::string& name, ::OIIO::ImageSpec& newspec,
              const ::OIIO::ImageSpec& config);

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
                       ::OIIO::stride_t xstride);
    bool read_scanline(int y, int z, float* data)
        __attribute__((annotate("cppmm:ignore")));

    bool read_scanlines(int subimage, int miplevel, int ybegin, int yend, int z,
                        int chbegin, int chend, ::OIIO::TypeDesc format,
                        void* data, ::OIIO::stride_t xstride,
                        ::OIIO::stride_t ystride);

    // deprecrated versions
    bool read_scanlines(int ybegin, int yend, int z, ::OIIO::TypeDesc format,
                        void* data, ::OIIO::stride_t xstrid,
                        ::OIIO::stride_t ystrid)
        __attribute__((annotate("cppmm:ignore")));
    bool read_scanlines(int ybegin, int yend, int z, int chbegin, int chend,
                        ::OIIO::TypeDesc format, void* data,
                        ::OIIO::stride_t xstride, ::OIIO::stride_t ystride)
        __attribute__((annotate("cppmm:ignore")));

    bool read_tile(int x, int y, int z, ::OIIO::TypeDesc format, void* data,
                   ::OIIO::stride_t xstride, ::OIIO::stride_t ystride,
                   ::OIIO::stride_t zstride);

    bool read_tiles(int subimage, int miplevel, int xbegin, int xend,
                    int ybegin, int yend, int zbegin, int zend, int chbegin,
                    int chend, ::OIIO::TypeDesc format, void* data,
                    ::OIIO::stride_t xstride, ::OIIO::stride_t ystride,
                    ::OIIO::stride_t zstride);

    // Deprecated versions
    bool read_tiles(int xbegin, int xend, int ybegin, int yend, int zbegin,
                    int zend, ::OIIO::TypeDesc format, void* data,
                    ::OIIO::stride_t xstride, ::OIIO::stride_t ystride,
                    ::OIIO::stride_t zstride)
        __attribute__((annotate("cppmm:ignore")));
    bool read_tiles(int xbegin, int xend, int ybegin, int yend, int zbegin,
                    int zend, int chbegin, int chend, ::OIIO::TypeDesc format,
                    void* data, ::OIIO::stride_t xstride,
                    ::OIIO::stride_t ystride, ::OIIO::stride_t zstride)
        __attribute__((annotate("cppmm:ignore")));

    // Could specify we have a manual definition for this method,
    // which will be found in the namespace cppmm_manual below
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
