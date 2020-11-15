cmake_minimum_required(VERSION 3.5)
project(containers-c)

add_library(containers-c STATIC
  containers_bind.cpp
  cppmm_containers.cpp
)

target_compile_options(containers-c PRIVATE
  -fno-strict-aliasing
)

target_include_directories(containers-c PUBLIC
  /home/anders/code/cppmm/test/containers
)

target_link_libraries(containers-c PUBLIC
  
)
