cmake_minimum_required(VERSION 3.5)
project(usd-c)

add_library(usd-c STATIC
  tftoken-c.cpp
  cppmm_containers.cpp
)

target_compile_options(usd-c PRIVATE
  -fno-strict-aliasing
)

target_include_directories(usd-c PUBLIC
  /home/anders/packages/usd/20.05/include
)

target_link_libraries(usd-c PUBLIC
  /home/anders/packages/usd/20.05/lib/libtf.so
)

install(TARGETS usd-c DESTINATION ${CMAKE_INSTALL_PREFIX})
