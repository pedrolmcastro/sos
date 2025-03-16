# From https://github.com/pedrolmcastro/cppmake

function(cppmake_enable_warnings)
    cmake_parse_arguments(CPPMAKE "AS_ERRORS" "TARGET" "" ${ARGN})

    if(NOT CPPMAKE_TARGET)
        message(FATAL_ERROR "Missing target")
    endif()

    if(CPPMAKE_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Invalid arguments: ${CPPMAKE_UNPARSED_ARGUMENTS}")
    endif()

    set(OPTIONS "")
    set(WARNINGS "")

    if(MSVC)
        if("${CMAKE_CXX_FLAGS}" MATCHES "/W3")
            message(
                STATUS
                "Removing /W3 compiler option added by CMake: CMP0092"
            )
            string(REGEX REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1700) # 2012 - 11.
            list(APPEND WARNINGS
                4302
                4311
                4431
            )
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1900) # 2015 - 14.
            list(APPEND WARNINGS
                4062
                4165
                4242
                4254
                4263
                4265
                4287
                4289
                4296
                4355
                4365
                4435
                4437
                4536
                4545
                4546
                4547
                4548
                4549
                4555
                4557
                4574
                4577
                4598
                4599
                4605
                4619
                4640
                4643
                4654
                4774
                4777
                4822
                4826
                4841
                4866
                4868
                4905
                4906
                4928
                4946
                4987
                5022
                5023
                5024
                5025
                5026
                5027
                5029
                5031
                5032
            )
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1910) # 2017 - 15.
            list(APPEND WARNINGS
                5038
                5039
                5041
                5042
            )
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1920) # 2019 - 16.
            list(APPEND WARNINGS
                5052
                5214
                5215
                5216
                5217
                5219
                5220
                5240
            )
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1930) # 2022 - 17.
            list(APPEND WARNINGS
                5249
                5254
                5258
                5259
                5262
                5263
                5264
                5266
                5267
            )
        endif()

        list(APPEND OPTIONS /permissive- /W4)

        if(CPPMAKE_AS_ERRORS)
            set(LEVEL e)
        else()
            set(LEVEL 1)
        endif()

        list(TRANSFORM WARNINGS PREPEND /w${LEVEL})
        list(APPEND OPTIONS ${WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        list(APPEND WARNINGS
            cast-align
            cast-qual
            conversion
            disabled-optimization
            effc++
            format=2
            logical-op
            non-virtual-dtor
            old-style-cast
            overloaded-virtual
            redundant-decls
            shadow
            sign-conversion
            sign-promo
            switch-enum
        )

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 4.6)
            list(APPEND WARNINGS double-promotion)
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 4.8)
            list(APPEND WARNINGS useless-cast)
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 5)
            list(APPEND WARNINGS
                date-time
                suggest-final-methods
                suggest-final-types
                suggest-override
            )
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 6)
            list(APPEND WARNINGS
                duplicated-cond
                misleading-indentation
                multiple-inheritance
                null-dereference
            )
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 7)
            list(APPEND WARNINGS
                alloca
                duplicated-branches
            )
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8)
            list(APPEND WARNINGS
                extra-semi
                unsafe-loop-optimizations
            )
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 10)
            list(APPEND WARNINGS
                arith-conversion
                redundant-tags
            )
        endif()

        list(APPEND OPTIONS -pedantic -Wall -Wextra)

        if(CPPMAKE_AS_ERRORS)
            list(APPEND OPTIONS -Werror)
        endif()

        list(TRANSFORM WARNINGS PREPEND -W)
        list(APPEND OPTIONS ${WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        list(APPEND WARNINGS
            cast-align
            cast-qual
            conversion
            double-promotion
            format=2
            implicit-fallthrough
            non-virtual-dtor
            null-dereference
            old-style-cast
            overloaded-virtual
            shadow
            sign-conversion
            switch-enum
            unused
        )

        list(APPEND OPTIONS -pedantic -Wall -Wextra -Wno-unknown-warning-option)

        if(CPPMAKE_AS_ERRORS)
            list(APPEND OPTIONS -Werror)
        endif()

        list(TRANSFORM WARNINGS PREPEND -W)
        list(APPEND OPTIONS ${WARNINGS})
    else()
        message(AUTHOR_WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()

    if(OPTIONS)
        target_compile_options(
            ${CPPMAKE_TARGET}
            PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:${OPTIONS}>
        )
    endif()
endfunction()
