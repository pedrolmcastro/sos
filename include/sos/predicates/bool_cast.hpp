#ifndef SOS_PREDICATES_BOOL_CAST_HPP
#define SOS_PREDICATES_BOOL_CAST_HPP


#include <utility>
#include <type_traits>

#include "sos/predicates/negation.hpp"

#include "sos/traits/make_transparent.hpp"


namespace sos::predicates {
    // Transparent function object performing a static cast to bool
    struct bool_cast_t final : traits::make_transparent {
        // Todo: Use static operator() in C++23
        template<class From> [[nodiscard]] constexpr bool operator()(From&& from) const
            noexcept(std::is_nothrow_constructible_v<bool, From&&>)
            requires(std::is_constructible_v<bool, From&&>)
        {
            return static_cast<bool>(std::forward<From>(from));
        }
    };

    inline constexpr bool_cast_t bool_cast;


    using not_bool_cast_t = negation<bool_cast_t>;
    inline constexpr not_bool_cast_t not_bool_cast;
}


#endif
