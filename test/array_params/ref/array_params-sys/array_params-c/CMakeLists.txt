cmake_minimum_required(VERSION 3.5)
project(array_params-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(SOURCES
    src/c-array_params.cpp
    src/array_params-errors.cpp
)
set(LIBNAME array_params-c-0_1)
add_library(${LIBNAME} STATIC ${SOURCES})
add_library(${LIBNAME}-shared SHARED ${SOURCES})
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/array_params/include)
target_include_directories(${LIBNAME}-shared PRIVATE /home/anders/code/cppmm/test/array_params/include)
target_include_directories(${LIBNAME} PRIVATE include)
target_include_directories(${LIBNAME}-shared PRIVATE include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})