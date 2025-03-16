cmake_minimum_required(VERSION 3.15)

project(sos_tests CXX)
message(STATUS "Generating sos tests")

include(CTest)
include(../cmake/sanitize.cmake)
include(../cmake/warnings.cmake)

if(NOT TARGET sos)
    find_package(sos REQUIRED)
endif()

file(
    GLOB_RECURSE
    SOS_TEST_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

foreach(SOS_TEST_SOURCE ${SOS_TEST_SOURCES})
    get_filename_component(SOS_TEST ${SOS_TEST_SOURCE} NAME_WLE)

    add_executable(${SOS_TEST} ${SOS_TEST_SOURCE})
    target_link_libraries(${SOS_TEST} PRIVATE sos::sos)

    cppmake_enable_warnings(TARGET ${SOS_TEST} AS_ERRORS)

    if(MSVC)
        cppmake_sanitize(TARGET ${SOS_TEST} ADDRESS)
    elseif(
        CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
    )
        cppmake_sanitize(TARGET ${SOS_TEST} ADDRESS LEAK UNDEFINED_BEHAVIOR)
    endif()

    add_test(NAME ${SOS_TEST} COMMAND ${SOS_TEST})
endforeach()
