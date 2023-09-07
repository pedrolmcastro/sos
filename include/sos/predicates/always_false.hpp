#ifndef SOS_PREDICATES_ALWAYS_FALSE_HPP
#define SOS_PREDICATES_ALWAYS_FALSE_HPP


#include <sos/traits/transparent.hpp>


namespace sos {
    struct always_false_t final : transparent {
        [[nodiscard]] constexpr bool operator()(auto&&) const noexcept {
            return false;
        }
    };

    inline constexpr always_false_t always_false{};
}


#endif
