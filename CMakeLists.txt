cmake_minimum_required(VERSION 3.5)
project(cppmm)

set(LLVM_ROOT $ENV{LLVM_ROOT})
set(CMAKE_PREFIX_PATH "${LLVM_ROOT}/lib/cmake/clang")
find_package(Clang REQUIRED CONFIG)

# Use the same C++ standard as LLVM does
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

add_subdirectory(fmt)

add_executable(cppmm
  src/cppmm.cpp
  src/pystring.cpp
  src/param.cpp
  src/namespaces.cpp
  src/type.cpp
  src/attributes.cpp
  src/record.cpp
  src/function.cpp
  src/method.cpp
  src/enum.cpp
  src/exports.cpp
  src/match_bindings.cpp
  src/match_decls.cpp
  src/decls.cpp
  )

target_link_libraries(cppmm clangTooling clangBasic clangASTMatchers fmt)
target_include_directories(cppmm PRIVATE ${LLVM_INCLUDE_DIRS})
# target_link_libraries(cppmm PRIVATE ${LLVM_ROOT}/lib/libclangTooling.a ${LLVM_ROOT}/lib/libclang.so)
