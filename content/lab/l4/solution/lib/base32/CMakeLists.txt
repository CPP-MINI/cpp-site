# Default static library definition
add_library(base32_static encoder.hpp decoder.hpp encoder.cpp decoder.cpp base32_def.hpp)

# Define a shared library which depends on the static version
add_library(base32 SHARED)
target_link_libraries(base32 PUBLIC base32_static)