cmake_minimum_required(VERSION 3.16) # Version from Ubuntu20.04 - will be good enough
project(l4)

set(CMAKE_CXX_STANDARD 20) # Setting up C++ 20 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -fsanitize=address,leak")

# It makes all includes relative to project root
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)
