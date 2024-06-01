FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)

add_executable(mathtestlib mathtestlib.cc)
add_executable(patterntestlib patterntestlib.cc)
add_executable(constantstestlib constantstestlib.cc)
add_executable(nodetestlib nodetestlib.cc)
add_executable(solvertestlib solvertestlib.cc)
add_executable(terminaltestlib terminaltestlib.cc)

target_compile_features(mathtestlib PRIVATE cxx_std_20)
target_compile_features(patterntestlib PRIVATE cxx_std_20)
target_compile_features(constantstestlib PRIVATE cxx_std_20)
target_compile_features(nodetestlib PRIVATE cxx_std_20)
target_compile_features(solvertestlib PRIVATE cxx_std_20)
target_compile_features(terminaltestlib PRIVATE cxx_std_17)

target_link_libraries(mathtestlib PRIVATE Catch2::Catch2 math_library)
target_link_libraries(patterntestlib PRIVATE Catch2::Catch2 pattern_library)
target_link_libraries(constantstestlib PRIVATE Catch2::Catch2 constants_library)
target_link_libraries(nodetestlib PRIVATE Catch2::Catch2 node_library)
target_link_libraries(solvertestlib PRIVATE Catch2::Catch2 math_library solver_library)
target_link_libraries(terminaltestlib PRIVATE Catch2::Catch2 terminal_library)

add_test(NAME mathtestlibtest COMMAND mathtestlib)
add_test(NAME patterntestlibtest COMMAND patterntestlib)
add_test(NAME constantstestlibtest COMMAND constantstestlib)
add_test(NAME nodetestlibtest COMMAND nodetestlib)
add_test(NAME solvertestlibtest COMMAND solvertestlib)
add_test(NAME terminaltestlibtest COMMAND terminaltestlib)
