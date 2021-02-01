cmake_minimum_required(VERSION 3.5)

set(LLVM_ENABLE_RTTI ON)
set(CMAKE_CXX_FLAGS "")

add_executable(asttoc
  src/main.cpp
  src/cppmm_ast_read.cpp
  src/cppmm_ast_to_c.cpp
)

target_include_directories(asttoc PRIVATE include)
