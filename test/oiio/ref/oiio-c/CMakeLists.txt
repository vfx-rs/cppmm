cmake_minimum_required(VERSION 3.5)
project(oiio-c)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
add_library(oiio-c SHARED
    std_vector.cpp
    c-filesystem.cpp
    c-typedesc.cpp
    c-imageio.cpp
    std_string.cpp
)
target_include_directories(oiio-c PRIVATE .)
target_include_directories(oiio-c PRIVATE /home/anders/packages/oiio/2.2.8/include)
target_include_directories(oiio-c PRIVATE /home/anders/packages/openexr/2.5.5/include)
install(TARGETS oiio-c DESTINATION ${CMAKE_INSTALL_PREFIX})