project=openexr

pushd build

# Generate the ast
./astgen/astgen ../test/$project/bind -u              \
    -o ../test/$project/ref/ast                   \
    -i $PWD/../test/$project/bind             \
    -rust-sys $PWD/../test/std/rust      \
    --                                   \
    -I/Volumes/src/cppmm/test/                   \
    -I/Volumes/src/cppmm/test/$project/bind                   \
    -I/Volumes/src/packages/usr/local/include \
    -I/Volumes/src/packages/usr/local/include/OpenEXR \
    -isysroot/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk \
    -isystem /Volumes/src/clang+llvm-11.0.0-x86_64-apple-darwin/include/c++/v1 \
    -isystem /Volumes/src/clang+llvm-11.0.0-x86_64-apple-darwin/lib/clang/11.0.0/include

# Generate the cpp
rm -rf out
mkdir -p out
./asttoc/asttoc -L /Volumes/src/packages/usr/local/lib -l Imath -o out ../test/$project/ref/ast

popd
