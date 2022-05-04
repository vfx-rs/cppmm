cmake_minimum_required(VERSION 3.5)
project(cppmm)

include(GNUInstallDirs)

set(CPPMM_MAJOR_VERSION 0)
set(CPPMM_MINOR_VERSION 11)
set(CPPMM_PATCH_VERSION 0)
set(CPPMM_VERSION "${CPPMM_MAJOR_VERSION}.${CPPMM_MINOR_VERSION}.${CPPMM_PATCH_VERSION}")

# Allow find_package to use <package>_ROOT variables when finding packages.
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

find_package(Clang REQUIRED CONFIG)

# Use the same C++ standard as LLVM does
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
# Generate info for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Simplify installation messages
set(CMAKE_INSTALL_MESSAGE LAZY)

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  add_compile_options(-fno-rtti)
endif()

# Configure version header and rez package manifest
option(CPPMM_INCLUDE_REZ "Install package.py for rez" OFF)
set(CPPMM_REZ_DIR "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/rez"
    CACHE STRING "Install path for package.py")
if (CPPMM_INCLUDE_REZ)
    configure_file(include/cppmm_config.hpp.in ${CMAKE_SOURCE_DIR}/include/cppmm_config.hpp)
    configure_file(package.py.in ${CMAKE_SOURCE_DIR}/package.py)
    install(FILES package.py DESTINATION ${CPPMM_REZ_DIR})
endif()

add_subdirectory(spdlog)
add_subdirectory(json)

add_subdirectory(astgen)
add_subdirectory(asttoc)
add_subdirectory(genbind)

enable_testing()

add_subdirectory(test/std)
add_subdirectory(test/imath)
# add_subdirectory(test/openexr)
# add_subdirectory(test/oiio)
# add_subdirectory(test/usd)
add_subdirectory(test/array_params)
add_subdirectory(test/comments)
add_subdirectory(test/deep_namespace)
add_subdirectory(test/function_pointers)
add_subdirectory(test/rustify_enum)
add_subdirectory(test/tmp_specs)
add_subdirectory(test/dtor)
add_subdirectory(test/opaqueptr)
add_subdirectory(test/exceptions)
add_subdirectory(test/nested)
add_subdirectory(test/uniqueptr)
add_subdirectory(test/property)
add_subdirectory(test/opaquebytes)
add_subdirectory(test/deriveattr)
add_subdirectory(test/mimpl)
add_subdirectory(test/copymoveaccess)
