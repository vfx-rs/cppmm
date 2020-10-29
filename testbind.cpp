#include <OpenImageIO/imageio.h>
#include <OpenImageIO/filesystem.h>

// FIXME: attributes in macros don't work
// #define CPPMM_IGNORE        __attribute__((annotate("cppmm:ignore")))
// #define CPPMM_MANUAL(fn)    __attribute__((annotate("cppmm:manual" # fn)))

namespace cppmm_bind {
namespace OIIO {
    class ImageInput {
        static std::unique_ptr<::OIIO::ImageInput> create(::OIIO::string_view, bool, const ::OIIO::ImageSpec*, ::OIIO::Filesystem::IOProxy*, ::OIIO::string_view);

        // Could specify we have a manual definition for this method, which will
        // which will be found in the namespace cppmm_manual below
        __attribute__((annotate("cppm:manual:OIIO_ImageInput_geterror")))
        std::string geterror();
    };

    bool getattribute(::OIIO::string_view, ::OIIO::TypeDesc, void*);
}
}

namespace cppmm_manual {
    void OIIO_ImageInput_geterror(char* errormsg, int len, bool clear) {
        //
    }
}
