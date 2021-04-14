add_executable(astgen
  src/astgen.cpp
  src/pystring.cpp
  src/process_binding.cpp
  src/resources.cpp
  )

target_link_libraries(astgen 
    clangTooling clangBasic clangASTMatchers 
    spdlog::spdlog 
    nlohmann_json::nlohmann_json)

target_compile_definitions(astgen 
    PRIVATE 
    SPDLOG_ACTIVE_LEVEL=TRACE)

target_include_directories(astgen 
    PRIVATE 
    ${LLVM_INCLUDE_DIRS})

install(TARGETS astgen DESTINATION ${CMAKE_INSTALL_BINDIR})
