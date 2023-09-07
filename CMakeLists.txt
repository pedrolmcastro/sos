cmake_minimum_required(VERSION 3.12)

project(
    sos
    VERSION 0.4.1
    DESCRIPTION "C++ header-only library to automate runtime checks using the type system"
    HOMEPAGE_URL "https://github.com/pedrolmcastro/sos"
    LANGUAGES CXX
)

message(STATUS "Generating sos ${PROJECT_VERSION}")


# Library

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)


# Tests

option(SOS_BUILD_TESTS "Build tests" OFF)

if(SOS_BUILD_TESTS)
    add_subdirectory(tests)
endif()
