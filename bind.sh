pushd build
./cppmm ../test/std/bind -u              \
    -o ../test/std/ref                   \
    -i $PWD/../test/std/bind             \
    -rust-sys $PWD/../test/std/rust      \
    --                                   \
    -I../test/std/bind                   \
    -isysroot/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk \
    -isystem /Volumes/src/clang+llvm-11.0.0-x86_64-apple-darwin/include/c++/v1 \
    -isystem /Volumes/src/clang+llvm-11.0.0-x86_64-apple-darwin/lib/clang/11.0.0/include
popd
