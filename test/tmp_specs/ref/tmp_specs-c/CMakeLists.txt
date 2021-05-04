cmake_minimum_required(VERSION 3.5)
project(tmp_specs-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(LIBNAME tmp_specs-c-0_1)
add_library(${LIBNAME} SHARED
    c-specs.cpp
tmp_specs-errors.cpp
)
target_include_directories(${LIBNAME} PRIVATE .)
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/tmp_specs/include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})