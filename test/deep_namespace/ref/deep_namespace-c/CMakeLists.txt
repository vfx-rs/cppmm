cmake_minimum_required(VERSION 3.5)
project(deep_namespace-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(LIBNAME deep_namespace-c-0_1)
add_library(${LIBNAME} SHARED
    c-dn.cpp
)
target_include_directories(${LIBNAME} PRIVATE .)
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/deep_namespace/include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})