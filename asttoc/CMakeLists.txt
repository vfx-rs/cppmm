cmake_minimum_required(VERSION 3.5)

add_subdirectory(fmt)

add_executable(asttoc
  src/main.cpp
  src/pystring.cpp
  src/cppmm_ast_read.cpp
  src/cppmm_ast_add_c.cpp
  src/cppmm_ast_write.cpp
)

target_include_directories(asttoc PRIVATE include)
target_include_directories(asttoc PRIVATE fmt/include)

target_link_libraries(asttoc fmt)
