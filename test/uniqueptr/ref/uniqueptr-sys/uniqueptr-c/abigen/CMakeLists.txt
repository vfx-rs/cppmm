file(GLOB_RECURSE ABIGEN_SOURCE *.cpp)
add_executable(abigen ${ABIGEN_SOURCE})
target_include_directories(abigen PRIVATE /home/anders/code/cppmm/test/uniqueptr/include)
target_include_directories(abigen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
