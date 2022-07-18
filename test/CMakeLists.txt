file(GLOB_RECURSE all_cpp_files *.cpp)
add_executable(test-link-dll ${all_cpp_files})

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(test-link-dll PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

target_link_libraries(test-link-dll PUBLIC dll)

# move dll to output folder
# cmake should die!
add_custom_command(TARGET test-link-dll POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:dll>
    $<TARGET_FILE_DIR:test-link-dll>
)
