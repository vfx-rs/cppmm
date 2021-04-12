cmake_minimum_required(VERSION 3.5)
project(std-c)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
add_library(std-c SHARED
    c-usestd.cpp
    std_string.cpp
)
target_include_directories(std-c PRIVATE .)
target_include_directories(std-c PRIVATE /home/anders/code/cppmm/test/std/include)
install(TARGETS std-c DESTINATION ${CMAKE_INSTALL_PREFIX})