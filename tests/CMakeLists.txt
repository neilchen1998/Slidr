# Try to find Catch2 that is at least 3.8 but the same major version
find_package(Catch2 CONFIG 3.8...<4.0 QUIET)
if (Catch2_FOUND)
  message(STATUS "Found Catch2 version: ${Catch2_VERSION}")
else()
  message(STATUS "Catch2 could not be found or version is too old, downloading via FetchContent...")
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1)
  FetchContent_MakeAvailable(Catch2)
endif()

add_executable(mathtestlib mathtestlib.cc)
add_executable(constantstestlib constantstestlib.cc)
add_executable(nodetestlib nodetestlib.cc)
add_executable(solvertestlib solvertestlib.cc)
add_executable(prompttestlib prompttestlib.cc)
add_executable(containertestlib containertestlib.cc)
add_executable(creatortestlib creatortestlib.cc)

target_link_libraries(mathtestlib PRIVATE Catch2::Catch2WithMain math_library fmt::fmt)
target_link_libraries(constantstestlib PRIVATE Catch2::Catch2WithMain constants_library)
target_link_libraries(nodetestlib PRIVATE Catch2::Catch2WithMain node_library)
target_link_libraries(solvertestlib PRIVATE Catch2::Catch2WithMain solver_library)
target_link_libraries(prompttestlib PRIVATE Catch2::Catch2WithMain prompt_library)
target_link_libraries(containertestlib PRIVATE Catch2::Catch2WithMain container_library node_library)
target_link_libraries(creatortestlib PRIVATE Catch2::Catch2WithMain solver_library)

add_test(NAME mathtestlibtest COMMAND mathtestlib)
add_test(NAME constantstestlibtest COMMAND constantstestlib)
add_test(NAME nodetestlibtest COMMAND nodetestlib)
add_test(NAME solvertestlibtest COMMAND solvertestlib)
add_test(NAME prompttestlibtest COMMAND prompttestlib)
add_test(NAME containertestlibtest COMMAND containertestlib)
add_test(NAME creatortestlibtest COMMAND creatortestlib)
