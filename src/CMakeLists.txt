file(GLOB MATH_HEADER_LIST CONFIGURE_DEPENDS "${8_PUZZLE_SOURCE_DIR}/include/math/*.hpp")
file(GLOB CONSTANTS_HEADER_LIST CONFIGURE_DEPENDS "${8_PUZZLE_SOURCE_DIR}/include/constants/*.hpp")
file(GLOB NODE_HEADER_LIST CONFIGURE_DEPENDS "${8_PUZZLE_SOURCE_DIR}/include/node/*.hpp")

add_library(math_library mathlib.cc ${MATH_HEADER_LIST})
add_library(constants_library constantslib.cc ${CONSTANTS_HEADER_LIST})
add_library(node_library nodelib.cc ${NODE_HEADER_LIST})

target_include_directories(math_library PUBLIC ../include)
target_include_directories(constants_library PUBLIC ../include)
target_include_directories(node_library PUBLIC ../include)

target_link_libraries(node_library PUBLIC math_library constants_library)

target_compile_features(math_library PUBLIC cxx_std_20)  # requires C++20 for concept
target_compile_features(constants_library PUBLIC cxx_std_20)
target_compile_features(node_library PUBLIC cxx_std_20)
