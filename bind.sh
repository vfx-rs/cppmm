project=imath

pushd build
./cppmm ../test/$project/bind -u              \
    -o ../test/$project/ref                   \
    -i $PWD/../test/$project/bind             \
    -rust-sys $PWD/../test/std/rust      \
    --                                   \
    -I../test/                   \
    -I../test/$project/bind                   \
    -I/Volumes/src/packages/usr/local/include \
    -isysroot/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk \
    -isystem /Volumes/src/clang+llvm-11.0.0-x86_64-apple-darwin/include/c++/v1 \
    -isystem /Volumes/src/clang+llvm-11.0.0-x86_64-apple-darwin/lib/clang/11.0.0/include
popd
