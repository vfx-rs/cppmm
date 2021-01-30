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
add_subdirectory(asttoc)

add_executable(cppmm
  src/cppmm.cpp
  src/pystring.cpp
  src/process_binding.cpp
  )

target_link_libraries(cppmm clangTooling clangBasic clangASTMatchers spdlog::spdlog nlohmann_json::nlohmann_json)
target_compile_definitions(cppmm PRIVATE SPDLOG_ACTIVE_LEVEL=TRACE)
target_include_directories(cppmm PRIVATE ${LLVM_INCLUDE_DIRS})

# Copy the clang headers to the build directory so tests work
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# Install the headers alongside the binary
install(DIRECTORY resources DESTINATION ${CMAKE_INSTALL_PREFIX})

enable_testing()

add_subdirectory(test/std)
add_subdirectory(test/imath)
add_subdirectory(test/oiio)
