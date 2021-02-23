cmake_minimum_required(VERSION 3.5)
project(cppmm)

set(LLVM_ROOT $ENV{LLVM_ROOT})
set(CMAKE_PREFIX_PATH "${LLVM_ROOT}/lib/cmake/clang")
find_package(Clang REQUIRED CONFIG)

# Use the same C++ standard as LLVM does
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

add_subdirectory(spdlog)
add_subdirectory(json)

add_subdirectory(astgen)
add_subdirectory(asttoc)

enable_testing()

add_subdirectory(test/std)
add_subdirectory(test/imath)
# add_subdirectory(test/openexr)
add_subdirectory(test/oiio)
add_subdirectory(test/usd)
