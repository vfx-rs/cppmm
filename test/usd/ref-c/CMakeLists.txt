cmake_minimum_required(VERSION 3.5)
project(/home/anders/code/cppmm/test/usd/ref-c)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
add_library(/home/anders/code/cppmm/test/usd/ref-c SHARED
    tftoken-c.cpp
)
target_include_directories(/home/anders/code/cppmm/test/usd/ref-c PRIVATE .)
target_include_directories(/home/anders/code/cppmm/test/usd/ref-c PRIVATE /home/anders/packages/boost/1.70.0/include)
target_include_directories(/home/anders/code/cppmm/test/usd/ref-c PRIVATE /home/anders/packages/usd/20.05/include)
install(TARGETS /home/anders/code/cppmm/test/usd/ref-c DESTINATION ${CMAKE_INSTALL_PREFIX})