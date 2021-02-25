#include <OpenEXR/ImfTimeCode.h>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace OPENEXR_IMF_INTERNAL_NAMESPACE {

namespace Imf = ::OPENEXR_IMF_INTERNAL_NAMESPACE;

struct TimeCode {
    using BoundType = Imf::TimeCode;
    enum Packing {};

    IMF_EXPORT
    TimeCode() CPPMM_RENAME(default); // all fields set to 0 or false

    IMF_EXPORT
    TimeCode(int hours, int minutes, int seconds, int frame,
             bool dropFrame = false, bool colorFrame = false,
             bool fieldPhase = false, bool bgf0 = false, bool bgf1 = false,
             bool bgf2 = false, int binaryGroup1 = 0, int binaryGroup2 = 0,
             int binaryGroup3 = 0, int binaryGroup4 = 0, int binaryGroup5 = 0,
             int binaryGroup6 = 0, int binaryGroup7 = 0, int binaryGroup8 = 0);

    IMF_EXPORT
    TimeCode(unsigned int timeAndFlags, unsigned int userData,
             Imf::TimeCode::Packing packing) CPPMM_RENAME(from_time_and_flags);

    IMF_EXPORT
    TimeCode(const Imf::TimeCode& other);

    ~TimeCode() = default;

    IMF_EXPORT
    Imf::TimeCode& operator=(const Imf::TimeCode& other);

    //----------------------------
    // Access to individual fields
    //----------------------------

    IMF_EXPORT
    int hours() const;
    IMF_EXPORT
    void setHours(int value);

    IMF_EXPORT
    int minutes() const;
    IMF_EXPORT
    void setMinutes(int value);

    IMF_EXPORT
    int seconds() const;
    IMF_EXPORT
    void setSeconds(int value);

    IMF_EXPORT
    int frame() const;
    IMF_EXPORT
    void setFrame(int value);

    IMF_EXPORT
    bool dropFrame() const;
    IMF_EXPORT
    void setDropFrame(bool value);

    IMF_EXPORT
    bool colorFrame() const;
    IMF_EXPORT
    void setColorFrame(bool value);

    IMF_EXPORT
    bool fieldPhase() const;
    IMF_EXPORT
    void setFieldPhase(bool value);

    IMF_EXPORT
    bool bgf0() const;
    IMF_EXPORT
    void setBgf0(bool value);

    IMF_EXPORT
    bool bgf1() const;
    IMF_EXPORT
    void setBgf1(bool value);

    IMF_EXPORT
    bool bgf2() const;
    IMF_EXPORT
    void setBgf2(bool value);

    IMF_EXPORT
    int binaryGroup(int group) const; // group must be between 1 and 8
    IMF_EXPORT
    void setBinaryGroup(int group, int value);

    IMF_EXPORT
    unsigned int timeAndFlags(Imf::TimeCode::Packing packing) const;

    IMF_EXPORT
    void setTimeAndFlags(unsigned int value, Imf::TimeCode::Packing packing);

    IMF_EXPORT
    unsigned int userData() const;

    IMF_EXPORT
    void setUserData(unsigned int value);

    //---------
    // Equality
    //---------

    IMF_EXPORT
    bool operator==(const Imf::TimeCode& v) const;
    IMF_EXPORT
    bool operator!=(const Imf::TimeCode& v) const;
} CPPMM_VALUETYPE;

} // namespace OPENEXR_IMF_INTERNAL_NAMESPACE

} // namespace cppmm_bind
