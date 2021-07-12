cmake_minimum_required(VERSION 3.5)
project(tmp_specs-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(SOURCES
    src/c-specs.cpp
    src/tmp_specs-errors.cpp
)
set(LIBNAME tmp_specs-c-0_1)
add_library(${LIBNAME} STATIC ${SOURCES})
add_library(${LIBNAME}-shared SHARED ${SOURCES})
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/tmp_specs/include)
target_include_directories(${LIBNAME}-shared PRIVATE /home/anders/code/cppmm/test/tmp_specs/include)
target_include_directories(${LIBNAME} PRIVATE include)
target_include_directories(${LIBNAME}-shared PRIVATE include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})