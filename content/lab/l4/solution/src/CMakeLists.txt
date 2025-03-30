
add_subdirectory(base32)

# Define an executable which depends on the shared base32 library
add_executable(l4_base32)
target_sources(l4_base32 PRIVATE main.cpp)
target_link_libraries(l4_base32 PRIVATE base32)

