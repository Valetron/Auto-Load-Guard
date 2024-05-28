if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "Create separate directory for build.")
endif()

cmake_minimum_required(VERSION 3.10)
project(Auto-Load-Guard LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(ProjectSettings)
include_directories(logic/guardian/)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.hpp")

message(STATUS "====== ${HEADERS}")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})
