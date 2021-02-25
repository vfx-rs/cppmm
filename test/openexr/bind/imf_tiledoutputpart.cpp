#include <OpenEXR/ImfTiledOutputPart.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct TiledOutputPart {
    using BoundType = Imf::TiledOutputPart;

    IMF_EXPORT
    TiledOutputPart(Imf::MultiPartOutputFile& multiPartFile, int partNumber);

    IMF_EXPORT
    const char* fileName() const;
    IMF_EXPORT
    const Imf::Header& header() const;
    IMF_EXPORT
    void setFrameBuffer(const Imf::FrameBuffer& frameBuffer);
    IMF_EXPORT
    const Imf::FrameBuffer& frameBuffer() const;
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
    void writeTiles(int dx1, int dx2, int dy1, int dy2, int lx, int ly);
    IMF_EXPORT
    void writeTiles(int dx1, int dx2, int dy1, int dy2, int l = 0) CPPMM_IGNORE;
    IMF_EXPORT
    void copyPixels(Imf::TiledInputFile& in)
        CPPMM_RENAME(copyPixels_from_tiled_input_file);
    IMF_EXPORT
    void copyPixels(Imf::InputFile& in);
    IMF_EXPORT
    void copyPixels(Imf::TiledInputPart& in)
        CPPMM_RENAME(copyPixels_from_tiled_input_part);
    IMF_EXPORT
    void copyPixels(Imf::InputPart& in) CPPMM_RENAME(copyPixels_from_part);

    IMF_EXPORT
    void updatePreviewImage(const Imf::PreviewRgba newPixels[]);
    IMF_EXPORT
    void breakTile(int dx, int dy, int lx, int ly, int offset, int length,
                   char c);

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
