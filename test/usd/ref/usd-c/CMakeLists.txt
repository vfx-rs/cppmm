cmake_minimum_required(VERSION 3.5)
project(usd-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(LIBNAME usd-c-0_1)
add_library(${LIBNAME} SHARED
    tftoken-c.cpp
)
target_include_directories(${LIBNAME} PRIVATE .)
target_include_directories(${LIBNAME} PRIVATE /home/anders/packages/boost/1.70.0/include)
target_include_directories(${LIBNAME} PRIVATE /home/anders/packages/openexr/2.5.5/include)
target_include_directories(${LIBNAME} PRIVATE /home/anders/packages/usd/20.05/include)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})