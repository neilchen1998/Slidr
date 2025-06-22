FetchContent_Declare(
  nanobench
  GIT_REPOSITORY https://github.com/martinus/nanobench.git
  GIT_TAG v4.3.10)
FetchContent_MakeAvailable(nanobench)

add_executable(mathbenchlib mathbenchlib.cc)
add_executable(nodebenchlib nodebenchlib.cc)

target_compile_features(mathbenchlib PRIVATE cxx_std_20)
target_compile_features(nodebenchlib PRIVATE cxx_std_20)

target_link_libraries(mathbenchlib PRIVATE nanobench math_library Boost::boost)
target_link_libraries(nodebenchlib PRIVATE nanobench node_library)
