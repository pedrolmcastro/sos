# From https://github.com/pedrolmcastro/cppmake


function(cppmake_sanitize)
    cmake_parse_arguments(CPPMAKE "ADDRESS;LEAK;MEMORY;SAFE_STACK;THREAD;UNDEFINED" "TARGET" "" ${ARGN})

    if(NOT CPPMAKE_TARGET)
        message(FATAL_ERROR "Missing target")
    endif()

    if(
        NOT CPPMAKE_ADDRESS
        AND NOT CPPMAKE_LEAK
        AND NOT CPPMAKE_MEMORY
        AND NOT CPPMAKE_SAFE_STACK
        AND NOT CPPMAKE_THREAD
        AND NOT CPPMAKE_UNDEFINED
    )
        message(FATAL_ERROR "No sanitizers specified")
    endif()

    if(CPPMAKE_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Invalid arguments: ${CPPMAKE_UNPARSED_ARGUMENTS}")
    endif()


    set(COMPILING "")
    set(LINKING "")

    if(MSVC)
        if(CPPMAKE_ADDRESS)
            list(APPEND COMPILING /fsanitize=address /Zi /INCREMENTAL:NO)
            list(APPEND LINKING /INCREMENTAL:NO)
        endif()

        if(CPPMAKE_LEAK)
            message(AUTHOR_WARNING "Leak sanitizer isn't supported on MSVC")
        endif()

        if(CPPMAKE_MEMORY)
            message(AUTHOR_WARNING "Memory sanitizer isn't supported on MSVC")
        endif()

        if(CPPMAKE_SAFE_STACK)
            message(AUTHOR_WARNING "Safe stack sanitizer isn't supported on MSVC")
        endif()

        if(CPPMAKE_THREAD)
            message(AUTHOR_WARNING "Thread sanitizer isn't supported on MSVC")
        endif()

        if(CPPMAKE_UNDEFINED)
            message(AUTHOR_WARNING "Undefined behavior sanitizer isn't supported on MSVC")
        endif()

    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|IntelLLVM")
        set(SANITIZERS "")

        if(CPPMAKE_ADDRESS)
            list(APPEND SANITIZERS "address")
        endif()

        if(CPPMAKE_LEAK)
            if(WIN32)
                message(AUTHOR_WARNING "Leak sanitizer isn't supported on Windows")
            else()
                list(APPEND SANITIZERS "leak")
            endif()
        endif()

        if(CPPMAKE_MEMORY)
            if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                message(AUTHOR_WARNING "Memory sanitizer isn't supported on GCC")
            elseif(WIN32)
                message(AUTHOR_WARNING "Memory sanitizer isn't supported on Windows")
            elseif(CPPMAKE_LEAK)
                message(AUTHOR_WARNING "Memory sanitizer is incompatible with leak sanitizer")
            elseif(CPPMAKE_THREAD)
                message(AUTHOR_WARNING "Memory sanitizer is incompatible with thread sanitizer")
            elseif(CPPMAKE_ADDRESS)
                message(AUTHOR_WARNING "Memory sanitizer is incompatible with address sanitizer")
            else()
                list(APPEND SANITIZERS "memory")
            endif()
        endif()

        if(CPPMAKE_SAFE_STACK)
            if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                message(AUTHOR_WARNING "Safe stack sanitizer isn't supported on GCC")
            elseif(CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
                message(AUTHOR_WARNING "Safe stack sanitizer isn't supported on ICC")
            else()
                list(APPEND SANITIZERS "safe-stack")
            endif()
        endif()

        if(CPPMAKE_THREAD)
            if(WIN32)
                message(AUTHOR_WARNING "Thread sanitizer isn't supported on Windows")
            elseif(CPPMAKE_LEAK)
                message(AUTHOR_WARNING "Thread sanitizer is incompatible with leak sanitizer")
            elseif(CPPMAKE_MEMORY)
                message(AUTHOR_WARNING "Thread sanitizer is incompatible with memory sanitizer")
            elseif(CPPMAKE_ADDRESS)
                message(AUTHOR_WARNING "Thread sanitizer is incompatible with address sanitizer")
            else()
                list(APPEND SANITIZERS "thread")
            endif()
        endif()

        if(CPPMAKE_UNDEFINED)
            list(APPEND SANITIZERS "undefined")
        endif()

        list(JOIN SANITIZERS "," SANITIZERS)

        if(SANITIZERS)
            list(APPEND COMPILING -fsanitize=${SANITIZERS})
            list(APPEND LINKING -fsanitize=${SANITIZERS})
        endif()

    else()
        message(AUTHOR_WARNING "Compiler not supported: ${CMAKE_CXX_COMPILER_ID}")

    endif()

    if(COMPILING AND LINKING)
        target_compile_options(${CPPMAKE_TARGET} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${COMPILING}>)
        target_link_options(${CPPMAKE_TARGET} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${LINKING}>)
    endif()
endfunction()
