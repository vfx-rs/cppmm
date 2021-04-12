cmake_minimum_required(VERSION 3.5)
project(usd-c)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
add_library(usd-c SHARED
    tftoken-c.cpp
)
target_include_directories(usd-c PRIVATE .)
target_include_directories(usd-c PRIVATE /home/anders/packages/boost/1.70.0/include)
target_include_directories(usd-c PRIVATE /home/anders/packages/openexr/2.5.5/include)
target_include_directories(usd-c PRIVATE /home/anders/packages/usd/20.05/include)
install(TARGETS usd-c DESTINATION ${CMAKE_INSTALL_PREFIX})