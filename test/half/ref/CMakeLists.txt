cmake_minimum_required(VERSION 3.5)
project(half-c)

add_library(half-c STATIC
  half.cpp
  cppmm_containers.cpp
)

target_compile_options(half-c PRIVATE
  -fno-strict-aliasing
)

target_include_directories(half-c PUBLIC
  /home/anders/packages/imath/3.0.0/include
)

target_link_libraries(half-c PUBLIC
  /home/anders/packages/imath/3.0.0/lib/libhalf.so
)
