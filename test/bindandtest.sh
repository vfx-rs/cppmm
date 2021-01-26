#!/usr/bin/env bash

set -e

./cppmm                                                             \
    ../test/oiio_min/bind                                           \
    -n OIIO=OpenImageIO_v2_2                                        \
    -o oiio_min-c                                                   \
    --rust-sys oiio_min-sys                                         \
    -l ${OIIO_ROOT}/lib/libOpenImageIO.so                           \
    --                                                              \
    -I${OIIO_ROOT}/include                                          \
    -I${OPENEXR_ROOT}/include                                       \
    -isystem ${LLVM_ROOT}/lib/clang/11.0.0/include/

./cppmm                                                             \
    ../test/half/bind                                               \
    -n Imath=Imath_3_0                                              \
    -o half-c                                                       \
    --rust-sys half-sys                                             \
    -u                                                              \
    -l /home/anders/packages/imath/3.0.0/lib/libhalf.so             \
    --                                                              \
    -I/home/anders/packages/imath/3.0.0/include                     \
    -isystem ${LLVM_ROOT}/lib/clang/11.0.0/include

./cppmm                                                             \
    ../test/imath/bind                                               \
    -n Imath=Imath_3_0                                              \
    -o imath-c                                                       \
    --rust-sys imath-sys                                             \
    -u                                                              \
    -l /home/anders/packages/imath/3.0.0/lib/libImath.so             \
    --                                                              \
    -I/home/anders/packages/imath/3.0.0/include                     \
    -isystem ${LLVM_ROOT}/lib/clang/11.0.0/include

./cppmm                                                             \
    ../test/containers/bind                                         \
    -o containers-c                                                 \
    --rust-sys containers-sys                                       \
    --                                                              \
    -I/home/anders/code/cppmm/test/containers/bind                  \
    -isystem ${LLVM_ROOT}/lib/clang/11.0.0/include

cp ../test/containers/test-rust-sys/test.rs                         \
    containers-sys/src/test.rs

pushd containers-sys && cargo test
popd

./cppmm                                                             \
    ../test/templates/bind                                          \
    -o templates-c                                                  \
    --rust-sys templates-sys                                        \
    --                                                              \
    -I/home/anders/code/cppmm/test/templates/bind                   \
    -isystem ${LLVM_ROOT}/lib/clang/11.0.0/include

# USD_ROOT=/home/anders/packages/usd/20.05
# ./cppmm                                                             \
#     ../test/usd/bind                                                \
#     -o usd-c                                                        \
#     -n pxr=pxrInternal_v0_20__pxrReserved__                         \
#     -l ${USD_ROOT}/lib/libtf.so                                     \
#     --rust-sys usd-sys                                              \
#     --                                                              \
#     -I${USD_ROOT}/include                                           \
#     -isystem ${LLVM_ROOT}/lib/clang/11.0.0/include

# cp ../test/usd/test-rust-sys/test.rs                         \
#     usd-sys/src/test.rs

# pushd usd-sys && env LD_LIBRARY_PATH=${USD_ROOT}/lib cargo test
# popd

../test/diff.sh
