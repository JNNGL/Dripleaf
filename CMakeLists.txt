cmake_minimum_required(VERSION 3.20)
project(Dripleaf)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE DRIPLEAF_SOURCES src/*.cpp)

add_executable(Dripleaf ${DRIPLEAF_SOURCES})

find_package(Python COMPONENTS Interpreter)

add_custom_target(
        check_license
        COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/check_license.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Checking license...")
add_dependencies(Dripleaf check_license)