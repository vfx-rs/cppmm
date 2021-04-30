cmake_minimum_required(VERSION 3.5)
project(dtor-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(LIBNAME dtor-c-0_1)
add_library(${LIBNAME} SHARED
    c-dtor.cpp
    std_string.cpp
)
target_include_directories(${LIBNAME} PRIVATE .)
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/dtor/include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})