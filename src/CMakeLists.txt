file(GLOB MATH_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/math/*.hpp")
file(GLOB CONSTANTS_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/constants/*.hpp")
file(GLOB NODE_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/node/*.hpp")
file(GLOB SOLVER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/solver/*.hpp")
file(GLOB PROMPT_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/prompt/*.hpp")
file(GLOB CONTAINER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/container/*.hpp")
file(GLOB FILESYSTEM_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/filesystem/*.hpp")
file(GLOB GUI_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/gui/*.hpp")

add_library(math_library INTERFACE)
add_library(constants_library INTERFACE)
add_library(node_library nodelib.cc ${NODE_HEADER_LIST})
add_library(solver_library INTERFACE)
add_library(prompt_library promptlib.cc ${PROMPT_HEADER_LIST})
add_library(container_library INTERFACE)
add_library(fs_library saveloadlib.cc ${FILESYSTEM_HEADER_LIST})
add_library(gui_library screenlib.cc animationlib.cc ${GUI_HEADER_LIST})

target_include_directories(math_library INTERFACE ../include ${MATH_HEADER_LIST})
target_include_directories(constants_library INTERFACE ../include ${CONSTANTS_HEADER_LIST})
target_include_directories(node_library PUBLIC ../include)
target_include_directories(solver_library INTERFACE ../include ${SOLVER_HEADER_LIST})
target_include_directories(prompt_library PUBLIC ../include)
target_include_directories(container_library INTERFACE ../include ${CONTAINER_HEADER_LIST})
target_include_directories(fs_library PUBLIC ../include)
target_include_directories(gui_library PUBLIC ../include)

# target_link_libraries(math_library INTERFACE Boost::boost) # if you want to use boost::hash_combine
target_link_libraries(node_library PUBLIC math_library fmt::fmt)
target_link_libraries(solver_library INTERFACE node_library container_library)
target_link_libraries(fs_library PUBLIC nlohmann_json::nlohmann_json fmt::fmt)
target_link_libraries(gui_library PUBLIC raylib fs_library)

target_compile_features(constants_library INTERFACE cxx_std_17)  # requires C++17 for inline variables
target_compile_features(math_library INTERFACE cxx_std_20)  # requires C++20 for concept
target_compile_features(prompt_library PUBLIC cxx_std_20)   # requires C++20 for std::span
target_compile_features(container_library INTERFACE cxx_std_20)  # requires C++20 for concepts & constexpr if
target_compile_features(fs_library PUBLIC cxx_std_17)  # requires C++17 for std::filesystem
