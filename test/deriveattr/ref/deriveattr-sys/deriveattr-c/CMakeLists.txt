cmake_minimum_required(VERSION 3.5)
project(deriveattr-c VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
set(SOURCES
    src/dattr.cpp
    include/dattr.h
    src/deriveattr-errors.cpp
)

add_subdirectory(abigen)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/dattr.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include.in/dattr.h 
    COMMAND abigen
    COMMAND python ARGS 
        ${CMAKE_CURRENT_SOURCE_DIR}/abigen/insert_abi.py 
        ${CMAKE_CURRENT_SOURCE_DIR}/include.in 
        ${CMAKE_CURRENT_BINARY_DIR}/include 
        ${CMAKE_CURRENT_BINARY_DIR}/abigen.txt
)
set(LIBNAME deriveattr-c-0_1)
add_library(${LIBNAME} STATIC ${SOURCES})
add_library(${LIBNAME}-shared SHARED ${SOURCES})

set_target_properties(${LIBNAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)
set_target_properties(${LIBNAME}-shared PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_definitions(${LIBNAME} PRIVATE DERIVEATTR_CPPMM_BUILD_EXPORT)
target_compile_definitions(${LIBNAME}-shared PRIVATE DERIVEATTR_CPPMM_BUILD_EXPORT)
if (WIN32)
target_compile_definitions(${LIBNAME} PRIVATE _Bool=bool)
target_compile_definitions(${LIBNAME}-shared PRIVATE _Bool=bool)
endif()
target_include_directories(${LIBNAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_include_directories(${LIBNAME}-shared PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_include_directories(${LIBNAME} PRIVATE /home/anders/code/cppmm/test/deriveattr/include)
target_include_directories(${LIBNAME}-shared PRIVATE /home/anders/code/cppmm/test/deriveattr/include)
target_include_directories(${LIBNAME} PRIVATE include)
target_include_directories(${LIBNAME}-shared PRIVATE include)
target_include_directories(${LIBNAME} PRIVATE src)
target_include_directories(${LIBNAME}-shared PRIVATE src)
install(TARGETS ${LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS ${LIBNAME}-shared DESTINATION ${CMAKE_INSTALL_PREFIX})
