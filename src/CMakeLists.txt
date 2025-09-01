file(GLOB MATH_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/slidr/math/*.hpp")
file(GLOB CONSTANTS_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/slidr/constants/*.hpp")
file(GLOB NODE_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/slidr/node/*.hpp")
file(GLOB SOLVER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/slidr/solver/*.hpp")
file(GLOB PROMPT_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/slidr/prompt/*.hpp")
file(GLOB CONTAINER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/slidr/container/*.hpp")

add_library(math_library INTERFACE)
add_library(constants_library INTERFACE)
add_library(node_library nodelib.cc ${NODE_HEADER_LIST})
add_library(solver_library INTERFACE)
add_library(prompt_library promptlib.cc ${PROMPT_HEADER_LIST})
add_library(container_library INTERFACE)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Test" OR CMAKE_BUILD_TYPE STREQUAL "Benchmark")
    target_compile_options(node_library PUBLIC -O3 -ffast-math -DNDEBUG)
    target_compile_options(prompt_library PUBLIC -O3 -ffast-math -DNDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_options(node_library PUBLIC -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -O0)
    target_compile_options(prompt_library PUBLIC -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -O0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(node_library PUBLIC -Wall -Wextra -pedantic -g3 -fsanitize=address,undefined)
    target_compile_options(prompt_library PUBLIC -Wall -Wextra -pedantic -g3 -fsanitize=address,undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "Gprof")
    target_compile_options(node_library PUBLIC -pg)
    target_compile_options(prompt_library PUBLIC -pg)
endif()

# Set linker flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_options(node_library PUBLIC -g3 -fsanitize=address,undefined)
    target_link_options(prompt_library PUBLIC -g3 -fsanitize=address,undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "Gprof")
    target_link_options(node_library PUBLIC -pg)
    target_link_options(prompt_library PUBLIC -pg)
endif()

target_include_directories(math_library INTERFACE ../slidr ${MATH_HEADER_LIST})
target_include_directories(constants_library INTERFACE ../slidr ${CONSTANTS_HEADER_LIST})
target_include_directories(node_library PUBLIC ../slidr ${NODE_HEADER_LIST})
target_include_directories(solver_library INTERFACE ../slidr ${SOLVER_HEADER_LIST})
target_include_directories(prompt_library PUBLIC ../slidr)
target_include_directories(container_library INTERFACE ../slidr ${CONTAINER_HEADER_LIST})

# target_link_libraries(math_library INTERFACE Boost::boost) # if you want to use boost::hash_combine
target_link_libraries(node_library PUBLIC math_library fmt::fmt)
target_link_libraries(solver_library INTERFACE node_library container_library)

target_compile_features(math_library INTERFACE cxx_std_20)  # requires C++20 for concept
target_compile_features(prompt_library PUBLIC cxx_std_20)   # requires C++20 for std::span
target_compile_features(node_library PUBLIC cxx_std_20)   # requires C++20 for std::span
target_compile_features(container_library INTERFACE cxx_std_20)  # requires C++20 for concepts & constexpr if
