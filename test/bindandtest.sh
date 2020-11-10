#!/usr/bin/env bash
./cppmm                                                             \
    ../test/oiio_min/c-typedesc.cpp                                 \
    ../test/oiio_min/c-imageio.cpp                                  \
    ../test/oiio_min/c-filesystem.cpp                               \
    -n OIIO=OpenImageIO_v2_2                                        \
    --                                                              \
    -I/home/anders/packages/oiio/2.2.8/include                      \
    -I/home/anders/packages/openexr/2.4.0/include                   \
    -I/home/anders/packages/llvm/10.0.1/lib/clang/10.0.1/include/

./cppmm                                                             \
    ../test/half/half.cpp                                           \
    -u                                                              \
    -n Imath=Imath_3_0                                              \
    --                                                              \
    -I/home/anders/packages/imath/3.0.0/include                     \
    -I/home/anders/packages/llvm/10.0.1/lib/clang/10.0.1/include

../test/diff.sh
