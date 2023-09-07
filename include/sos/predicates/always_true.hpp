#ifndef SOS_PREDICATES_ALWAYS_TRUE_HPP
#define SOS_PREDICATES_ALWAYS_TRUE_HPP


#include <sos/traits/transparent.hpp>


namespace sos {
    struct always_true_t final : transparent {
        [[nodiscard]] constexpr bool operator()(auto&&) const noexcept {
            return true;
        }
    };

    inline constexpr always_true_t always_true{};
}


#endif
