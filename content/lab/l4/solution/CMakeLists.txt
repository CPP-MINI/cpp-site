cmake_minimum_required(VERSION 3.16)
project(l4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)
