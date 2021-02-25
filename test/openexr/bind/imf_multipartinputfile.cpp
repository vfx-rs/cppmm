#include <OpenEXR/ImfMultiPartInputFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct MultiPartInputFile {
    using BoundType = Imf::MultiPartInputFile;

    IMF_EXPORT
    MultiPartInputFile(const char fileName[], int numThreads,
                       bool reconstructChunkOffsetTable = true);

    IMF_EXPORT
    MultiPartInputFile(Imf::IStream& is, int numThreads,
                       bool reconstructChunkOffsetTable = true)
        CPPMM_RENAME(from_stream);

    IMF_EXPORT
    virtual ~MultiPartInputFile();

    // ----------------------
    // Count of number of parts in file
    // ---------------------
    IMF_EXPORT
    int parts() const;

    //----------------------
    // Access to the headers
    //----------------------

    IMF_EXPORT
    const Imf::Header& header(int n) const;

    //----------------------------------
    // Access to the file format version
    //----------------------------------

    IMF_EXPORT
    int version() const;

    // =----------------------------------------
    // Check whether the entire chunk offset
    // table for the part is written correctly
    // -----------------------------------------
    IMF_EXPORT
    bool partComplete(int part) const;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
