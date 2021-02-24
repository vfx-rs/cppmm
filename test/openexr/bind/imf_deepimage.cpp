#include <OpenEXR/ImfDeepImage.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct DeepImage {
    using BoundType = Imf::DeepImage;

    // From Image
    IMFUTIL_EXPORT
    Imf::LevelMode levelMode() const;
    IMFUTIL_EXPORT
    Imf::LevelRoundingMode levelRoundingMode() const;

    IMFUTIL_EXPORT
    int numLevels() const CPPMM_THROWS(Iex::LogicExc, IEX_LOGIC_ERROR);
    IMFUTIL_EXPORT
    int numXLevels() const;
    IMFUTIL_EXPORT
    int numYLevels() const;

    IMFUTIL_EXPORT
    const IMATH_NAMESPACE::Box2i& dataWindow() const;
    IMFUTIL_EXPORT
    const IMATH_NAMESPACE::Box2i& dataWindowForLevel(int l) const;
    IMFUTIL_EXPORT
    const IMATH_NAMESPACE::Box2i& dataWindowForLevel(int lx, int ly) const;

    IMFUTIL_EXPORT
    int levelWidth(int lx) const;
    IMFUTIL_EXPORT
    int levelHeight(int ly) const;

    IMFUTIL_EXPORT
    void shiftPixels(int dx, int dy)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT);

    IMFUTIL_EXPORT
    void resize(const IMATH_NAMESPACE::Box2i& dataWindow);

    IMFUTIL_EXPORT
    virtual void resize(const IMATH_NAMESPACE::Box2i& dataWindow,
                        Imf::LevelMode levelMode,
                        Imf::LevelRoundingMode levelRoundingMode)
        CPPMM_RENAME(resize_with_mode);

    IMFUTIL_EXPORT
    void insertChannel(const std::string& name, Imf::PixelType type,
                       int xSamplingt, int ySampling, bool pLinear)
        CPPMM_RENAME(insertChannel_with);

    IMFUTIL_EXPORT
    void insertChannel(const std::string& name, const Imf::Channel& channel);

    IMFUTIL_EXPORT
    void eraseChannel(const std::string& name);
    IMFUTIL_EXPORT
    void clearChannels();

    IMFUTIL_EXPORT
    void renameChannel(const std::string& oldName, const std::string& newName)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT)
            CPPMM_THROWS(std::exception, IEX_OUT_OF_MEMORY);

    IMFUTIL_EXPORT
    void renameChannels(const Imf::RenamingMap& oldToNewNames)
        CPPMM_THROWS(Iex::ArgExc, IEX_INVALID_ARGUMENT)
            CPPMM_THROWS(std::exception, IEX_OUT_OF_MEMORY);

    // DeepImage
    IMFUTIL_EXPORT DeepImage() CPPMM_RENAME(default);

    IMFUTIL_EXPORT
    DeepImage(const IMATH_NAMESPACE::Box2i& dataWindow,
              Imf::LevelMode levelMode,
              Imf::LevelRoundingMode levelRoundingMode);

    IMFUTIL_EXPORT
    virtual ~DeepImage();

    IMFUTIL_EXPORT
    virtual Imf::DeepImageLevel& level(int l);
    IMFUTIL_EXPORT
    virtual const Imf::DeepImageLevel& level(int l) const;

    IMFUTIL_EXPORT
    virtual Imf::DeepImageLevel& level(int lx, int ly);
    IMFUTIL_EXPORT
    virtual const Imf::DeepImageLevel& level(int lx, int ly) const;

} CPPMM_OPAQUEBYTES;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
