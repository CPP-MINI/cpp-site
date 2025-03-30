# Default static library definition
add_library(base32_static)
target_sources(
        base32_static
        PUBLIC encoder.hpp decoder.hpp
        PRIVATE encoder.cpp decoder.cpp
)

# Define a shared library which depends on the static version
add_library(base32 SHARED)
target_link_libraries(base32 PUBLIC base32_static)