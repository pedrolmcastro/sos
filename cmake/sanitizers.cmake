# Based on https://github.com/cpp-best-practices/cmake_template/blob/main/cmake/Sanitizers.cmake


function(sos_enable_sanitizers)
    set(OPTIONS SANITIZE_LEAK SANITIZE_MEMORY SANITIZE_THREAD SANITIZE_ADDRESS SANITIZE_UNDEFINED)
    cmake_parse_arguments(SOS "${OPTIONS}" "TARGET" "" ${ARGN})

    if(NOT SOS_TARGET)
        message(FATAL_ERROR "Missing target")
    endif()

    if(
        NOT SOS_SANITIZE_LEAK
        AND NOT SOS_SANITIZE_MEMORY
        AND NOT SOS_SANITIZE_THREAD
        AND NOT SOS_SANITIZE_ADDRESS
        AND NOT SOS_SANITIZE_UNDEFINED
    )
        message(FATAL_ERROR "No sanitizers specified")
    endif()

    if(SOS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Invalid arguments: ${SOS_UNPARSED_ARGUMENTS}")
    endif()


    if(MSVC)
        if(SOS_SANITIZE_LEAK)
            message(AUTHOR_WARNING "Leak sanitizer isn't supported on MSVC")
        endif()

        if(SOS_SANITIZE_MEMORY)
            message(AUTHOR_WARNING "Memory sanitizer isn't supported on MSVC")
        endif()

        if(SOS_SANITIZE_THREAD)
            message(AUTHOR_WARNING "Thread sanitizer isn't supported on MSVC")
        endif()

        if(SOS_SANITIZE_ADDRESS)
            target_compile_options(${SOS_TARGET} PRIVATE /fsanitize=address /Zi /INCREMENTAL:NO)
            target_link_options(${SOS_TARGET} PRIVATE /INCREMENTAL:NO)
        endif()

        if(SOS_SANITIZE_UNDEFINED)
            message(AUTHOR_WARNING "Undefined behavior sanitizer isn't supported on MSVC")
        endif()

    elseif(
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
        CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM"
    )
        set(SANITIZERS "")

        if(SOS_SANITIZE_LEAK)
            if(WIN32)
                message(AUTHOR_WARNING "Leak sanitizer isn't supported on Windows")
            else()
                list(APPEND SANITIZERS "leak")
            endif()
        endif()

        if(SOS_SANITIZE_MEMORY)
            if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                message(AUTHOR_WARNING "Memory sanitizer isn't supported on GCC")
            elseif(WIN32)
                message(AUTHOR_WARNING "Memory sanitizer isn't supported on Windows")
            elseif(SOS_SANITIZE_LEAK)
                message(AUTHOR_WARNING "Memory sanitizer is incompatible with leak sanitizer")
            elseif(SOS_SANITIZE_THREAD)
                message(AUTHOR_WARNING "Memory sanitizer is incompatible with thread sanitizer")
            elseif(SOS_SANITIZE_ADDRESS)
                message(AUTHOR_WARNING "Memory sanitizer is incompatible with address sanitizer")
            else()
                list(APPEND SANITIZERS "memory")
            endif()
        endif()

        if(SOS_SANITIZE_THREAD)
            if(WIN32)
                message(AUTHOR_WARNING "Thread sanitizer isn't supported on Windows")
            elseif(SOS_SANITIZE_LEAK)
                message(AUTHOR_WARNING "Thread sanitizer is incompatible with leak sanitizer")
            elseif(SOS_SANITIZE_MEMORY)
                message(AUTHOR_WARNING "Thread sanitizer is incompatible with memory sanitizer")
            elseif(SOS_SANITIZE_ADDRESS)
                message(AUTHOR_WARNING "Thread sanitizer is incompatible with address sanitizer")
            else()
                list(APPEND SANITIZERS "thread")
            endif()
        endif()

        if(SOS_SANITIZE_ADDRESS)
            list(APPEND SANITIZERS "address")
        endif()

        if(SOS_SANITIZE_UNDEFINED)
            list(APPEND SANITIZERS "undefined")
        endif()

        list(JOIN SANITIZERS "," SANITIZERS)

        if(SANITIZERS)
            target_compile_options(${SOS_TARGET} PRIVATE -fsanitize=${SANITIZERS})
            target_link_options(${SOS_TARGET} PRIVATE -fsanitize=${SANITIZERS})
        endif()

    else()
        message(AUTHOR_WARNING "Compiler not supported: ${CMAKE_CXX_COMPILER_ID}")
    endif()
endfunction()
