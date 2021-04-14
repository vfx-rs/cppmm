add_executable(genbind
  src/genbind.cpp
  src/pystring.cpp
  )

target_link_libraries(genbind clangTooling clangBasic clangASTMatchers spdlog::spdlog nlohmann_json::nlohmann_json)
target_compile_definitions(genbind PRIVATE SPDLOG_ACTIVE_LEVEL=TRACE)
target_include_directories(genbind PRIVATE ${LLVM_INCLUDE_DIRS})

install(TARGETS genbind DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES src/genbind.py DESTINATION ${CMAKE_INSTALL_BINDIR})
