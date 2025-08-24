add_executable(app app.cc)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Test" OR CMAKE_BUILD_TYPE STREQUAL "Benchmark")
    target_compile_options(app PUBLIC -O3 -ffast-math -DNDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_options(app PUBLIC -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -O0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(app PUBLIC -Wall -Wextra -pedantic -g3 -fsanitize=address,undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "Gprof")
    target_compile_options(app PUBLIC -pg)
endif()

# Set linker flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_options(app PUBLIC -g3 -fsanitize=address,undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "Gprof")
    target_link_options(app PUBLIC -pg)
endif()

# Link required libraries
target_link_libraries(app PRIVATE solver_library prompt_library)
