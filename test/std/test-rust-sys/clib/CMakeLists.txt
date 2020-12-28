cmake_minimum_required(VERSION 3.5)
project(clib)

set (CMAKE_CXX_STANDARD 11)

add_library(clib STATIC
  test_bind.cpp
  cppmm_containers.cpp
  std_string.cpp
)

target_compile_options(clib PRIVATE
  -fno-strict-aliasing
)

target_include_directories(clib PUBLIC
  ../test/std/bind
  /Volumes/src/cppmm/build/../test/std/bind
)

target_link_libraries(clib PUBLIC
  
)

install(TARGETS clib DESTINATION ${CMAKE_INSTALL_PREFIX})
