
# Download a cmake library during the configure phase
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.16.0
)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

add_executable(
        base32_test
        encoder_test.cpp
        decoder_test.cpp
)
target_link_libraries(
        base32_test
        PRIVATE
        GTest::gtest_main
        base32_static
)
gtest_discover_tests(base32_test)
