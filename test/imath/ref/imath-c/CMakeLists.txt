cmake_minimum_required(VERSION 3.5)
project(imath-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(LIBNAME imath-c-0_1)
add_library(${LIBNAME} SHARED
    imath_vec.cpp
    imath_box.cpp
imath-errors.cpp
)
target_include_directories(${LIBNAME} PRIVATE .)
target_include_directories(${LIBNAME} PRIVATE /home/anders/packages/openexr/2.5.5/include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})