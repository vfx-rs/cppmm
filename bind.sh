pushd build
./cppmm ../test/std/bind -u              \
    -o test-std-c                        \
    --                                   \
    -I../test/std/bind/std_string.hpp    \
    -isysroot/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk \
    -isystem /Volumes/src/clang+llvm-11.0.0-x86_64-apple-darwin/include/c++/v1 \
    -isystem /Volumes/src/clang+llvm-11.0.0-x86_64-apple-darwin/lib/clang/11.0.0/include
popd
