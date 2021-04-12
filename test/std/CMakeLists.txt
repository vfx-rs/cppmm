add_test(NAME std 
    COMMAND 
        python 
            ${CMAKE_SOURCE_DIR}/test/runtest.py 
            $<TARGET_FILE:astgen> 
            $<TARGET_FILE:asttoc> 
            ${CMAKE_CURRENT_SOURCE_DIR}/bind
            ${CMAKE_BINARY_DIR}/test/std/output
            std
            ${CMAKE_CURRENT_SOURCE_DIR}/ref
            -I${CMAKE_CURRENT_SOURCE_DIR}/include
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
