
# CPPMM
C-plus-plus-minus-minus

`cppmm` is a binding generator for creating C and Rust interfaces to C++ libraries. Its purpose is to semi-automatically take any* C++ and turn it into a C API and a matching Rust FFI crate (what is commonly known as a `-sys` crate). It takes a binding file as input which describes what classes and functions of the target library are to be bound, instantiates and names templates, names overloads and much more.

[* ] Our priority is targeting a small set of libraries--just those in consideration by the `vfx-rs` project. It should work for other libraries but will have assumptions baked into it about the C++ it will accept based on the types and idioms found in our target libraries. Failure to bind libraries outside of that scope will be considered a low-priority bug.


## Current status

### Components
- [x] AST generation
- [x] C library output
- [x] Rust-sys output
- [x] Binding file generation

### Libraries bound

| Feature | Status |
| ------- | ------ |
| Imath | <ul><li> - [ ] Still under discussion whether this will be a binding, a reimplementation, or just using mint or something like it. </ul></li> |
| OpenEXR | <ul><li> ✔️ Complete. Not fully tested </ul></li> |
| OpenImageIO | <ul><li> ⚙️ Partially complete </ul></li> |
| OpenColorIO | <ul><li> ⚙️ In progress </ul></li> |
| Ptex | <ul><li> ⚙️ In progress </ul></li> |
| OpenShadingLanguage | <ul><li> :x: Planned </ul></li> |
| Slang | <ul><li> :x: Planned </ul></li> |
| MaterialX | <ul><li> :x: Planned </ul></li> |
| Alembic | <ul><li> :x: Planned </ul></li> |
| OpenVDB | <ul><li> :x: Planned </ul></li> |
| USD | <ul><li> :x:  Planned </ul></li> |

## Documentation

There is a series of tutorials introducing the concepts of writing binding files and using the tools here (Note: work in progress): https://github.com/vfx-rs/cppmm/wiki


## Why not bindgen/cxx/autocxx?

1. While excellent, all these libraries have limitations in the C++ they can bind that make them unsuitable for our target libraries.
2. We want to be able to control the output to generate good C and Rust APIs: to choose which template instantiations and which overloads we want to bind, and what to name them.
3. The target libraries tend to move very quickly with a lot of API churn. It would be nice if our binding tool could help us keep up to date by tracking changes in the target libraries.

We are specifically *not* trying to create a completely automatic binding mechanism from C++ to C and Rust. Trying to specify all the necessary information in your `build.rs` is unwieldy. 

Moreover, we need to support many different versions of the C++ API concurrently, and the binding description should be a separate build artefact maintained (and version-controlled) independently of the Rust project. 

Although we are specifically targeting Rust here, it is our goal that the generated C API should be pleasant enough to use from pure C, and of course it is suitable for binding to other languages using their own FFI mechanisms.

## Supported C++ features

| Feature | Status |
| ------- | ------ |
| Builtins | <ul><li> - [x] Works </ul></li> |
| POD structs | <ul><li> - [x] Works </ul></li> |
| Opaque structs | <ul><li> - [x] Works </ul></li> |
| Opaque pointers | <ul><li> - [x] Works </ul></li> |
| Templated structs | <ul><li> - [x] Works </ul></li> |
| Templated functions/methods | <ul><li> - [x] Works </ul></li> |
| Polymorphic functions/methods | <ul><li> - [x] Works </ul></li> |
| STL containers | <ul><li> - [x] Works </ul></li> |
| "Subclassing" C++ types in Rust | <ul><li> - [ ] Planned </ul></li> |
| Variadiac templates | <ul><li> - [ ] Unsupported </ul></li> |

## How does it work?

cppmm introduces the concept of a *binding description file* that declares which classes and methods should be bound and which should be ignored, what representation we should use for them, and how they should be renamed if necessary or desired.

The binding file is regular C++ so that we don't have to deal with the nightmare that is parsing C++ declarations and can get Clang to do it for us:

```c++
#include <OpenEXR/ImathVec.h>

// CPPMM_ macro definitions etc automatically inserted in this virtual header
#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace Imath = ::IMATH_INTERNAL_NAMESPACE; //< This expands to e.g. Imath_2_5

// We match the target library's namespace hierarchy so we can find the 
// matching declarations
namespace IMATH_INTERNAL_NAMESPACE {

template <class T> class Vec3 {
public:
    // This alias tells cppmm which type our binding class represents
    using BoundType = Imath::Vec3<T>;

    // We just list the declarations for all methods we want to bind
    Vec3();
    Vec3(const Imath::Vec3<T>& v) CPPMM_RENAME(copy); //< Rename this method
    T length();

    // We can also state explicitly any methods we want to ignore.
    // Any methods we don't declare or ignore generate a warning to help track
    // API changes
    T length2() CPPMM_IGNORE;

} CPPMM_VALUETYPE; // Expose the fields of this class to C and Rust. Other
                   // possibilities are OPAQUEBYTES and OPAQUEPTR

// explicitly instantiate the template so Clang generates the AST
template class Vec3<float>;

// We use aliases to give template instantiations an explicit name
using V3f = Imath::Vec3<float>;

}
}
```

The `astgen` binary reads this binding file and creates a JSON file containing
a representation of the AST of the target API. Then `asttoc` reads this JSON, transforms the AST into a C representation, and spits out a C wrapper that calls the underlying C++ API. For the binding file above, that C wrapper looks something like:

```c++
typedef struct {
    float x;
    float y;
    float z;
} Imath_2_5_V3f;

void Imath_2_5_V3f_ctor(Imath_2_5_V3f* this_);
void Imath_2_5_V3f_copy(Imath_2_5_V3f* this_, const Imath_2_5_V3f* param1);
float Imath_2_5_V3f_length(const Imath_2_5_V3f* this_);
```

`asttoc` also creates a rust-sys wrapper that looks something like:
```Rust
#[repr(C)]
#[derive(Debug, Clone)]
pub struct Imath_2_5_V3f {
    pub x: c_float,
    pub y: c_float,
    pub z: c_float,
}

extern "C" {
    fn Imath_2_5_V3f_ctor(this_: *mut Imath_2_5_V3f);
    fn Imath_2_5_V3f_copy(this_: *mut Imath_2_5_V3f, param1: *const Imath_2_5_V3f);
    fn Imath_2_5_V3f_length(this_: *const Imath_2_5_V3f) -> f32;
}
```


## Quick start
You must have LLVM and clang 14.0.0 installed. To run the tests you'll need OpenEXR 2.5.5 installed. Other versions may work but the tests will fail as they rely on diffing the output, which will have the version numbers baked into the type names.

### Checkout
The repository includes spdlog and nlohmann::json as submodules, so clone with `--recursive`:
```bash
git clone --recursive git@github.com:vfx-rs/cppmm.git
```
Or if you already have it cloned:
```bash
git submodule update --init
```

### Build
To build:
```
mkdir build && cd build
env LLVM_ROOT=</path/to/llvm/installation> cmake ..
make
```

### Build a debug build
To build:
```
mkdir build && cd build
env LLVM_ROOT=</path/to/llvm/installation> cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Test
Some basic integration tests are in place using CTest. To run them you'll need to set the environment variables `OPENEXR_ROOT` to point to the relevant installations. Since the tests diff the output against reference you'll need the same versions (at least to minor versions) in order to not get spurious errors. Those versions are:
```
OpenEXR: 2.5.5
```

Then just run `make test` from the build directory.

