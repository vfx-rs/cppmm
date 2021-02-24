#include <OpenEXR/ImfDeepTiledInputFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepTiledInputFile {
    using BoundType = Imf::DeepTiledInputFile;
    IMF_EXPORT
    DeepTiledInputFile(const char fileName[], int numThreads);
    IMF_EXPORT
    DeepTiledInputFile(Imf::IStream& is, int numThreads)
        CPPMM_RENAME(from_stream);
    IMF_EXPORT
    virtual ~DeepTiledInputFile();
    IMF_EXPORT
    const char* fileName() const;
    IMF_EXPORT
    const Imf::Header& header() const;

    IMF_EXPORT
    int version() const;
    IMF_EXPORT
    void setFrameBuffer(const Imf::DeepFrameBuffer& frameBuffer);

    IMF_EXPORT
    const Imf::DeepFrameBuffer& frameBuffer() const;

    IMF_EXPORT
    bool isComplete() const;
    IMF_EXPORT
    unsigned int tileXSize() const;
    IMF_EXPORT
    unsigned int tileYSize() const;
    IMF_EXPORT
    Imf::LevelMode levelMode() const;
    IMF_EXPORT
    Imf::LevelRoundingMode levelRoundingMode() const;

    IMF_EXPORT
    int numLevels() const;
    IMF_EXPORT
    int numXLevels() const;
    IMF_EXPORT
    int numYLevels() const;
    IMF_EXPORT
    bool isValidLevel(int lx, int ly) const;
    IMF_EXPORT
    size_t totalTiles() const;

    IMF_EXPORT
    int levelWidth(int lx) const;
    IMF_EXPORT
    int levelHeight(int ly) const;

    IMF_EXPORT
    int numXTiles(int lx) const;
    IMF_EXPORT
    int numYTiles(int ly) const;

    IMF_EXPORT
    IMATH_NAMESPACE::Box2i dataWindowForLevel(int l = 0) const CPPMM_IGNORE;
    IMF_EXPORT
    IMATH_NAMESPACE::Box2i dataWindowForLevel(int lx, int ly) const;

    IMF_EXPORT
    IMATH_NAMESPACE::Box2i dataWindowForTile(int dx, int dy,
                                             int l = 0) const CPPMM_IGNORE;

    IMF_EXPORT
    IMATH_NAMESPACE::Box2i dataWindowForTile(int dx, int dy, int lx,
                                             int ly) const;

    IMF_EXPORT
    void readTile(int dx, int dy, int l = 0) CPPMM_IGNORE;
    IMF_EXPORT
    void readTile(int dx, int dy, int lx, int ly);

    IMF_EXPORT
    void readTiles(int dx1, int dx2, int dy1, int dy2, int lx, int ly);

    IMF_EXPORT
    void readTiles(int dx1, int dx2, int dy1, int dy2, int l = 0) CPPMM_IGNORE;

    IMF_EXPORT
    void rawTileData(int& dx, int& dy, int& lx, int& ly, char* pixelData,
                     Imf::Int64& dataSize) const;

    IMF_EXPORT
    void readPixelSampleCount(int dx, int dy, int l = 0) CPPMM_IGNORE;
    IMF_EXPORT
    void readPixelSampleCount(int dx, int dy, int lx, int ly);

    IMF_EXPORT
    void readPixelSampleCounts(int dx1, int dx2, int dy1, int dy2, int lx,
                               int ly);

    IMF_EXPORT
    void readPixelSampleCounts(int dx1, int dx2, int dy1, int dy2,
                               int l = 0) CPPMM_IGNORE;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
