#include <OpenEXR/ImfFramesPerSecond.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

inline Imf::Rational fps_23_976();
inline Imf::Rational fps_24();
inline Imf::Rational fps_25();
inline Imf::Rational fps_29_97();
inline Imf::Rational fps_30();
inline Imf::Rational fps_47_952();
inline Imf::Rational fps_48();
inline Imf::Rational fps_50();
inline Imf::Rational fps_59_94();
inline Imf::Rational fps_60();

IMF_EXPORT Imf::Rational guessExactFps(double fps)
    CPPMM_RENAME(guessExactFps_f64);
IMF_EXPORT Imf::Rational guessExactFps(const Imf::Rational& fps);

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
