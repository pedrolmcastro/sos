cmake_minimum_required(VERSION 3.14)

project(sos_tests CXX)
message(STATUS "Generating sos tests")

include(CTest)


if(NOT TARGET sos)
    find_package(sos REQUIRED)
endif()


file(GLOB_RECURSE SOS_TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

foreach(SOS_TEST_SOURCE ${SOS_TEST_SOURCES})
    get_filename_component(SOS_TEST ${SOS_TEST_SOURCE} NAME_WLE)

    add_executable(${SOS_TEST} ${SOS_TEST_SOURCE})
    target_link_libraries(${SOS_TEST} PRIVATE sos::sos)

    target_include_directories(
        ${SOS_TEST} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

    # Enable warnings
    if(MSVC)
        target_compile_options(${SOS_TEST} PRIVATE /W4 /WX)
    else()
        target_compile_options(${SOS_TEST} PRIVATE -Werror -Wall -Wextra -pedantic)
    endif()

    add_test(NAME ${SOS_TEST} COMMAND ${SOS_TEST})
endforeach()
