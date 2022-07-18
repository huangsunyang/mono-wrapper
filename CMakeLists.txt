cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 17)
project(mono-wrapper VERSION 0.1.0)

add_subdirectory(src "${PROJECT_SOURCE_DIR}/src/build")
add_subdirectory(dll "${PROJECT_SOURCE_DIR}/dll/build")
add_subdirectory(test "${PROJECT_SOURCE_DIR}/test/build")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
