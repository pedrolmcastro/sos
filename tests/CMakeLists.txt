cmake_minimum_required(VERSION 3.15)

project(sos_tests CXX)
message(STATUS "Generating sos tests")

include(CTest)
include(../cmake/warnings.cmake)


if(NOT TARGET sos)
    find_package(sos REQUIRED)
endif()


file(GLOB_RECURSE SOS_TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

foreach(SOS_TEST_SOURCE ${SOS_TEST_SOURCES})
    get_filename_component(SOS_TEST ${SOS_TEST_SOURCE} NAME_WLE)

    add_executable(${SOS_TEST} ${SOS_TEST_SOURCE})
    target_link_libraries(${SOS_TEST} PRIVATE sos::sos)

    sos_target_enable_warnings(${SOS_TEST})

    add_test(NAME ${SOS_TEST} COMMAND ${SOS_TEST})
endforeach()
