FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)

add_executable(mathtestlib mathtestlib.cc)
add_executable(constantstestlib constantstestlib.cc)

target_compile_features(mathtestlib PRIVATE cxx_std_20)
target_compile_features(constantstestlib PRIVATE cxx_std_20)

target_link_libraries(mathtestlib PRIVATE Catch2::Catch2 math_library)
target_link_libraries(constantstestlib PRIVATE Catch2::Catch2 constants_library)

add_test(NAME mathtestlibtest COMMAND mathtestlib)
add_test(NAME constantstestlibtest COMMAND constantstestlib)
