cmake_minimum_required(VERSION 3.5)

add_subdirectory(fmt)

set(LLVM_ENABLE_RTTI ON)
set(CMAKE_CXX_FLAGS "")

add_executable(asttoc
  src/main.cpp
  src/pystring.cpp
  src/cppmm_ast_read.cpp
  src/cppmm_ast_add_c.cpp
  src/cppmm_ast_write.cpp
)

target_include_directories(asttoc PRIVATE include)
