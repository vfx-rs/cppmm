cmake_minimum_required(VERSION 3.5)
project(rustify_enum-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(SOURCES
    src/c-renum.cpp
    src/rustify_enum-errors.cpp
)
set(LIBNAME rustify_enum-c-0_1)
add_library(${LIBNAME} STATIC ${SOURCES})
add_library(${LIBNAME}-shared SHARED ${SOURCES})
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/rustify_enum/include)
target_include_directories(${LIBNAME}-shared PRIVATE /home/anders/code/cppmm/test/rustify_enum/include)
target_include_directories(${LIBNAME} PRIVATE include)
target_include_directories(${LIBNAME}-shared PRIVATE include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})