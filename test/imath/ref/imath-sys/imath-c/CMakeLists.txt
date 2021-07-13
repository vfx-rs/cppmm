cmake_minimum_required(VERSION 3.5)
project(imath-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(SOURCES
    src/imath_vec.cpp
    src/imath_box.cpp
    src/imath-errors.cpp
)
set(LIBNAME imath-c-0_1)
add_library(${LIBNAME} STATIC ${SOURCES})
add_library(${LIBNAME}-shared SHARED ${SOURCES})
target_include_directories(${LIBNAME} PRIVATE /home/anders/packages/openexr/2.5.5/include)
target_include_directories(${LIBNAME}-shared PRIVATE /home/anders/packages/openexr/2.5.5/include)
target_include_directories(${LIBNAME} PRIVATE include)
target_include_directories(${LIBNAME}-shared PRIVATE include)
target_include_directories(${LIBNAME} PRIVATE src)
target_include_directories(${LIBNAME}-shared PRIVATE src)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})