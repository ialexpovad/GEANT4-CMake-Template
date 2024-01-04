cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(ORIGINAL_PROJECT_NAME "CMakeGEANT4Template")
project(tests LANGUAGES CXX)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} ${ORIGINAL_PROJECT_NAME}::${ORIGINAL_PROJECT_NAME})

# Add a test to the project to be run by ctest.
# See https://cmake.org/cmake/help/latest/command/add_test.html
# See https://cmake.org/cmake/help/latest/manual/ctest.1.html
# COMMAND tag specifies the test command-line. If it is an executable target
# created by add_executable(), it will automatically be replaced by the location
# of the executable created at build time.
add_test(NAME ${PROJECT_NAME}
         COMMAND ${PROJECT_NAME}
         WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)