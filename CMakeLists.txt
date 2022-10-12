cmake_minimum_required(VERSION 3.20)
project(Dripleaf)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libuv)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libuv/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libdeflate)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libdeflate)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/openssl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/openssl/include)

file(GLOB_RECURSE DRIPLEAF_SOURCES src/*.cpp)
add_executable(Dripleaf ${DRIPLEAF_SOURCES})
target_link_libraries(Dripleaf ssl crypto glad glfw uv_a libdeflate_static)

find_package(Python COMPONENTS Interpreter)

add_custom_target(
        check_license
        COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/check_license.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Checking license...")
add_dependencies(Dripleaf check_license)