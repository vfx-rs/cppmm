add_executable(astgen
  src/astgen.cpp
  src/pystring.cpp
  src/process_binding.cpp
  )

target_link_libraries(astgen clangTooling clangBasic clangASTMatchers spdlog::spdlog nlohmann_json::nlohmann_json)
target_compile_definitions(astgen PRIVATE SPDLOG_ACTIVE_LEVEL=TRACE)
target_compile_definitions(astgen PRIVATE
    CPPMM_PACKAGE_RESOURCES_DIR="${CPPMM_PACKAGE_RESOURCES_DIR}")
target_include_directories(astgen PRIVATE ${LLVM_INCLUDE_DIRS})

# Copy the clang headers to the build directory so tests work
file(COPY resources/ DESTINATION
    "${CMAKE_CURRENT_BINARY_DIR}/../${CPPMM_PACKAGE_RESOURCES_DIR}")
# Install the headers alongside the binary
install(DIRECTORY resources/ DESTINATION ${CPPMM_PACKAGE_RESOURCES_DIR})
install(TARGETS astgen DESTINATION ${CMAKE_INSTALL_BINDIR})
