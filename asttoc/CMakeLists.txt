cmake_minimum_required(VERSION 3.5)

add_subdirectory(fmt)

add_executable(asttoc
  src/main.cpp
  src/pystring.cpp
  src/cppmm_ast_read.cpp
  src/cppmm_ast_add_c.cpp
  src/cppmm_ast_write_c.cpp
  src/cppmm_ast_write_cmake.cpp
  src/cppmm_ast_write_rustsys.cpp
)

target_include_directories(asttoc PRIVATE include)
target_include_directories(asttoc PRIVATE fmt/include)
target_include_directories(asttoc PRIVATE ${LLVM_INCLUDE_DIRS})

target_link_libraries(asttoc fmt spdlog::spdlog LLVMSupport)

install(TARGETS asttoc DESTINATION ${CMAKE_INSTALL_BINDIR})
