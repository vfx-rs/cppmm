#pragma once

#ifdef __cplusplus
extern "C" {
#endif



typedef struct OIIO_ImageSpec OIIO_ImageSpec;

OIIO_ImageSpec*  OIIO_ImageSpec_assign(OIIO_ImageSpec* self, const OIIO_ImageSpec* );

/// Searches `extra_attribs` for any attributes matching `name` (as a
/// regular expression), removing them entirely from `extra_attribs`. If
/// `searchtype` is anything other than `TypeDesc::UNKNOWN`, matches
/// will be restricted only to attributes with the given type. The name
/// comparison will be case-sensitive if `casesensitive` is true,
/// otherwise in a case-insensitive manner.
void  OIIO_ImageSpec_erase_attribute(OIIO_ImageSpec* self, const char* name, OIIO_TypeDesc searchtype, _Bool casesensitive);

/// Returns, as a string, a serialized version of the `ImageSpec`. The
/// `format` may be either `ImageSpec::SerialText` or
/// `ImageSpec::SerialXML`. The `verbose` argument may be one of:
/// `ImageSpec::SerialBrief` (just resolution and other vital
/// statistics, one line for `SerialText`, `ImageSpec::SerialDetailed`
/// (contains all metadata in original form), or
/// `ImageSpec::SerialDetailedHuman` (contains all metadata, in many
/// cases with human-readable explanation).
char*  OIIO_ImageSpec_serialize(const OIIO_ImageSpec* self, OIIO_ImageSpec_SerialFormat format, OIIO_ImageSpec_SerialVerbose verbose);

/// Returns the number of bytes comprising an entire image of these
/// dimensions, i.e.,
///     `pixel_bytes(native) * width * height * depth`
/// This will return `std::numeric_limits<image size_t>::max()` in the
/// event of an overflow where it's not representable in an
/// `imagesize_t`. If `native` is false (default), assume all channels
/// are in `this->format`, but if `native` is true, compute the size of
/// a pixel in the "native" data format of the file (these may differ in
/// the case of per-channel formats).
unsigned long  OIIO_ImageSpec_image_bytes(const OIIO_ImageSpec* self, _Bool native);

/// Helper function to verify that the given pixel range exactly covers
/// a set of tiles.  Also returns false if the spec indicates that the
/// image isn't tiled at all.
_Bool  OIIO_ImageSpec_valid_tile_range(OIIO_ImageSpec* self, int xbegin, int xend, int ybegin, int yend, int zbegin, int zend);

/// Returns the number of bytes comprising each channel of each pixel
/// (i.e., the size of a single value of the type described by the
/// `format` field).
unsigned long  OIIO_ImageSpec_channel_bytes(const OIIO_ImageSpec* self);

/// Return the number of pixels for an entire image.  This will
/// return `std::numeric_limits<imagesize_t>::max()` in the event of
/// an overflow where it's not representable in an `imagesize_t`.
unsigned long  OIIO_ImageSpec_image_pixels(const OIIO_ImageSpec* self);

/// Adjust the stride values, if set to AutoStride, to be the right
/// sizes for contiguous data with the given format, channels,
/// width, height.
void  OIIO_ImageSpec_auto_stride(long* xstride, long* ystride, long* zstride, long channelsize, int nchannels, int width, int height);

/// Return the number of pixels comprising a tile (or 0 if it is not a
/// tiled image).  This will return
/// `std::numeric_limits<imagesize_t>::max()` in the event of an
/// overflow where it's not representable in an `imagesize_t`.
unsigned long  OIIO_ImageSpec_tile_pixels(const OIIO_ImageSpec* self);

/// Returns the number of bytes comprising each scanline, i.e.,
/// `pixel_bytes(native) * width` This will return
/// `std::numeric_limits<imagesize_t>::max()` in the event of an
/// overflow where it's not representable in an `imagesize_t`.
unsigned long  OIIO_ImageSpec_scanline_bytes(const OIIO_ImageSpec* self, _Bool native);

/// Searches `extra_attribs` for an attribute matching `name`, returning
/// a pointer to the attribute record, or NULL if there was no match.
/// If `searchtype` is anything other than `TypeDesc::UNKNOWN`, matches
/// will be restricted only to attributes with the given type. The name
/// comparison will be exact if `casesensitive` is true, otherwise in a
/// case-insensitive manner if `caseinsensitive` is false.
OIIO_ParamValue*  OIIO_ImageSpec_find_attribute(OIIO_ImageSpec* self, const char* name, OIIO_TypeDesc searchtype, _Bool casesensitive);

/// Sets the `channelnames` to reasonable defaults for the number of
/// channels.  Specifically, channel names are set to "R", "G", "B,"
/// and "A" (up to and including 4 channels, beyond that they are named
/// "channel*n*".
void  OIIO_ImageSpec_default_channel_names(OIIO_ImageSpec* self);

/// Set the data format, and clear any per-channel format information
/// in `channelformats`.
void  OIIO_ImageSpec_set_format(OIIO_ImageSpec* self, OIIO_TypeDesc fmt);

/// Adjust xstride, if set to AutoStride, to be the right size for
/// contiguous data with the given format and channels.
void  OIIO_ImageSpec_auto_stride_x(long* xstride, OIIO_TypeDesc format, int nchannels);

/// Verify that on this platform, a `size_t` is big enough to hold the
/// number of bytes (and pixels) in a scanline, a tile, and the
/// whole image.  If this returns false, the image is much too big
/// to allocate and read all at once, so client apps beware and check
/// these routines for overflows!
_Bool  OIIO_ImageSpec_size_t_safe(const OIIO_ImageSpec* self);


void  OIIO_ImageSpec_copy(OIIO_ImageSpec* self, const OIIO_ImageSpec* );

/// Add a metadata attribute to `extra_attribs`, with the given name and
/// data type. The `value` pointer specifies the address of the data to
/// be copied.
void  OIIO_ImageSpec_attribute(OIIO_ImageSpec* self, const char* name, OIIO_TypeDesc type, const void* value);

/// Returns the number of bytes comprising an image tile, i.e.,
///     `pixel_bytes(native) * tile_width * tile_height * tile_depth`
/// If native is false (default), assume all channels are in
/// `this->format`, but if `native` is true, compute the size of a pixel
/// in the "native" data format of the file (these may differ in the
/// case of per-channel formats).
unsigned long  OIIO_ImageSpec_tile_bytes(const OIIO_ImageSpec* self, _Bool native);

/// Return the number of bytes for each pixel (counting all channels).
/// If `native` is false (default), assume all channels are in
/// `this->format`, but if `native` is true, compute the size of a pixel
/// in the "native" data format of the file (these may differ in
/// the case of per-channel formats).
unsigned long  OIIO_ImageSpec_pixel_bytes(const OIIO_ImageSpec* self, _Bool native);

/// If the `ImageSpec` contains the named attribute and its type matches
/// `type`, copy the attribute value into the memory pointed to by `val`
/// (it is up to the caller to ensure there is enough space) and return
/// `true`. If no such attribute is found, or if it doesn't match the
/// type, return `false` and do not modify `val`.
///
/// EXAMPLES:
///
///     ImageSpec spec;
///     ...
///     // Retrieving an integer attribute:
///     int orientation = 0;
///     spec.getattribute ("orientation", TypeInt, &orientation);
///
///     // Retrieving a string attribute with a char*:
///     const char* compression = nullptr;
///     spec.getattribute ("compression", TypeString, &compression);
///
///     // Alternately, retrieving a string with a ustring:
///     ustring compression;
///     spec.getattribute ("compression", TypeString, &compression);
///
/// Note that when passing a string, you need to pass a pointer to the
/// `char*`, not a pointer to the first character.  Also, the `char*`
/// will end up pointing to characters owned by the `ImageSpec`; the
/// caller does not need to ever free the memory that contains the
/// characters.
///
/// This was added in version 2.1.
_Bool  OIIO_ImageSpec_getattribute(const OIIO_ImageSpec* self, const char* name, OIIO_TypeDesc type, void* value, _Bool casesensitive);

/// Copy from `other` the image dimensions (x, y, z, width, height,
/// depth, full*, nchannels, format) and data types. It does *not* copy
/// arbitrary named metadata or channel names (thus, for an `ImageSpec`
/// with lots of metadata, it is much less expensive than copying the
/// whole thing with `operator=()`).
void  OIIO_ImageSpec_copy_dimensions(OIIO_ImageSpec* self, const OIIO_ImageSpec* other);

/// Return the number of bytes for just the subset of channels in each
/// pixel described by [chbegin,chend). If native is false (default),
/// assume all channels are in this->format, but if native is true,
/// compute the size of a pixel in the "native" data format of the file
/// (these may differ in the case of per-channel formats).
unsigned long  OIIO_ImageSpec_pixel_bytes_for(const OIIO_ImageSpec* self, int chbegin, int chend, _Bool native);

/// Search for the named attribute and return the pointer to its
/// `ParamValue` record, or NULL if not found.  This variety of
/// `find_attribute(}` can retrieve items such as "width", which are
/// data members of the `ImageSpec`, but not in `extra_attribs`. The
/// `tmpparam` is a storage area owned by the caller, which is used as
/// temporary buffer in cases where the information does not correspond
/// to an actual `extra_attribs` (in this case, the return value will be
/// `&tmpparam`). The extra names it understands are:
///
/// - `"x"` `"y"` `"z"` `"width"` `"height"` `"depth"`
///   `"full_x"` `"full_y"` `"full_z"` `"full_width"` `"full_height"` `"full_depth"`
///
///   Returns the `ImageSpec` fields of those names (despite the
///   fact that they are technically not arbitrary named attributes
///   in `extra_attribs`). All are of type `int`.
///
/// - `"datawindow"`
///
///   Without a type, or if requested explicitly as an `int[4]`,
///   returns the OpenEXR-like pixel data min and max coordinates,
///   as a 4-element integer array: `{ x, y, x+width-1, y+height-1
///   }`. If instead you specifically request as an `int[6]`, it
///   will return the volumetric data window, `{ x, y, z, x+width-1,
///   y+height-1, z+depth-1 }`.
///
/// - `"displaywindow"`
///
///   Without a type, or if requested explicitly as an `int[4]`,
///   returns the OpenEXR-like pixel display min and max
///   coordinates, as a 4-element integer array: `{ full_x, full_y,
///   full_x+full_width-1, full_y+full_height-1 }`. If instead you
///   specifically request as an `int[6]`, it will return the
///   volumetric display window, `{ full_x, full_y, full_z,
///   full_x+full_width-1, full_y+full_height-1, full_z+full_depth-1 }`.
///
/// EXAMPLES
///
///     ImageSpec spec;           // has the info
///     Imath::Box2i dw;          // we want the displaywindow here
///     ParamValue tmp;           // so we can retrieve pseudo-values
///     TypeDesc int4("int[4]");  // Equivalent: TypeDesc int4(TypeDesc::INT,4);
///     const ParamValue* p = spec.find_attribute ("displaywindow", int4);
///     if (p)
///         dw = Imath::Box2i(p->get<int>(0), p->get<int>(1),
///                           p->get<int>(2), p->get<int>(3));
///
///     p = spec.find_attribute("temperature", TypeFloat);
///     if (p)
///         float temperature = p->get<float>();
///
const OIIO_ParamValue*  OIIO_ImageSpec_find_attribute_or(const OIIO_ImageSpec* self, const char* name, OIIO_ParamValue* tmpparam, OIIO_TypeDesc searchtype, _Bool casesensitive);

/// If the named attribute can be found in the `ImageSpec`, return its
/// data type. If no such attribute exists, return `TypeUnknown`.
///
/// This was added in version 2.1.
OIIO_TypeDesc  OIIO_ImageSpec_getattributetype(const OIIO_ImageSpec* self, const char* name, _Bool casesensitive);

/// For a given parameter `p`, format the value nicely as a string.  If
/// `human` is true, use especially human-readable explanations (units,
/// or decoding of values) for certain known metadata.
char*  OIIO_ImageSpec_metadata_val(const OIIO_ParamValue* p, _Bool human);

/// Populates the fields of the `ImageSpec` based on the XML passed in.
void  OIIO_ImageSpec_from_xml(OIIO_ImageSpec* self, const char* xml);

/// Set pixel data window parameters (x, y, z, width, height, depth)
/// for this ImageSpec from an ROI.
/// Does NOT change the channels of the spec, regardless of r.
void  OIIO_ImageSpec_set_roi(OIIO_ImageSpec* self, const OIIO_ROI* r);

/// Converts the contents of the `ImageSpec` as an XML string.
char*  OIIO_ImageSpec_to_xml(const OIIO_ImageSpec* self);

/// Return the channelformat of the given channel. This is safe even
/// if channelformats is not filled out.
OIIO_TypeDesc  OIIO_ImageSpec_channelformat(const OIIO_ImageSpec* self, int chan);

/// Return the channel name of the given channel. This is safe even if
/// channelnames is not filled out.
const char*  OIIO_ImageSpec_channel_name(const OIIO_ImageSpec* self, int chan);

/// Fill in an array of channel formats describing all channels in
/// the image.  (Note that this differs slightly from the member
/// data channelformats, which is empty if there are not separate
/// per-channel formats.)
void  OIIO_ImageSpec_get_channelformats(const OIIO_ImageSpec* self, std_vector* formats);

/// Return the index of the channel with the given name, or -1 if no
/// such channel is present in `channelnames`.
int  OIIO_ImageSpec_channelindex(const OIIO_ImageSpec* self, const char* name);

/// Return the number of bytes needed for the single specified
/// channel.  If native is false (default), compute the size of one
/// channel of `this->format`, but if native is true, compute the size
/// of the channel in terms of the "native" data format of that
/// channel as stored in the file.
unsigned long  OIIO_ImageSpec_channel_bytes_for(const OIIO_ImageSpec* self, int chan, _Bool native);

/// Set full/display window parameters (full_x, full_y, full_z,
/// full_width, full_height, full_depth) for this ImageSpec from an ROI.
/// Does NOT change the channels of the spec, regardless of r.
void  OIIO_ImageSpec_set_roi_full(OIIO_ImageSpec* self, const OIIO_ROI* r);

/// Return full/display window for this ImageSpec expressed as a ROI.
OIIO_ROI  OIIO_ImageSpec_roi_full(const OIIO_ImageSpec* self);

/// Return pixel data window for this ImageSpec expressed as a ROI.
OIIO_ROI  OIIO_ImageSpec_roi(const OIIO_ImageSpec* self);

/// Returns `true` for a newly initialized (undefined) `ImageSpec`.
/// (Designated by no channels and undefined data type -- true of the
/// uninitialized state of an ImageSpec, and presumably not for any
/// ImageSpec that is useful or purposefully made.)
_Bool  OIIO_ImageSpec_undefined(const OIIO_ImageSpec* self);


typedef struct OIIO_ImageInput OIIO_ImageInput;

void  OIIO_ImageInput_copy(OIIO_ImageInput* self, const OIIO_ImageInput* );


OIIO_ImageInput*  OIIO_ImageInput_assign(OIIO_ImageInput* self, const OIIO_ImageInput* );

/// Try to lock the internal mutex, returning true if successful, or
/// false if the lock could not be immediately acquired.
_Bool  OIIO_ImageInput_try_lock(OIIO_ImageInput* self);

/// Retrieve the current thread-spawning policy.
/// @see  `threads(int)`
int  OIIO_ImageInput_threads(const OIIO_ImageInput* self);

/// Read into `deepdata` the block of native deep data tiles that
/// include all pixels and channels specified by pixel range.
///
/// @param  subimage    The subimage to read from (starting with 0).
/// @param  miplevel    The MIP level to read (0 is the highest
///                     resolution level).
/// @param  xbegin/xend The x range of the pixels covered by the group
///                     of tiles being read.
/// @param  ybegin/yend The y range of the pixels covered by the tiles.
/// @param  zbegin/zend The z range of the pixels covered by the tiles
///                     (for a 2D image, zbegin=0 and zend=1).
/// @param  chbegin/chend
///                     The channel range to read.
/// @param  deepdata    A `DeepData` object into which the data for
///                     these tiles will be placed.
/// @returns            `true` upon success, or `false` upon failure.
///
/// @note The call will fail if the image is not tiled, or if the pixel
/// ranges do not fall along tile (or image) boundaries, or if it is not
/// a valid tile range.
_Bool  OIIO_ImageInput_read_native_deep_tiles(OIIO_ImageInput* self, int subimage, int miplevel, int xbegin, int xend, int ybegin, int yend, int zbegin, int zend, int chbegin, int chend, OIIO_DeepData* deepdata);

/// Read deep scanlines containing pixels (*,y,z), for all y in the
/// range [ybegin,yend) into `deepdata`. This will fail if it is not a
/// deep file.
///
/// @param  subimage    The subimage to read from (starting with 0).
/// @param  miplevel    The MIP level to read (0 is the highest
///                     resolution level).
/// @param  chbegin/chend
///                     The channel range to read.
/// @param  ybegin/yend The y range of the scanlines being passed.
/// @param  z           The z coordinate of the scanline.
/// @param  deepdata    A `DeepData` object into which the data for
///                     these scanlines will be placed.
/// @returns            `true` upon success, or `false` upon failure.
_Bool  OIIO_ImageInput_read_native_deep_scanlines(OIIO_ImageInput* self, int subimage, int miplevel, int ybegin, int yend, int z, int chbegin, int chend, OIIO_DeepData* deepdata);

/// Set the threading policy for this ImageInput, controlling the
/// maximum amount of parallelizing thread "fan-out" that might occur
/// during large read operations. The default of 0 means that the global
/// `attribute("threads")` value should be used (which itself defaults
/// to using as many threads as cores; see Section `Global Attributes`_).
///
/// The main reason to change this value is to set it to 1 to indicate
/// that the calling thread should do all the work rather than spawning
/// new threads. That is probably the desired behavior in situations
/// where the calling application has already spawned multiple worker
/// threads.
void  OIIO_ImageInput_set_threads(OIIO_ImageInput* self, int n);

/// Return a reference to the image specification of the current
/// subimage/MIPlevel.  Note that the contents of the spec are invalid
/// before `open()` or after `close()`, and may change with a call to
/// `seek_subimage()`. It is thus not thread-safe, since the spec may
/// change if another thread calls `seek_subimage`, or any of the
/// `read_*()` functions that take explicit subimage/miplevel.
const OIIO_ImageSpec*  OIIO_ImageInput_spec(const OIIO_ImageInput* self);

/// Return the name of the format implemented by this class.
const char*  OIIO_ImageInput_format_name(const OIIO_ImageInput* self);

/// Seek to the given subimage and MIP-map level within the open image
/// file.  The first subimage of the file has index 0, the highest-
/// resolution MIP level has index 0.  The new subimage's vital
/// statistics=may be retrieved by `this->spec()`.  The reader is
/// expected to give the appearance of random access to subimages and
/// MIP levels -- in other words, if it can't randomly seek to the given
/// subimage/level, it should transparently close, reopen, and
/// sequentially read through prior subimages and levels.
///
/// @returns
///         `true` upon success, or `false` upon failure. A failure may
///         indicate that no such subimage or MIP level exists in the
///         file.
_Bool  OIIO_ImageInput_seek_subimage(OIIO_ImageInput* self, int subimage, int miplevel);

/// Ulock the internal mutex.
void  OIIO_ImageInput_unlock(OIIO_ImageInput* self);

/// Given the name of a "feature", return whether this ImageInput
/// supports output of images with the given properties. Most queries
/// will simply return 0 for "doesn't support" and 1 for "supports it,"
/// but it is acceptable to have queries return other nonzero integers
/// to indicate varying degrees of support or limits (but should be
/// clearly documented as such).
///
/// Feature names that ImageInput implementations are expected to
/// recognize include:
///
/// - `"arbitrary_metadata"` : Does this format allow metadata with
///       arbitrary names and types?
///
/// - `"exif"` :
///       Can this format store Exif camera data?
///
/// - `"iptc"` :
///       Can this format store IPTC data?
///
/// - `"procedural"` :
///       Can this format create images without reading from a disk
///       file?
///
/// - `"ioproxy"` :
///       Does this format reader support reading from an `IOProxy`?
///
/// This list of queries may be extended in future releases. Since this
/// can be done simply by recognizing new query strings, and does not
/// require any new API entry points, addition of support for new
/// queries does not break ``link compatibility'' with
/// previously-compiled plugins.
int  OIIO_ImageInput_supports(const OIIO_ImageInput* self, const char* feature);

/// Set an IOProxy for this reader. This must be called prior to
/// `open()`, and only for readers that support them
/// (`supports("ioproxy")`). The caller retains ownership of the proxy.
///
/// @returns `true` for success, `false` for failure.
_Bool  OIIO_ImageInput_set_ioproxy(OIIO_ImageInput* self, OIIO_Filesystem_IOProxy* ioproxy);

/// Create an ImageInput subclass instance that is able to read the
/// given file and open it, returning a `unique_ptr` to the ImageInput
/// if successful.  The `unique_ptr` is set up with an appropriate
/// deleter so the ImageInput will be properly closed and deleted when
/// the `unique_ptr` goes out of scope or is reset. If the open fails,
/// return an empty `unique_ptr` and set an error that can be retrieved
/// by `OIIO::geterror()`.
///
/// The `config`, if not nullptr, points to an ImageSpec giving hints,
/// requests, or special instructions.  ImageInput implementations are
/// free to not respond to any such requests, so the default
/// implementation is just to ignore `config`.
///
/// `open()` will first try to make an ImageInput corresponding to
/// the format implied by the file extension (for example, `"foo.tif"`
/// will try the TIFF plugin), but if one is not found or if the
/// inferred one does not open the file, every known ImageInput type
/// will be tried until one is found that will open the file.
///
/// @param filename
///         The name of the file to open.
///
/// @param config
///         Optional pointer to an ImageSpec whose metadata contains
///         "configuration hints."
///
/// @param ioproxy
///         Optional pointer to an IOProxy to use (not supported by all
///         formats, see `supports("ioproxy")`). The caller retains
///         ownership of the proxy.
///
/// @returns
///         A `unique_ptr` that will close and free the ImageInput when
///         it exits scope or is reset. The pointer will be empty if the
///         required writer was not able to be created.
OIIO_ImageInput*  OIIO_ImageInput_open(const char* filename, const OIIO_ImageSpec* config, OIIO_Filesystem_IOProxy* ioproxy);

/// Create and return an ImageInput implementation that is able to read
/// the given file or format.  If `do_open` is true (and the `filename`
/// is the name of a file, not just a format), fully open it if possible
/// (using the optional `config` configuration spec, if supplied),
/// otherwise just create the ImageInput but don't open it. The
/// plugin_searchpath parameter is an override of the searchpath.
/// colon-separated list of directories to search for ImageIO plugin
/// DSO/DLL's (not a searchpath for the image itself!).
///
/// If the `filename` parameter is the name of a file format (such as
/// "openexr"), it will create an ImageInput that reads that particular
/// format. If the name is a file extension (such as "exr" or ".exr"),
/// it will guess the file format from the extension and return that
/// type of ImageInput.
///
/// If `filename` is a full file name (such as "hawaii.exr"), it will
/// create an ImageInput that reads the format implied by the file
/// extension (".tif") and try to open the file with that reader. If the
/// file can be opened and appears to be of the correct type, then that
/// ImageInput (after being closed) will be returned to the caller. But
/// if it fails (say, because the file type does not match the
/// extension), then every known kind of image reader will be tried in
/// turn, until one can be found that succeeds in opening that file. The
/// `create()` file will fail entirely only if no known image reader
/// type succeeds.
///
/// If the caller intends to immediately open the file, then it is often
/// simpler to call static `ImageInput::open()`.
///
/// @param filename
///         The name of an image file, or a file extension, or the name
///         of a file format.
///
/// @param do_open
///         If `true`, not only create but also open the file.
///
/// @param config
///         Optional pointer to an ImageSpec whose metadata contains
///         "configuration hints" for the ImageInput implementation.
///
/// @param ioproxy
///         Optional pointer to an IOProxy to use (not supported by all
///         formats, see `supports("ioproxy")`). The caller retains
///         ownership of the proxy. If this is not supplied, it is still
///         possible to set the proxy with a call to `set_proxy()` prior
///         to `open()`.
///
/// @param plugin_searchpath
///         An optional colon-separated list of directories to search
///         for OpenImageIO plugin DSO/DLL's.
///
/// @returns
///         A `unique_ptr` that will close and free the ImageInput when
///         it exits scope or is reset. The pointer will be empty if the
///         required writer was not able to be created.
OIIO_ImageInput*  OIIO_ImageInput_create(const char* filename, _Bool do_open, const OIIO_ImageSpec* config, OIIO_Filesystem_IOProxy* ioproxy, const char* plugin_searchpath);

/// Return a full copy of the ImageSpec of the designated subimage and
/// MIPlevel. This method is thread-safe, but it is potentially
/// expensive, due to the work that needs to be done to fully copy an
/// ImageSpec if there is lots of named metadata to allocate and copy.
/// See also the less expensive `spec_dimensions()`. Errors (such as
/// having requested a nonexistent subimage) are indicated by returning
/// an ImageSpec with `format==TypeUnknown`.
OIIO_ImageSpec  OIIO_ImageInput_spec_copy(OIIO_ImageInput* self, int subimage, int miplevel);

/// Return a copy of the ImageSpec of the designated subimage and
/// miplevel, but only the dimension and type fields. Just as with a
/// call to `ImageSpec::copy_dimensions()`, neither the channel names
/// nor any of the arbitrary named metadata will be copied, thus this is
/// a relatively inexpensive operation if you don't need that
/// information. It is guaranteed to be thread-safe. Errors (such as
/// having requested a nonexistent subimage) are indicated by returning
/// an ImageSpec with `format==TypeUnknown`.
OIIO_ImageSpec  OIIO_ImageInput_spec_dimensions(OIIO_ImageInput* self, int subimage, int miplevel);

/// Close an open ImageInput. The call to close() is not strictly
/// necessary if the ImageInput is destroyed immediately afterwards,
/// since it is required for the destructor to close if the file is
/// still open.
///
/// @returns
///         `true` upon success, or `false` upon failure.
_Bool  OIIO_ImageInput_close(OIIO_ImageInput* self);

/// Lock the internal mutex, block until the lock is acquired.
void  OIIO_ImageInput_lock(OIIO_ImageInput* self);

/// Read the entire image of `spec.width x spec.height x spec.depth`
/// pixels into a buffer with the given strides and in the desired
/// data format.
///
/// Depending on the spec, this will read either all tiles or all
/// scanlines. Assume that data points to a layout in row-major order.
///
/// This version of read_image, because it passes explicit subimage and
/// miplevel, does not require a separate call to seek_subimage, and is
/// guaranteed to be thread-safe against other concurrent calls to any
/// of the read_* methods that take an explicit subimage/miplevel (but
/// not against any other ImageInput methods).
///
/// Because this may be an expensive operation, a progress callback
/// may be passed.  Periodically, it will be called as follows:
///
///     progress_callback (progress_callback_data, float done);
///
/// where `done` gives the portion of the image (between 0.0 and 1.0)
/// that has been written thus far.
///
/// @param  subimage    The subimage to read from (starting with 0).
/// @param  miplevel    The MIP level to read (0 is the highest
///                     resolution level).
/// @param  chbegin/chend
///                     The channel range to read.
/// @param  format      A TypeDesc describing the type of `data`.
/// @param  data        Pointer to the pixel data.
/// @param  xstride/ystride/zstride
///                     The distance in bytes between successive pixels,
///                     scanlines, and image planes (or `AutoStride`).
/// @param  progress_callback/progress_callback_data
///                     Optional progress callback.
/// @returns            `true` upon success, or `false` upon failure.
_Bool  OIIO_ImageInput_read_image(OIIO_ImageInput* self, int subimage, int miplevel, int chbegin, int chend, OIIO_TypeDesc format, void* data, long xstride, long ystride, long zstride, * progress_callback, void* progress_callback_data);

/// Returns the index of the subimage that is currently being read.
/// The first subimage (or the only subimage, if there is just one)
/// is number 0.
int  OIIO_ImageInput_current_subimage(const OIIO_ImageInput* self);

/// Read multiple scanlines that include pixels (*,y,z) for all ybegin
/// <= y < yend in the specified subimage and mip level, into `data`,
/// using the strides given and converting to the requested data
/// `format` (TypeUnknown indicates no conversion, just copy native data
/// types). Only channels [chbegin,chend) will be read/copied
/// (chbegin=0, chend=spec.nchannels reads all channels, yielding
/// equivalent behavior to the simpler variant of `read_scanlines`).
///
/// This version of read_scanlines, because it passes explicit
/// subimage/miplevel, does not require a separate call to
/// seek_subimage, and is guaranteed to be thread-safe against other
/// concurrent calls to any of the read_* methods that take an explicit
/// subimage/miplevel (but not against any other ImageInput methods).
///
/// @param  subimage    The subimage to read from (starting with 0).
/// @param  miplevel    The MIP level to read (0 is the highest
///                     resolution level).
/// @param  ybegin/yend The y range of the scanlines being passed.
/// @param  z           The z coordinate of the scanline.
/// @param  chbegin/chend
///                     The channel range to read.
/// @param  format      A TypeDesc describing the type of `data`.
/// @param  data        Pointer to the pixel data.
/// @param  xstride/ystride
///                     The distance in bytes between successive pixels
///                     and scanlines (or `AutoStride`).
/// @returns            `true` upon success, or `false` upon failure.
///
/// @note This call was changed for OpenImageIO 2.0 to include the
///     explicit subimage and miplevel parameters. The previous
///     versions, which lacked subimage and miplevel parameters (thus
///     were dependent on a prior call to `seek_subimage`) are
///     considered deprecated.
_Bool  OIIO_ImageInput_read_scanlines(OIIO_ImageInput* self, int subimage, int miplevel, int ybegin, int yend, int z, int chbegin, int chend, OIIO_TypeDesc format, void* data, long xstride, long ystride);

/// Returns the index of the MIPmap image that is currently being read.
/// The highest-res MIP level (or the only level, if there is just
/// one) is number 0.
int  OIIO_ImageInput_current_miplevel(const OIIO_ImageInput* self);

/// Read the entire deep data image of spec.width x spec.height x
/// spec.depth pixels, all channels, into `deepdata`.
///
/// @param  subimage    The subimage to read from (starting with 0).
/// @param  miplevel    The MIP level to read (0 is the highest
///                     resolution level).
/// @param  deepdata    A `DeepData` object into which the data for
///                     the image will be placed.
/// @returns            `true` upon success, or `false` upon failure.
_Bool  OIIO_ImageInput_read_native_deep_image(OIIO_ImageInput* self, int subimage, int miplevel, OIIO_DeepData* deepdata);

/// Read the scanline that includes pixels (*,y,z) from the "current"
/// subimage and MIP level.  The `xstride` value gives the distance
/// between successive pixels (in bytes).  Strides set to `AutoStride`
/// imply "contiguous" data.
///
/// @note This variety of `read_scanline` is not re-entrant nor
/// thread-safe. If you require concurrent reads to the same open
/// ImageInput, you should use `read_scanlines` that has the `subimage`
/// and `miplevel` passed explicitly.
///
/// @param  y/z         The y & z coordinates of the scanline. For 2D
///                     images, z should be 0.
/// @param  format      A TypeDesc describing the type of `data`.
/// @param  data        Pointer to the pixel data buffer.
/// @param  xstride     The distance in bytes between successive
///                     pixels in `data` (or `AutoStride`).
/// @returns            `true` upon success, or `false` upon failure.
_Bool  OIIO_ImageInput_read_scanline(OIIO_ImageInput* self, int y, int z, OIIO_TypeDesc format, void* data, long xstride);

/// Return true if the `filename` names a file of the type for this
/// ImageInput.  The implementation will try to determine this as
/// efficiently as possible, in most cases much less expensively than
/// doing a full `open()`.  Note that there can be false positives: a
/// file can appear to be of the right type (i.e., `valid_file()`
/// returning `true`) but still fail a subsequent call to `open()`, such
/// as if the contents of the file are truncated, nonsensical, or
/// otherwise corrupted.
///
/// @returns
///         `true` upon success, or `false` upon failure.
_Bool  OIIO_ImageInput_valid_file(const OIIO_ImageInput* self, const char* filename);

/// Read the tile whose upper-left origin is (x,y,z) into `data[]`,
/// converting if necessary from the native data format of the file into
/// the `format` specified. The stride values give the data spacing of
/// adjacent pixels, scanlines, and volumetric slices (measured in
/// bytes). Strides set to AutoStride imply 'contiguous' data in the
/// shape of a full tile, i.e.,
///
///     xstride = format.size() * spec.nchannels
///     ystride = xstride * spec.tile_width
///     zstride = ystride * spec.tile_height
///
/// @note This variety of `read_tile` is not re-entrant nor thread-safe.
/// If you require concurrent reads to the same open ImageInput, you
/// should use `read_tiles()` that has the `subimage` and `miplevel`
/// passed explicitly.
///
/// @param  x/y/z       The upper left coordinate of the tile being passed.
/// @param  format      A TypeDesc describing the type of `data`.
/// @param  data        Pointer to the pixel data.
/// @param  xstride/ystride/zstride
///                     The distance in bytes between successive pixels,
///                     scanlines, and image planes (or `AutoStride` to
///                     indicate a "contiguous" single tile).
/// @returns            `true` upon success, or `false` upon failure.
///
/// @note This call will fail if the image is not tiled, or if (x,y,z)
/// is not the upper left corner coordinates of a tile.
_Bool  OIIO_ImageInput_read_tile(OIIO_ImageInput* self, int x, int y, int z, OIIO_TypeDesc format, void* data, long xstride, long ystride, long zstride);

/// Read the block of multiple tiles that include all pixels in
///
///     [xbegin,xend) X [ybegin,yend) X [zbegin,zend)
///
/// This is analogous to calling `read_tile(x,y,z,...)` for each tile
/// in turn (but for some file formats, reading multiple tiles may allow
/// it to read more efficiently or in parallel).
///
/// The begin/end pairs must correctly delineate tile boundaries, with
/// the exception that it may also be the end of the image data if the
/// image resolution is not a whole multiple of the tile size. The
/// stride values give the data spacing of adjacent pixels, scanlines,
/// and volumetric slices (measured in bytes). Strides set to AutoStride
/// imply contiguous data in the shape of the [begin,end) region, i.e.,
///
///     xstride = format.size() * spec.nchannels
///     ystride = xstride * (xend-xbegin)
///     zstride = ystride * (yend-ybegin)
///
/// This version of read_tiles, because it passes explicit subimage and
/// miplevel, does not require a separate call to seek_subimage, and is
/// guaranteed to be thread-safe against other concurrent calls to any
/// of the read_* methods that take an explicit subimage/miplevel (but
/// not against any other ImageInput methods).
///
/// @param  subimage    The subimage to read from (starting with 0).
/// @param  miplevel    The MIP level to read (0 is the highest
///                     resolution level).
/// @param  xbegin/xend The x range of the pixels covered by the group
///                     of tiles being read.
/// @param  ybegin/yend The y range of the pixels covered by the tiles.
/// @param  zbegin/zend The z range of the pixels covered by the tiles
///                     (for a 2D image, zbegin=0 and zend=1).
/// @param  chbegin/chend
///                     The channel range to read.
/// @param  format      A TypeDesc describing the type of `data`.
/// @param  data        Pointer to the pixel data.
/// @param  xstride/ystride/zstride
///                     The distance in bytes between successive pixels,
///                     scanlines, and image planes (or `AutoStride`).
/// @returns            `true` upon success, or `false` upon failure.
///
/// @note The call will fail if the image is not tiled, or if the pixel
/// ranges do not fall along tile (or image) boundaries, or if it is not
/// a valid tile range.
_Bool  OIIO_ImageInput_read_tiles(OIIO_ImageInput* self, int subimage, int miplevel, int xbegin, int xend, int ybegin, int yend, int zbegin, int zend, int chbegin, int chend, OIIO_TypeDesc format, void* data, long xstride, long ystride, long zstride);


#ifdef __cplusplus
}
#endif
    