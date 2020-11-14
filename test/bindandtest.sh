#!/usr/bin/env bash
./cppmm                                                             \
    ../test/oiio_min                                                \
    -n OIIO=OpenImageIO_v2_2                                        \
    -o oiio_min-c                                                   \
    -l /home/anders/packages/oiio/2.2.8/lib/libOpenImageIO.so       \
    --                                                              \
    -I/home/anders/packages/oiio/2.2.8/include                      \
    -I/home/anders/packages/openexr/2.4.0/include                   \
    -isystem /home/anders/packages/llvm/10.0.1/lib/clang/10.0.1/include/

./cppmm                                                             \
    ../test/half                                                    \
    -o half-c                                                       \
    -u                                                              \
    -l /home/anders/packages/imath/3.0.0/lib/libhalf.so             \
    --                                                              \
    -I/home/anders/packages/imath/3.0.0/include                     \
    -isystem /home/anders/packages/llvm/10.0.1/lib/clang/10.0.1/include

../test/diff.sh
