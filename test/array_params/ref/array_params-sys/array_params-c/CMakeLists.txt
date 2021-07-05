cmake_minimum_required(VERSION 3.5)
project(array_params-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(LIBNAME array_params-c-0_1)
add_library(${LIBNAME} SHARED
    c-array_params.cpp
array_params-errors.cpp
)
target_include_directories(${LIBNAME} PRIVATE .)
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/array_params/include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})