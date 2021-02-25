#include <OpenEXR/ImfTestFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

IMF_EXPORT bool isOpenExrFile(const char fileName[]) CPPMM_IGNORE;

IMF_EXPORT bool isOpenExrFile(const char fileName[],
                              bool& isTiled) CPPMM_IGNORE;

IMF_EXPORT bool isOpenExrFile(const char fileName[], bool& isTiled,
                              bool& isDeep) CPPMM_IGNORE;

IMF_EXPORT bool isOpenExrFile(const char fileName[], bool& isTiled,
                              bool& isDeep, bool& isMultiPart);

IMF_EXPORT bool isTiledOpenExrFile(const char fileName[]);

IMF_EXPORT bool isDeepOpenExrFile(const char fileName[]);

IMF_EXPORT bool isMultiPartOpenExrFile(const char fileName[]);

IMF_EXPORT bool isOpenExrFile(Imf::IStream& is) CPPMM_IGNORE;

IMF_EXPORT bool isOpenExrFile(Imf::IStream& is, bool& isTiled) CPPMM_IGNORE;

IMF_EXPORT bool isOpenExrFile(Imf::IStream& is, bool& isTiled,
                              bool& isDeep) CPPMM_IGNORE;

IMF_EXPORT bool isOpenExrFile(Imf::IStream& is, bool& isTiled, bool& isDeep,
                              bool& isMultiPart)
    CPPMM_RENAME(stream_is_openexr_file);

IMF_EXPORT bool isTiledOpenExrFile(Imf::IStream& is)
    CPPMM_RENAME(stream_is_tiled_openexr_file);

IMF_EXPORT bool isDeepOpenExrFile(Imf::IStream& is)
    CPPMM_RENAME(stream_is_deep_openexr_file);

IMF_EXPORT bool isMultiPartOpenExrFile(Imf::IStream& is)
    CPPMM_RENAME(stream_is_multi_part_openexr_file);

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
