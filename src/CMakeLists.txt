file(GLOB_RECURSE all_cpp_files *.cpp)
add_library(mono-wrapper ${all_cpp_files})

message(WARNING ${all_cpp_files})

# include path
target_include_directories(mono-wrapper
    # mono include
    PUBLIC "${PROJECT_SOURCE_DIR}/third-party/mono/include"
)

# lib
target_link_libraries(mono-wrapper
    # mono dll lib, dll needs in same folder as exe
    PUBLIC "${PROJECT_SOURCE_DIR}/third-party/mono/lib/Release/mono-2.0-sgen.lib")

# set root folder as working directory
set_property(TARGET mono-wrapper
    PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# move dll to output folder
add_custom_command(TARGET mono-wrapper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/third-party/mono/bin/Release/mono-2.0-sgen.dll"
    "${PROJECT_SOURCE_DIR}/third-party/mono/bin/Release/mono-2.0-sgen.pdb"
    "${PROJECT_SOURCE_DIR}/script.dll"
    $<TARGET_FILE_DIR:mono-wrapper>
)

message(WARNING ${PROJECT_SOURCE_DIR})
