cmake_minimum_required(VERSION 3.5)
project(deep_namespace-c)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
add_library(deep_namespace-c SHARED
    c-dn.cpp
)
target_include_directories(deep_namespace-c PRIVATE .)
target_include_directories(deep_namespace-c PRIVATE /home/anders/code/cppmm/test/deep_namespace/include)
install(TARGETS deep_namespace-c DESTINATION ${CMAKE_INSTALL_PREFIX})