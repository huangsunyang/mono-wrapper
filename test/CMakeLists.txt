file(GLOB_RECURSE all_cpp_files *.cpp)
add_executable(test-link-dll ${all_cpp_files})

find_package(Catch2 REQUIRED)
target_link_libraries(test-link-dll PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
target_link_libraries(test-link-dll PRIVATE dll)
target_link_libraries(test-link-dll PRIVATE mono-wrapper)


# move dll to output folder
# cmake should die!
add_custom_command(TARGET test-link-dll POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:dll>
    $<TARGET_FILE:csharp-script>
    $<TARGET_FILE_DIR:test-link-dll>
)


set(VCPKG_INSTALL_ROOT ${CMAKE_TOOLCHAIN_FILE}/../../../installed)
set(CATCH_SRC_DIR ${VCPKG_INSTALL_ROOT}/${VCPKG_TARGET_TRIPLET}/Catch2)
list(APPEND CMAKE_MODULE_PATH ${CATCH_SRC_DIR})
include(Catch)
catch_discover_tests(test-link-dll)

