cmake_minimum_required(VERSION 3.5)
project(oiio-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(LIBNAME oiio-c-0_1)
add_library(${LIBNAME} SHARED
    std_vector.cpp
    c-filesystem.cpp
    c-typedesc.cpp
    c-imageio.cpp
    std_string.cpp
)
target_include_directories(${LIBNAME} PRIVATE .)
target_include_directories(${LIBNAME} PRIVATE /home/anders/packages/oiio/2.2.8/include)
target_include_directories(${LIBNAME} PRIVATE /home/anders/packages/openexr/2.5.5/include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})