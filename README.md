
# CPPMM
C-plus-plus-minus-minus

## Current status

- [x] AST generation
- [ ] C library output
- [ ] Rust-sys output
- [x] Binding file generation

## Introduction

`cppmm` is a binding generator for creating C and Rust interfaces to C++ libraries. It is targeting a very small subset of libraries--just those in consideration by the `vfx-rs` project--and is not expected to work for anything else and will have assumptions about the C++ it will accept based on the types and idioms found in those libraries baked into it.

## Documentation

There is a series of tutorials introducing the concepts of writing binding files and using the tools here (Note: work in progress): https://github.com/vfx-rs/cppmm/wiki

## Supported C++ features

| Feature | Status |
| ------- | ------ |
| Builtins | -[x] |


## Why not bindgen/cxx/autocxx?

Several reasons:
1. While excellent, all these libraries have limitations in the C++ they can bind that make them unsuitable for our target libraries.
2. We want to be able to control the output to generate good C and Rust APIs: to choose which template instantiations and which overloads we want to bind, and what to name them.
3. The target libraries tend to move very quickly with a lot of API churn. It would be nice if our binding tool could help us keep up to date by tracking changes in the target libraries.

We are specifically *not* trying to create a completely automatic binding mechanism from C++ to C and Rust. Trying to specify all the necessary information in your `build.rs` is unwieldy. 

Moreover, we need to support many different versions of the C++ API concurrently, and the binding description should be a separate build artefact maintained (and version-controlled) independently of the Rust project. 

Although we are specifically targeting Rust here, it is our goal that the generated C API should be pleasant enough to use from pure C, and of course it is suitable for binding to other languages using their own FFI mechanisms.

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

and then another generator can create a rust-sys wrapper that would look something like:
```Rust
pub struct Imath_2_5_V3f {
    pub x: f32,
    pub y: f32,
    pub z: f32,
}

extern "C" {
    fn Imath_2_5_V3f_ctor(this_: *mut Imath_2_5_V3f);
    fn Imath_2_5_V3f_copy(this_: *mut Imath_2_5_V3f, param1: *const Imath_2_5_V3f);
    fn Imath_2_5_V3f_length(this_: *const Imath_2_5_V3f) -> f32;
}
```


## Quick start
You must have LLVM and clang installed. I've tested it with llvm 10.0.1 and 11.0.0. To run the tests you'll need USD 20.05, OIIO 2.2.8 and OpenEXR 2.5.5 installed. Other versions may work but the tests will fail as they rely on diffing the output, which will have the version numbers baked into the namespaces.

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
Some basic integration tests are in place using CTest. To run them you'll need to set the environment variables `OIIO_ROOT`, `OPENEXR_ROOT` and `USD_ROOT` to point to the relevant installations. Since the tests diff the output against reference you'll need the same versions (at least to minor versions) in order to not get spurious errors. Those versions are:
```
OpenImageIO: 2.2.8
OpenEXR: 2.5.5
USD: 20.05
```

Then just run `make test` from the build directory.

