FetchContent_Declare(
  nanobench
  GIT_REPOSITORY https://github.com/martinus/nanobench.git
  GIT_TAG v4.3.10)
FetchContent_MakeAvailable(nanobench)

add_executable(mathbenchmark mathbenchmark.cc)
add_executable(nodebenchmark nodebenchmark.cc)

target_link_libraries(mathbenchmark PRIVATE nanobench math_library Boost::boost)
target_link_libraries(nodebenchmark PRIVATE nanobench node_library)
