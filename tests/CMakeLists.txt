FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)

add_executable(mathtestlib mathtestlib.cc)
add_executable(constantstestlib constantstestlib.cc)
add_executable(nodetestlib nodetestlib.cc)
add_executable(solvertestlib solvertestlib.cc)
add_executable(prompttestlib prompttestlib.cc)

target_compile_features(mathtestlib PRIVATE cxx_std_20)
target_compile_features(constantstestlib PRIVATE cxx_std_20)
target_compile_features(nodetestlib PRIVATE cxx_std_20)
target_compile_features(solvertestlib PRIVATE cxx_std_20)
target_compile_features(prompttestlib PRIVATE cxx_std_20)

target_link_libraries(mathtestlib PRIVATE Catch2::Catch2 math_library)
target_link_libraries(constantstestlib PRIVATE Catch2::Catch2 constants_library)
target_link_libraries(nodetestlib PRIVATE Catch2::Catch2 node_library)
target_link_libraries(solvertestlib PRIVATE Catch2::Catch2 solver_library)
target_link_libraries(prompttestlib PRIVATE Catch2::Catch2 prompt_library)

add_test(NAME mathtestlibtest COMMAND mathtestlib)
add_test(NAME constantstestlibtest COMMAND constantstestlib)
add_test(NAME nodetestlibtest COMMAND nodetestlib)
add_test(NAME solvertestlibtest COMMAND solvertestlib)
add_test(NAME prompttestlibtest COMMAND prompttestlib)
