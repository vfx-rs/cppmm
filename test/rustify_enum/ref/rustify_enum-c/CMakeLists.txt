cmake_minimum_required(VERSION 3.5)
project(rustify_enum-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(LIBNAME rustify_enum-c-0_1)
add_library(${LIBNAME} SHARED
    c-renum.cpp
)
target_include_directories(${LIBNAME} PRIVATE .)
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/rustify_enum/include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})