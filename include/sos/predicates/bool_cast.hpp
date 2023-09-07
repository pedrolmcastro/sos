#ifndef SOS_PREDICATES_BOOL_CAST_HPP
#define SOS_PREDICATES_BOOL_CAST_HPP


#include <utility>

#include <sos/traits/transparent.hpp>


namespace sos {
    template<class From>
    concept bool_castable = requires(From&& from) {
        static_cast<bool>(std::forward<From>(from));
    };

    template<class From>
    concept nothrow_bool_castable = bool_castable<From> and requires(From&& from) {
        { static_cast<bool>(std::forward<From>(from)) } noexcept;
    };


    struct bool_cast_t final : transparent {
        template<bool_castable From>
        [[nodiscard]] constexpr bool operator()(From&& from) const
            noexcept(nothrow_bool_castable<From>)
        {
            return static_cast<bool>(std::forward<From>(from));
        }
    };

    inline constexpr bool_cast_t bool_cast{};
}


#endif
