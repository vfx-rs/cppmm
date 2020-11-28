cmake_minimum_required(VERSION 3.5)
project(oiio_min-c)

add_library(oiio_min-c STATIC
  c-typedesc.cpp
  c-filesystem.cpp
  c-imageio.cpp
  cppmm_containers.cpp
)

target_compile_options(oiio_min-c PRIVATE
  -fno-strict-aliasing
)

target_include_directories(oiio_min-c PUBLIC
  /home/anders/packages/oiio/2.2.8/include
  /home/anders/packages/openexr/2.4.0/include
)

target_link_libraries(oiio_min-c PUBLIC
  /home/anders/packages/oiio/2.2.8/lib/libOpenImageIO.so
)

install(TARGETS oiio_min-c DESTINATION ${CMAKE_INSTALL_PREFIX})
