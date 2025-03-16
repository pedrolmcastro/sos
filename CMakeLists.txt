cmake_minimum_required(VERSION 3.15)

project(
    sos
    VERSION 0.6.0
    DESCRIPTION "C++ 20 header-only contracts library based on P2900"
    HOMEPAGE_URL "https://github.com/pedrolmcastro/sos"
    LANGUAGES CXX
)

message(STATUS "Generating sos ${PROJECT_VERSION}")

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

if(MSVC)
    set(SOS_COMPILE_OPTIONS /w14996)
elseif(
    CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
)
    set(
        SOS_COMPILE_OPTIONS
        -Wdeprecated-declarations
        -Wno-error=deprecated-declarations
    )
else()
    message(AUTHOR_WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

target_compile_options(${PROJECT_NAME} INTERFACE ${SOS_COMPILE_OPTIONS})

option(SOS_BUILD_TESTS "Build SOS tests" OFF)

if(SOS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
