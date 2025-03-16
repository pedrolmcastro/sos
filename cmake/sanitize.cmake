# From https://github.com/pedrolmcastro/cppmake

function(cppmake_sanitize)
    cmake_parse_arguments(
        CPPMAKE
        "ADDRESS;LEAK;MEMORY;SAFE_STACK;THREAD;UNDEFINED_BEHAVIOR"
        "TARGET"
        ""
        ${ARGN}
    )

    if(NOT CPPMAKE_TARGET)
        message(FATAL_ERROR "Missing target")
    endif()

    if(
        NOT CPPMAKE_ADDRESS
        AND NOT CPPMAKE_LEAK
        AND NOT CPPMAKE_MEMORY
        AND NOT CPPMAKE_SAFE_STACK
        AND NOT CPPMAKE_THREAD
        AND NOT CPPMAKE_UNDEFINED_BEHAVIOR
    )
        message(FATAL_ERROR "No sanitizers specified")
    endif()

    if(CPPMAKE_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Invalid arguments: ${CPPMAKE_UNPARSED_ARGUMENTS}")
    endif()

    set(COMPILE_OPTIONS "")
    set(LINK_OPTIONS "")

    if(MSVC)
        if(CPPMAKE_ADDRESS)
            list(APPEND COMPILE_OPTIONS /fsanitize=address /Zi /INCREMENTAL:NO)
            list(APPEND LINK_OPTIONS /INCREMENTAL:NO)
        endif()

        if(CPPMAKE_LEAK)
            message(FATAL_ERROR "Leak sanitizer isn't supported on MSVC")
        endif()

        if(CPPMAKE_MEMORY)
            message(FATAL_ERROR "Memory sanitizer isn't supported on MSVC")
        endif()

        if(CPPMAKE_SAFE_STACK)
            message(
                FATAL_ERROR
                "Safe stack sanitizer isn't supported on MSVC"
            )
        endif()

        if(CPPMAKE_THREAD)
            message(FATAL_ERROR "Thread sanitizer isn't supported on MSVC")
        endif()

        if(CPPMAKE_UNDEFINED_BEHAVIOR)
            message(
                FATAL_ERROR
                "Undefined behavior sanitizer isn't supported on MSVC"
            )
        endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|IntelLLVM")
        set(SANITIZERS "")

        if(CPPMAKE_ADDRESS)
            list(APPEND SANITIZERS "address")
        endif()

        if(CPPMAKE_LEAK)
            if(WIN32)
                message(
                    FATAL_ERROR
                    "Leak sanitizer isn't supported on Windows"
                )
            else()
                list(APPEND SANITIZERS "leak")
            endif()
        endif()

        if(CPPMAKE_MEMORY)
            if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                message(
                    FATAL_ERROR
                    "Memory sanitizer isn't supported on GCC"
                )
            elseif(WIN32)
                message(
                    FATAL_ERROR
                    "Memory sanitizer isn't supported on Windows"
                )
            elseif(CPPMAKE_ADDRESS)
                message(
                    FATAL_ERROR
                    "Memory sanitizer is incompatible with address sanitizer"
                )
            elseif(CPPMAKE_LEAK)
                message(
                    FATAL_ERROR
                    "Memory sanitizer is incompatible with leak sanitizer"
                )
            else()
                list(APPEND SANITIZERS "memory")
            endif()
        endif()

        if(CPPMAKE_SAFE_STACK)
            if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                message(
                    FATAL_ERROR
                    "Safe stack sanitizer isn't supported on GCC"
                )
            elseif(CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
                message(
                    FATAL_ERROR
                    "Safe stack sanitizer isn't supported on ICC"
                )
            elseif(CPPMAKE_ADDRRESS)
                message(
                    FATAL_ERROR
                    "Safe stack sanitizer is incompatible with address sanitizer"
                )
            elseif(CPPMAKE_LEAK)
                message(
                    FATAL_ERROR
                    "Safe stack sanitizer is incompatible with leak sanitizer"
                )
            else()
                list(APPEND SANITIZERS "safe-stack")
            endif()
        endif()

        if(CPPMAKE_THREAD)
            if(WIN32)
                message(
                    FATAL_ERROR
                    "Thread sanitizer isn't supported on Windows"
                )
            elseif(CPPMAKE_ADDRESS)
                message(
                    FATAL_ERROR
                    "Thread sanitizer is incompatible with address sanitizer"
                )
            elseif(CPPMAKE_LEAK)
                message(
                    FATAL_ERROR
                    "Thread sanitizer is incompatible with leak sanitizer"
                )
            elseif(CPPMAKE_MEMORY)
                message(
                    FATAL_ERROR
                    "Thread sanitizer is incompatible with memory sanitizer"
                )
            else()
                list(APPEND SANITIZERS "thread")
            endif()
        endif()

        if(CPPMAKE_UNDEFINED_BEHAVIOR)
            list(APPEND SANITIZERS "undefined")
        endif()

        list(JOIN SANITIZERS "," SANITIZERS)

        if(SANITIZERS)
            list(APPEND COMPILE_OPTIONS -fsanitize=${SANITIZERS})
            list(APPEND LINK_OPTIONS -fsanitize=${SANITIZERS})
        endif()
    else()
        message(AUTHOR_WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()

    if(COMPILE_OPTIONS AND LINK_OPTIONS)
        target_compile_options(
            ${CPPMAKE_TARGET}
            PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:${COMPILE_OPTIONS}>
        )

        target_link_options(
            ${CPPMAKE_TARGET}
            PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:${LINK_OPTIONS}>
        )
    endif()
endfunction()
