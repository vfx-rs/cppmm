set(testname usd)

add_test(NAME ${testname} 
    COMMAND 
        python 
            ${CMAKE_SOURCE_DIR}/test/runtest.py 
            $<TARGET_FILE:astgen> 
            $<TARGET_FILE:asttoc> 
            ${CMAKE_CURRENT_SOURCE_DIR}/bind 
            ${CMAKE_BINARY_DIR}/test/${testname}/output
            ${testname}
            ${CMAKE_CURRENT_SOURCE_DIR}/ref
            -I$ENV{OPENEXR_ROOT}/include
            -I$ENV{USD_ROOT}/include
            -I$ENV{BOOST_ROOT}/include
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
