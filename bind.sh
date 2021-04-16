project=openexr

pushd build

# Generate the ast
./astgen/astgen ../test/$project/bind -u              \
    -o ../test/$project/ref/ast                   \
    -rust-sys $PWD/../test/std/rust      \
    --                                   \
    -I/Volumes/src/cppmm/test/                   \
    -I/Volumes/src/packages/include \
    -I/Volumes/src/packages/include/OpenEXR \
    -I/usr/local/include \
    -isysroot/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk \
    -isystem /Volumes/src/clang+llvm-11.0.0-x86_64-apple-darwin/include/c++/v1
##
##-i $PWD/../test/$project/bind             \
#-I/Volumes/src/cppmm/test/$project/bind                   \

#cp ../test/openexr/imf_attribute_patched.json ../test/openexr/ref/ast/imf_attribute.json

# Generate the cpp
rm -rf out
mkdir -p out
./asttoc/asttoc -L /Volumes/src/packages/lib -l Imath -l IlmImf -l IlmImfUtil -l Half -l IlmThread -l Iex -l IexMath -p openexr -o out ../test/$project/ref/ast

popd
