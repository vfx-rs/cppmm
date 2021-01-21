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
Then to run:
```
./cppmm ../test/half/bind -u            \
    -l </path/to/half/library>          \
    -o </path/to/generated/project>     \
    --                                  \
    -I</path/to/imath/includes>         \
    -isystem </path/to/libc++/includes>
```
for me this is:
```
./cppmm ../test/half/bind -u                                    \
    -l /home/anders/packages/imath/3.0.0/lib/libhalf.so         \
    -o half-c                                                   \
    --                                                          \
    -I/home/anders/packages/openexr/3.0.0/include               \
    -isystem /home/anders/packages/llvm/10.0.1/lib/clang/10.0.1/include/
```
Note the use of `-isystem` to specify the clang includes. This is necessary to stop the generator passing that include directory to the C library build, which is probably not what you want.

This will generate a CMake project called `half-c` in the build directory, which you can build in the usual way.

### Testsuite
If you want to run the automated tests, do this from the `build` directory:
```bash
../test/bindandtest.sh
```
Note you'll first need to modify the commands in bindandtest.sh to modify your local environment. This script just binds the tests `half`, `oiio_min` and `containers` and diffs their output against the pre-generated projects in each test's `ref` directory. If you get no output, that means everything matches.

### Limitations
- No support for binding constants or #defines
- No support for function pointers
- Template monomorphization is currently limited to builtins (float, int etc.)
- Template methods on a template class (i.e. methods that have their own template parameter list) are not currently supported.


## Todo
- [ ] Add support for binding straight from the original C++ headers with attributes
- [x] Add Rust -sys crate output
- [x] Add automatic tests including test runners (rely on Rust for this?)
- [x] Add type registry and warn on missing type declarations
- [x] Add parameter names for copy constructors and assignment operators
- [x] Add support for declaring enums
- [x] Add support for free functions
- [x] Add support for returning strings
- [x] Add support for vector
- [x] Add support for generating C versions of C++ types (value types)
- [x] Figure out how to parse attributes inside macros
