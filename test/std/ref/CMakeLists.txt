cmake_minimum_required(VERSION 3.5)
project(ref)

set (CMAKE_CXX_STANDARD 11)

add_library(ref STATIC
  test_bind.cpp
  cppmm_containers.cpp
  std_string.cpp
)

target_compile_options(ref PRIVATE
  -fno-strict-aliasing
)

target_include_directories(ref PUBLIC
  ../test/std/bind
  /Volumes/src/cppmm/build/../test/std/bind
)

target_link_libraries(ref PUBLIC
  
)

install(TARGETS ref DESTINATION ${CMAKE_INSTALL_PREFIX})
