# CPPMM
C-plus-plus-minus-minus

## Introduction

`cppmm` is a binding generator for creating C and Rust interfaces to C++ libraries. It is targeting a very small subset of libraries--just those in consideration by the `vfx-rs` project--and is not expected to work for anything else and will have assumptions about the C++ it will accept based on the types and idioms found in those libraries baked into it.

## Quick start
You must have LLVM and clang installed. I've tested it with llvm 10.0.1 only. To run the test you'll need OIIO 2.2.8 and openexr 2.4.0 (other versions may work but are untested)

### Checkout
The repository includes fmtlib 4.1.0 and nlohmann::json as submodules, so clone with `--recursive`:
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

### Test
Some basic integration tests are in place using CTest. To run them you'll need to set the environment variables `OIIO_ROOT` and `OPENEXR_ROOT` to point to the relevant installations. Since the tests diff the output against reference you'll probably need the same versions (at least to minor versions) in order to not get spurious errors. Those versions are:
```
OpenImageIO: 2.2.8
OpenEXR: 2.4.0
```

Then just run `make test` from the build directory.

### Run

From the build directory run:
```sh
./cppmm ../test/imath/bind  -- -I/home/anders/packages/imath/2.4.0/include 
```
This will generate a file called `out.xml` containing the AST for V3f, V3i, Box3f and Box3i
