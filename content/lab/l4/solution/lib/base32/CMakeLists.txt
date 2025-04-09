# Define common source list for both targets
set(BASE32_SOURCES encoder.hpp decoder.hpp encoder.cpp decoder.cpp base32_def.hpp)

# Default static library definition
add_library(base32_static ${BASE32_SOURCES})

# Define a shared library
add_library(base32 SHARED ${BASE32_SOURCES})