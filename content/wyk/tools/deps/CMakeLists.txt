cmake_minimum_required(VERSION 3.20)
project(deps VERSION 1.0.0)

 find_package(fmt CONFIG REQUIRED)

# add_subdirectory(libs/fmt)

# include(FetchContent)
# FetchContent_Declare(
#         fmt
#         GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#         GIT_TAG 10.1.1 # Use the specific version you want (e.g., latest stable tag)
# )
# FetchContent_MakeAvailable(fmt)

add_subdirectory(src)
