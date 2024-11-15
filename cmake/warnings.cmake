# From https://github.com/pedrolmcastro/cppmake


function(cppmake_enable_warnings)
    cmake_parse_arguments(CPPMAKE "AS_ERRORS" "TARGET" "" ${ARGN})

    if(NOT CPPMAKE_TARGET)
        message(FATAL_ERROR "Missing target")
    endif()

    if(CPPMAKE_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Invalid arguments: ${CPPMAKE_UNPARSED_ARGUMENTS}")
    endif()


    set(WARNINGS "")

    if(MSVC)
        if("${CMAKE_CXX_FLAGS}" MATCHES "/W3")
            message(STATUS "Removing /W3 compiler option added by default by CMake: CMP0092")
            string(REGEX REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        endif()

        list(APPEND WARNINGS /W4 /permissive-)

        if(CPPMAKE_AS_ERRORS)
            list(APPEND WARNINGS /WX)
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1700) # 2012 - 11.
            list(APPEND WARNINGS
                /w44431 # Missing type specifier
                /w24302 # Truncating conversions
                /w44311 # Truncating pointer conversions
            )
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1900) # 2015 - 14.
            list(APPEND WARNINGS
                /w44062 # Missing enumerator on switch
                /w14165 # Conversion from HRESULT to bool
                /w44242 # Conversion with type mismatch
                /w44254 # Larger bitfield assigned to a smaller one
                /w44263 # Member function overload is not an override
                /w34265 # Missing virtual destructor
                /w34287 # Unsigned variable operated with negative number
                /w44289 # Variable declared in a for-loop used outside the scope
                /w44296 # Unsigned compared with zero
                /w14355 # Use of this in member initializer list
                /w44365 # Conversion with sign mismatch
                /w44435 # Object layout with virtual base changes is inconsistent
                /w44437 # A dynamic_cast from virtual base can fail
                /w44536 # Type name exceeds the meta-data limit of characters
                /w14545 # Missing arguments to function expression before comma
                /w14546 # Missing arguments to function before comma
                /w14547 # Operator before comma without side-effect
                /w14548 # Expression before comma without side-effect
                /w14549 # Operator before comma without side-effect
                /w14555 # Expression without side-effect
                /w34557 # Use of __assume with side-effect
                /w44574 # Use of #ifndef istead of #if
                /w14577 # Use of noexcept with no exception handling mode specified
                /w14598 # Precompiled header number mismatch
                /w34599 # Precompiled header command line arguments number mismatch
                /w14605 # Precompiled header defined macro mismatch
                /w34619 # Invalid #pragma warning number
                /w34640 # Local static object is not thread-safe
                /w44643 # Prohibited forward declaring of identifier in namespace std
                /w44654 # Ignored code before include of precompiled header
                /w44774 # Format string is not a string literal
                /w44777 # Format string checking
                /w14822 # Missing local class member function body
                /w24826 # Sign-extended conversion
                /w44841 # Compound member designator used in offsetof
                /w44866 # Compiler may not enforce left-to-right evaluation order for call to operator
                /w44868 # Compiler may not enforce left-to-right evaluation order in braced initialization list
                /w14905 # Wide string literal cast to LPSTR
                /w14906 # String literal cast to LPWSTR
                /w14928 # Multiple user-defined conversions implicitly applied
                /w14946 # Use of reinterpret_cast between related classes
                /w44987 # Use of throw (...) specifier
                /w15022 # Multiple move constructors
                /w15023 # Multiple move assignment operators
                /w45024 # Move constructor implicitly defined as deleted
                /w45025 # Move assigment implicitly defined as deleted
                /w15026 # Move constructor implicitly defined as deleted
                /w15027 # Move assigment implicitly defined as deleted
                /w45029 # Alignment attribute applyed to something other than variables, data members or tag types
                /w45031 # Popping state from other file with #pragma warning(pop)
                /w45032 # Missing #pragma warning(pop)
            )
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1910) # 2017 - 15.
            list(APPEND WARNINGS
                /w45038 # Member initializer list order different from declaration
                /w45039 # Throwing function passed to extern C
                /w45041 # Out-of-line constexpr static data member
                /w45042 # Inline function declaration at block scope
            )
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1920) # 2019 - 16.
            list(APPEND WARNINGS
                /w35052 # Keyword used in a C++ version prior to when it was introduced
                /w45214 # Invalid keyword to an operand with a volatile type
                /w45215 # Volatile parameter
                /w45216 # Volatile return
                /w45217 # Volatile structured binding
                /w25219 # Conversion with type mismatch
                /w45220 # Non-static volatile data member doesn't imply non trivial compiler generated members
                /w45240 # Invalid attribute position
            )
        endif()

        if(MSVC_VERSION VERSION_GREATER_EQUAL 1930) # 2022 - 17.
            list(APPEND WARNINGS
                /w15249 # Non representable enumerator value
                /w45254 # Invalid terse static_assert
                /w45258 # Unnecessary explicit capture
                /w45259 # Missing template<> in explicit specialization
                /w15262 # Implicit fall-through
                /w45263 # Prevented copy elision by calling std::move
                /w45264 # Unused const variable
                /w45266 # Const return
                /w45267 # Deprecated implicit copy constructor/assignment given any user-provided
            )
        endif()

    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        list(APPEND WARNINGS -Wall -Wextra -pedantic)

        if(CPPMAKE_AS_ERRORS)
            list(APPEND WARNINGS -Werror)
        endif()

        list(APPEND WARNINGS
            -Weffc++                # Scott Meyers’ Effective C++
            -Wshadow                # Name shadowing
            -Wformat=2              # Format string checking
            -Wcast-qual             # Removed qualifier in pointer cast
            -Wcast-align            # Pointer cast with increased target alignment
            -Wconversion            # Implicit conversion
            -Wlogical-op            # Suspicious logical operations
            -Wsign-promo            # Conversion from unsigned to signed
            -Wswitch-enum           # Missing enumerator on switch
            -Wold-style-cast        # Use of C-style cast
            -Wredundant-decls       # Redundant declarations
            -Wsign-conversion       # Conversion with sign mismatch
            -Wnon-virtual-dtor      # Missing virtual destructor
            -Woverloaded-virtual    # Member function overload is not an override
            -Wdisabled-optimization # Failed to optimize
        )

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 4.6)
            list(APPEND WARNINGS -Wdouble-promotion) # Implicit floating-point promotion
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 4.8)
            list(APPEND WARNINGS -Wuseless-cast) # Useless cast
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 5)
            list(APPEND WARNINGS
                -Wdate-time             # Use of __TIME__, __DATE__ or __TIMESTAMP__
                -Wsuggest-override      # Suggest override on virtual member function
                -Wsuggest-final-types   # Suggest final on types
                -Wsuggest-final-methods # Suggest final on virtual member function
            )
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 6)
            list(APPEND WARNINGS
                -Wduplicated-cond        # Duplicated condition in if-else-if chain
                -Wnull-dereference       # Dereferencing a null pointer
                -Wmultiple-inheritance   # Use of multiple inheritance
                -Wmisleading-indentation # Indentation doesn't match block structure
            )
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 7)
            list(APPEND WARNINGS
                -Walloca              # Use of alloca
                -Wduplicated-branches # Duplicated branch in if-else chain
            )
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8)
            list(APPEND WARNINGS
                -Wextra-semi                # Redundant semicolons
                -Wunsafe-loop-optimizations # Failed to optimize loop
            )
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 10)
            list(APPEND WARNINGS
                -Warith-conversion # Implicit conversion in arithmetic operations
                -Wredundant-tags   # Redundant class-key or enum-key
            )
        endif()

    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        list(APPEND WARNINGS -Wall -Wextra -pedantic -Wno-unknown-warning-option)

        if(CPPMAKE_AS_ERRORS)
            list(APPEND WARNINGS -Werror)
        endif()

        list(APPEND WARNINGS
            -Wshadow               # Name shadowing
            -Wunused               # Unused constructs
            -Wformat=2             # Format string checking
            -Wcast-qual            # Removed qualifier in pointer cast
            -Wcast-align           # Pointer cast with increased target alignment
            -Wconversion           # Implicit conversion
            -Wswitch-enum          # Missing enumerator on switch
            -Wold-style-cast       # Use of C-style cast
            -Wsign-conversion      # Conversion with sign mismatch
            -Wdouble-promotion     # Implicit floating-point promotion
            -Wnon-virtual-dtor     # Missing virtual destructor
            -Wnull-dereference     # Dereferencing a null pointer
            -Woverloaded-virtual   # Member function overload is not an override
            -Wimplicit-fallthrough # Implicit fall-through
        )

    else()
        # TODO: Support Intel compiler
        message(AUTHOR_WARNING "Compiler not supported: ${CMAKE_CXX_COMPILER_ID}")

    endif()

    if(WARNINGS)
        target_compile_options(${CPPMAKE_TARGET} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${WARNINGS}>)
    endif()
endfunction()
