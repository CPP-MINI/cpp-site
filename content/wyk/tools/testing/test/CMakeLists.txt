add_executable(fn_test gtest_demo.cpp fib_test.cpp string_test.cpp)
target_link_libraries(fn_test PRIVATE GTest::gtest_main functions)
