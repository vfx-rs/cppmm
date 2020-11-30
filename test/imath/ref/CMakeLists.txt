cmake_minimum_required(VERSION 3.5)
project(imath-c)

add_library(imath-c STATIC
  imath_vec.cpp
  cppmm_containers.cpp
)

target_compile_options(imath-c PRIVATE
  -fno-strict-aliasing
)

target_include_directories(imath-c PUBLIC
  /home/anders/packages/imath/3.0.0/include
)

target_link_libraries(imath-c PUBLIC
  /home/anders/packages/imath/3.0.0/lib/libImath.so
)

install(TARGETS imath-c DESTINATION ${CMAKE_INSTALL_PREFIX})
