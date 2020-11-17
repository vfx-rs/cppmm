#!/usr/bin/env bash
./cppmm                                                             \
    ../test/oiio_min/bind                                           \
    -n OIIO=OpenImageIO_v2_2                                        \
    -o oiio_min-c                                                   \
    --rust-sys oiio_min-sys                                         \
    -l /home/anders/packages/oiio/2.2.8/lib/libOpenImageIO.so       \
    --                                                              \
    -I/home/anders/packages/oiio/2.2.8/include                      \
    -I/home/anders/packages/openexr/2.4.0/include                   \
    -isystem /home/anders/packages/llvm/10.0.1/lib/clang/10.0.1/include/

./cppmm                                                             \
    ../test/half/bind                                               \
    -o half-c                                                       \
    --rust-sys half-sys                                             \
    -u                                                              \
    -l /home/anders/packages/imath/3.0.0/lib/libhalf.so             \
    --                                                              \
    -I/home/anders/packages/imath/3.0.0/include                     \
    -isystem /home/anders/packages/llvm/10.0.1/lib/clang/10.0.1/include

./cppmm                                                             \
    ../test/containers/bind                                         \
    -o containers-c                                                 \
    --rust-sys containers-sys                                       \
    --                                                              \
    -I/home/anders/code/cppmm/test/containers/bind                  \
    -isystem /home/anders/packages/llvm/10.0.1/lib/clang/10.0.1/include

cp ../test/containers/test-rust-sys/test.rs                         \
    containers-sys/src/test.rs

pushd containers-sys && cargo test
popd

../test/diff.sh
