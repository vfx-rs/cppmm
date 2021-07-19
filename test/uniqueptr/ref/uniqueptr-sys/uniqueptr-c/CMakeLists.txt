cmake_minimum_required(VERSION 3.5)
project(uniqueptr-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(SOURCES
    src/foo.cpp
    src/uptr.cpp
    src/uniqueptr-errors.cpp
)
set(LIBNAME uniqueptr-c-0_1)
add_library(${LIBNAME} STATIC ${SOURCES})
add_library(${LIBNAME}-shared SHARED ${SOURCES})
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/uniqueptr/include)
target_include_directories(${LIBNAME}-shared PRIVATE /home/anders/code/cppmm/test/uniqueptr/include)
target_include_directories(${LIBNAME} PRIVATE include)
target_include_directories(${LIBNAME}-shared PRIVATE include)
target_include_directories(${LIBNAME} PRIVATE src)
target_include_directories(${LIBNAME}-shared PRIVATE src)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})