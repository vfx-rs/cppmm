# CPPMM
C-plus-plus-minus-minus

## Introduction

`cppmm` is a binding generator for creating C and Rust interfaces to C++ libraries. It is targeting a very small subset of libraries--just those in consideration by the `vfx-rs` project--and is not expected to work for anything else and will have assumptions about the C++ it will accept based on the types and idioms found in those libraries baked into it.

## Quick start
You must have LLVM and clang installed. I've tested it with llvm 10.0.1 only. To run the test you'll need OIIO 2.2.8 and openexr 2.4.0 (other versions may work but are untested)

### Checkout
The repository includes fmtlib 4.1.0 as a submodule, so clone with `--recursive`:
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

### Run

From the build directory run:
```sh
./cppmm ../test/imath/bind  -- -I/home/anders/packages/imath/3.0.0/include -isystem $LLVM_ROOT/lib/clang/11.0.0/include
```
This will generate a file called `out.xml` containing the AST for V3f, V3i, Box3f and Box3i
