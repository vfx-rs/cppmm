set(testname imath)
set(includes "-I/home/anders/packages/openexr/2.4.0/include")

add_test(NAME ${testname} 
    COMMAND 
        python 
            ${CMAKE_SOURCE_DIR}/test/runtest.py 
            $<TARGET_FILE:cppmm> 
            ${CMAKE_CURRENT_SOURCE_DIR}/bind 
            ${CMAKE_BINARY_DIR}/test/${testname}/ast
            ${CMAKE_CURRENT_SOURCE_DIR}/ref
            ${includes}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
