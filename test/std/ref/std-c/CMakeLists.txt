cmake_minimum_required(VERSION 3.5)
project(std-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(LIBNAME std-c-0_1)
add_library(${LIBNAME} SHARED
    c-usestd.cpp
    std_string.cpp
std-errors.cpp
)
target_include_directories(${LIBNAME} PRIVATE .)
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/std/include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})