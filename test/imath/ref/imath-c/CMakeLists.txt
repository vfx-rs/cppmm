cmake_minimum_required(VERSION 3.5)
project(imath-c)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
add_library(imath-c SHARED
    imath_vec.cpp
    imath_box.cpp
)
target_include_directories(imath-c PRIVATE .)
target_include_directories(imath-c PRIVATE /home/anders/packages/openexr/2.5.5/include)
install(TARGETS imath-c DESTINATION ${CMAKE_INSTALL_PREFIX})