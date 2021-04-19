cmake_minimum_required(VERSION 3.5)
project(comments-c)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
add_library(comments-c SHARED
    c-comments.cpp
)
target_include_directories(comments-c PRIVATE .)
target_include_directories(comments-c PRIVATE /home/anders/code/cppmm/test/comments/include)
install(TARGETS comments-c DESTINATION ${CMAKE_INSTALL_PREFIX})