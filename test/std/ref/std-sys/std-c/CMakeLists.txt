cmake_minimum_required(VERSION 3.5)
project(std-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(SOURCES
    src/c-usestd.cpp
    src/std_set.cpp
    src/std_string.cpp
    src/std-errors.cpp
)
set(LIBNAME std-c-0_1)
add_library(${LIBNAME} STATIC ${SOURCES})
add_library(${LIBNAME}-shared SHARED ${SOURCES})
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/std/include)
target_include_directories(${LIBNAME}-shared PRIVATE /home/anders/code/cppmm/test/std/include)
target_include_directories(${LIBNAME} PRIVATE include)
target_include_directories(${LIBNAME}-shared PRIVATE include)
target_include_directories(${LIBNAME} PRIVATE src)
target_include_directories(${LIBNAME}-shared PRIVATE src)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})