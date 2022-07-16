cmake_minimum_required(VERSION 3.0.0)

macro (global_config)
    set(CMAKE_VERBOSE_MAKEFILE on)
    set(CMAKE_CXX_STANDARD 17)
    project(mono-wrapper VERSION 0.1.0)
endmacro()

macro (test_config)
    include(CTest)
    enable_testing()
endmacro()

macro (mono_wrapper_config)
    file(GLOB_RECURSE all_cpp_files src/*.cpp)
    add_executable(mono-wrapper ${all_cpp_files})

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
endmacro()

macro (cpack_config)
    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
    include(CPack)
endmacro()

macro (main)
    global_config()
    mono_wrapper_config()
    test_config()
    cpack_config()
endmacro()

main()
