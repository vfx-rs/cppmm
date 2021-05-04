#pragma once
#include <c-imageio.h>


#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>
#include <cstring>


inline OpenImageIO_v2_2::ImageSpec::SerialFormat const & OIIO_ImageSpec_SerialFormat_to_cpp_ref(
    OIIO_ImageSpec_SerialFormat const * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialFormat const * >(rhs));
}

inline OpenImageIO_v2_2::ImageSpec::SerialFormat & OIIO_ImageSpec_SerialFormat_to_cpp_ref(
    OIIO_ImageSpec_SerialFormat * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialFormat * >(rhs));
}

inline OpenImageIO_v2_2::ImageSpec::SerialFormat const * OIIO_ImageSpec_SerialFormat_to_cpp(
    OIIO_ImageSpec_SerialFormat const * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialFormat const * >(rhs);
}

inline OpenImageIO_v2_2::ImageSpec::SerialFormat * OIIO_ImageSpec_SerialFormat_to_cpp(
    OIIO_ImageSpec_SerialFormat * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialFormat * >(rhs);
}

inline void to_c(
    OIIO_ImageSpec_SerialFormat const * * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialFormat const & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_SerialFormat const * >(&(rhs));
}

inline void to_c(
    OIIO_ImageSpec_SerialFormat const * * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialFormat const * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_SerialFormat const * >(rhs);
}

inline void to_c(
    OIIO_ImageSpec_SerialFormat * * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialFormat & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_SerialFormat * >(&(rhs));
}

inline void to_c(
    OIIO_ImageSpec_SerialFormat * * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialFormat * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_SerialFormat * >(rhs);
}

inline void to_c_copy(
    OIIO_ImageSpec_SerialFormat * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialFormat const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

inline OpenImageIO_v2_2::ImageSpec::SerialVerbose const & OIIO_ImageSpec_SerialVerbose_to_cpp_ref(
    OIIO_ImageSpec_SerialVerbose const * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialVerbose const * >(rhs));
}

inline OpenImageIO_v2_2::ImageSpec::SerialVerbose & OIIO_ImageSpec_SerialVerbose_to_cpp_ref(
    OIIO_ImageSpec_SerialVerbose * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialVerbose * >(rhs));
}

inline OpenImageIO_v2_2::ImageSpec::SerialVerbose const * OIIO_ImageSpec_SerialVerbose_to_cpp(
    OIIO_ImageSpec_SerialVerbose const * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialVerbose const * >(rhs);
}

inline OpenImageIO_v2_2::ImageSpec::SerialVerbose * OIIO_ImageSpec_SerialVerbose_to_cpp(
    OIIO_ImageSpec_SerialVerbose * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ImageSpec::SerialVerbose * >(rhs);
}

inline void to_c(
    OIIO_ImageSpec_SerialVerbose const * * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialVerbose const & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_SerialVerbose const * >(&(rhs));
}

inline void to_c(
    OIIO_ImageSpec_SerialVerbose const * * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialVerbose const * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_SerialVerbose const * >(rhs);
}

inline void to_c(
    OIIO_ImageSpec_SerialVerbose * * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialVerbose & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_SerialVerbose * >(&(rhs));
}

inline void to_c(
    OIIO_ImageSpec_SerialVerbose * * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialVerbose * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_SerialVerbose * >(rhs);
}

inline void to_c_copy(
    OIIO_ImageSpec_SerialVerbose * lhs
    , OpenImageIO_v2_2::ImageSpec::SerialVerbose const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

/** Default constructor is an undefined region. Note that this is also
interpreted as All(). */

/** Is a region defined? */

/** @{
 @name Spatial size functions.
 The width, height, and depth of the region. */



/** Number of channels in the region.  Beware -- this defaults to a
huge number, and to be meaningful you must consider
std::min (imagebuf.nchannels(), roi.nchannels()). */

/** Total number of pixels in the region. */

inline OpenImageIO_v2_2::ROI const & to_cpp_ref(
    OIIO_ROI_t const * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ROI const * >(rhs));
}

inline OpenImageIO_v2_2::ROI & to_cpp_ref(
    OIIO_ROI_t * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ROI * >(rhs));
}

inline OpenImageIO_v2_2::ROI const * to_cpp(
    OIIO_ROI_t const * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ROI const * >(rhs);
}

inline OpenImageIO_v2_2::ROI * to_cpp(
    OIIO_ROI_t * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ROI * >(rhs);
}

inline void to_c(
    OIIO_ROI_t const * * lhs
    , OpenImageIO_v2_2::ROI const & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ROI_t const * >(&(rhs));
}

inline void to_c(
    OIIO_ROI_t const * * lhs
    , OpenImageIO_v2_2::ROI const * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ROI_t const * >(rhs);
}

inline void to_c(
    OIIO_ROI_t * * lhs
    , OpenImageIO_v2_2::ROI & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ROI_t * >(&(rhs));
}

inline void to_c(
    OIIO_ROI_t * * lhs
    , OpenImageIO_v2_2::ROI * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ROI_t * >(rhs);
}

inline void to_c_copy(
    OIIO_ROI_t * lhs
    , OpenImageIO_v2_2::ROI const & rhs)
{
        memcpy(lhs, &(rhs), sizeof(*(lhs)));
}

/** Constructor: given just the data format, set all other fields to
something reasonable. */

/** Constructs an `ImageSpec` with the given x and y resolution, number
of channels, and pixel data format.

All other fields are set to the obvious defaults -- the image is an
ordinary 2D image (not a volume), the image is not offset or a crop
of a bigger image, the image is scanline-oriented (not tiled),
channel names are "R", "G", "B"' and "A" (up to and including 4
channels, beyond that they are named "channel *n*"), the fourth
channel (if it exists) is assumed to be alpha. */

/** Set the data format, and clear any per-channel format information
in `channelformats`. */

/** Sets the `channelnames` to reasonable defaults for the number of
channels.  Specifically, channel names are set to "R", "G", "B,"
and "A" (up to and including 4 channels, beyond that they are named
"channel*n*". */

/** Returns the number of bytes comprising each channel of each pixel
(i.e., the size of a single value of the type described by the
`format` field). */

/** Return the number of bytes needed for the single specified
channel.  If native is false (default), compute the size of one
channel of `this->format`, but if native is true, compute the size
of the channel in terms of the "native" data format of that
channel as stored in the file. */

/** Returns the number of bytes comprising each scanline, i.e.,
`pixel_bytes(native) * width` This will return
`std::numeric_limits<imagesize_t>::max()` in the event of an
overflow where it's not representable in an `imagesize_t`. */

/** Returns, as a string, a serialized version of the `ImageSpec`. The
`format` may be either `ImageSpec::SerialText` or
`ImageSpec::SerialXML`. The `verbose` argument may be one of:
`ImageSpec::SerialBrief` (just resolution and other vital
statistics, one line for `SerialText`, `ImageSpec::SerialDetailed`
(contains all metadata in original form), or
`ImageSpec::SerialDetailedHuman` (contains all metadata, in many
cases with human-readable explanation). */



inline OpenImageIO_v2_2::ImageSpec const & to_cpp_ref(
    OIIO_ImageSpec_t const * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec const * >(rhs));
}

inline OpenImageIO_v2_2::ImageSpec & to_cpp_ref(
    OIIO_ImageSpec_t * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ImageSpec * >(rhs));
}

inline OpenImageIO_v2_2::ImageSpec const * to_cpp(
    OIIO_ImageSpec_t const * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ImageSpec const * >(rhs);
}

inline OpenImageIO_v2_2::ImageSpec * to_cpp(
    OIIO_ImageSpec_t * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ImageSpec * >(rhs);
}

inline void to_c(
    OIIO_ImageSpec_t const * * lhs
    , OpenImageIO_v2_2::ImageSpec const & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_t const * >(&(rhs));
}

inline void to_c(
    OIIO_ImageSpec_t const * * lhs
    , OpenImageIO_v2_2::ImageSpec const * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_t const * >(rhs);
}

inline void to_c(
    OIIO_ImageSpec_t * * lhs
    , OpenImageIO_v2_2::ImageSpec & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_t * >(&(rhs));
}

inline void to_c(
    OIIO_ImageSpec_t * * lhs
    , OpenImageIO_v2_2::ImageSpec * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageSpec_t * >(rhs);
}

inline void to_c_copy(
    OIIO_ImageSpec_t * * lhs
    , OpenImageIO_v2_2::ImageSpec const & rhs)
{
        OpenImageIO_v2_2__ImageSpec_copy(lhs, reinterpret_cast<OIIO_ImageSpec_t const * >(&(rhs)));
}

/** Return the name of the format implemented by this class. */

/** If any of the API routines returned false indicating an error, this
method will return the error string (and clear any error flags).  If
no error has occurred since the last time `geterror()` was called,
it will return an empty string. */

inline OpenImageIO_v2_2::ImageInput const & to_cpp_ref(
    OIIO_ImageInput_t const * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ImageInput const * >(rhs));
}

inline OpenImageIO_v2_2::ImageInput & to_cpp_ref(
    OIIO_ImageInput_t * rhs)
{
        return *(reinterpret_cast<OpenImageIO_v2_2::ImageInput * >(rhs));
}

inline OpenImageIO_v2_2::ImageInput const * to_cpp(
    OIIO_ImageInput_t const * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ImageInput const * >(rhs);
}

inline OpenImageIO_v2_2::ImageInput * to_cpp(
    OIIO_ImageInput_t * rhs)
{
        return reinterpret_cast<OpenImageIO_v2_2::ImageInput * >(rhs);
}

inline void to_c(
    OIIO_ImageInput_t const * * lhs
    , OpenImageIO_v2_2::ImageInput const & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageInput_t const * >(&(rhs));
}

inline void to_c(
    OIIO_ImageInput_t const * * lhs
    , OpenImageIO_v2_2::ImageInput const * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageInput_t const * >(rhs);
}

inline void to_c(
    OIIO_ImageInput_t * * lhs
    , OpenImageIO_v2_2::ImageInput & rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageInput_t * >(&(rhs));
}

inline void to_c(
    OIIO_ImageInput_t * * lhs
    , OpenImageIO_v2_2::ImageInput * rhs)
{
        *(lhs) = reinterpret_cast<OIIO_ImageInput_t * >(rhs);
}

/** Union of two regions, the smallest region containing both. */

/** Intersection of two regions. */
