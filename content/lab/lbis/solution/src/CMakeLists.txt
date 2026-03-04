

# Define an executable which depends on the shared base32 library
add_executable(lbis_base32 main.cpp)
target_link_libraries(lbis_base32 PRIVATE base32)

