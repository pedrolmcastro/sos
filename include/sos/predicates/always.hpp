#ifndef SOS_PREDICATES_ALWAYS_HPP
#define SOS_PREDICATES_ALWAYS_HPP


#include "sos/traits/make_transparent.hpp"


namespace sos::predicates {
    // Transparent function object always returning Value
    template<bool Value> struct always_t final : traits::make_transparent {
        static constexpr bool value = Value;

        [[nodiscard]] explicit constexpr operator bool() const noexcept {
            return value;
        }

        // Todo: Use static operator() in C++23
        [[nodiscard]] constexpr bool operator()(auto&&...) const noexcept {
            return value;
        }
    };


    using always_true_t = always_t<true>;
    inline constexpr always_true_t always_true;

    using always_false_t = always_t<false>;
    inline constexpr always_false_t always_false;
}


#endif
