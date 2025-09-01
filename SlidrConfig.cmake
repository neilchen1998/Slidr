install(EXPORT SlidrTargets
    FILE SlidrTargets.cmake
    NAMESPACE Slidr::
    DESTINATION lib/cmake/Slidr
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/SlidrConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SlidrConfig.cmake
    INSTALL_DESTINATION lib/cmake/Slidr
)
