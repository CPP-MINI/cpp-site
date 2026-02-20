cmake_minimum_required(VERSION 3.20)
project(functions VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)
