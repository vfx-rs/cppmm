#include <OpenEXR/ImfTiledRgbaFile.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct TiledRgbaOutputFile {
    using BoundType = Imf::TiledRgbaOutputFile;

    IMF_EXPORT
    TiledRgbaOutputFile(const char name[], const Imf::Header& header,
                        Imf::RgbaChannels rgbaChannels, int tileXSize,
                        int tileYSize, Imf::LevelMode mode,
                        Imf::LevelRoundingMode rmode, int numThreads)
        CPPMM_RENAME(with_header);

    IMF_EXPORT
    TiledRgbaOutputFile(Imf::OStream& os, const Imf::Header& header,
                        Imf::RgbaChannels rgbaChannels, int tileXSize,
                        int tileYSize, Imf::LevelMode mode,
                        Imf::LevelRoundingMode rmode, int numThreads)
        CPPMM_RENAME(from_stream_with_header);

    IMF_EXPORT
    TiledRgbaOutputFile(const char name[], int tileXSize, int tileYSize,
                        Imf::LevelMode mode, Imf::LevelRoundingMode rmode,
                        const IMATH_NAMESPACE::Box2i& displayWindow,
                        const IMATH_NAMESPACE::Box2i& dataWindow,
                        Imf::RgbaChannels rgbaChannels, float pixelAspectRatio,
                        const IMATH_NAMESPACE::V2f screenWindowCenter,
                        float screenWindowWidth, Imf::LineOrder lineOrder,
                        Imf::Compression compression, int numThreads);

    IMF_EXPORT
    virtual ~TiledRgbaOutputFile();

    IMF_EXPORT
    void setFrameBuffer(const Imf::Rgba* base, size_t xStride, size_t yStride);

    IMF_EXPORT
    const Imf::Header& header() const;
    IMF_EXPORT
    const Imf::FrameBuffer& frameBuffer() const;
    IMF_EXPORT
    const IMATH_NAMESPACE::Box2i& displayWindow() const;
    IMF_EXPORT
    const IMATH_NAMESPACE::Box2i& dataWindow() const;
    IMF_EXPORT
    float pixelAspectRatio() const;
    IMF_EXPORT
    const IMATH_NAMESPACE::V2f screenWindowCenter() const;
    IMF_EXPORT
    float screenWindowWidth() const;
    IMF_EXPORT
    Imf::LineOrder lineOrder() const;
    IMF_EXPORT
    Imf::Compression compression() const;
    IMF_EXPORT
    Imf::RgbaChannels channels() const;

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
    int levelWidth(int lx) const;
    IMF_EXPORT
    int levelHeight(int ly) const;

    IMF_EXPORT
    int numXTiles(int lx = 0) const;
    IMF_EXPORT
    int numYTiles(int ly = 0) const;

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
    void writeTile(int dx, int dy, int l = 0) CPPMM_IGNORE;
    IMF_EXPORT
    void writeTile(int dx, int dy, int lx, int ly);

    IMF_EXPORT
    void writeTiles(int dxMin, int dxMax, int dyMin, int dyMax, int lx, int ly);

    IMF_EXPORT
    void writeTiles(int dxMin, int dxMax, int dyMin, int dyMax,
                    int l = 0) CPPMM_IGNORE;

    IMF_EXPORT
    void updatePreviewImage(const Imf::PreviewRgba newPixels[]);

    IMF_EXPORT
    void breakTile(int dx, int dy, int lx, int ly, int offset, int length,
                   char c);
} CPPMM_OPAQUEBYTES;

struct TiledRgbaInputFile {
    using BoundType = Imf::TiledRgbaInputFile;

    IMF_EXPORT
    TiledRgbaInputFile(const char name[], int numThreads);

    IMF_EXPORT
    TiledRgbaInputFile(Imf::IStream& is, int numThreads)
        CPPMM_RENAME(from_stream);

    IMF_EXPORT
    TiledRgbaInputFile(const char name[], const std::string& layerName,
                       int numThreads) CPPMM_RENAME(with_layer);

    IMF_EXPORT
    TiledRgbaInputFile(Imf::IStream& is, const std::string& layerName,
                       int numThreads) CPPMM_RENAME(from_stream_with_layer);

    IMF_EXPORT
    virtual ~TiledRgbaInputFile();

    IMF_EXPORT
    void setFrameBuffer(Imf::Rgba* base, size_t xStride, size_t yStride);

    IMF_EXPORT
    void setLayerName(const std::string& layerName);

    IMF_EXPORT
    const Imf::Header& header() const;
    IMF_EXPORT
    const Imf::FrameBuffer& frameBuffer() const;
    IMF_EXPORT
    const IMATH_NAMESPACE::Box2i& displayWindow() const;
    IMF_EXPORT
    const IMATH_NAMESPACE::Box2i& dataWindow() const;
    IMF_EXPORT
    float pixelAspectRatio() const;
    IMF_EXPORT
    const IMATH_NAMESPACE::V2f screenWindowCenter() const;
    IMF_EXPORT
    float screenWindowWidth() const;
    IMF_EXPORT
    Imf::LineOrder lineOrder() const;
    IMF_EXPORT
    Imf::Compression compression() const;
    IMF_EXPORT
    Imf::RgbaChannels channels() const;
    IMF_EXPORT
    const char* fileName() const;
    IMF_EXPORT
    bool isComplete() const;

    IMF_EXPORT
    int version() const;

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
    int levelWidth(int lx) const;
    IMF_EXPORT
    int levelHeight(int ly) const;

    IMF_EXPORT
    int numXTiles(int lx = 0) const;
    IMF_EXPORT
    int numYTiles(int ly = 0) const;

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
    void readTiles(int dxMin, int dxMax, int dyMin, int dyMax, int lx, int ly);

    IMF_EXPORT
    void readTiles(int dxMin, int dxMax, int dyMin, int dyMax,
                   int l = 0) CPPMM_IGNORE;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
