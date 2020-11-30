cmake_minimum_required(VERSION 3.5)
project(templates-c)

add_library(templates-c STATIC
  templates_bind.cpp
  cppmm_containers.cpp
)

target_compile_options(templates-c PRIVATE
  -fno-strict-aliasing
)

target_include_directories(templates-c PUBLIC
  /home/anders/code/cppmm/test/templates/bind
)

target_link_libraries(templates-c PUBLIC
  
)

install(TARGETS templates-c DESTINATION ${CMAKE_INSTALL_PREFIX})
