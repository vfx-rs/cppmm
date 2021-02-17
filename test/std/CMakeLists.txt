add_test(NAME std 
    COMMAND 
        python 
            ${CMAKE_SOURCE_DIR}/test/runtest.py 
            $<TARGET_FILE:astgen> 
            ${CMAKE_CURRENT_SOURCE_DIR}/bind 
            ${CMAKE_BINARY_DIR}/test/std/ast
            ${CMAKE_CURRENT_SOURCE_DIR}/ref
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
