#include <OpenEXR/ImfPartHelper.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct MultiViewChannelName {
    using BoundType = Imf::MultiViewChannelName;

    std::string getLayer() const;
    std::string getSuffix() const;
} CPPMM_OPAQUEBYTES;

// // FIXME: what do we do with these?
// template <typename T>
// int SplitChannels(const T& begin, const T& end, bool multipart = true,
//                   const std::string& heroView = "");

// template <class T>
// void GetChannelsInMultiPartFile(const Imf::MultiPartInputFile& file, T&
// chans);

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
