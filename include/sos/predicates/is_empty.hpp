#ifndef SOS_PREDICATES_IS_EMPTY_HPP
#define SOS_PREDICATES_IS_EMPTY_HPP


#include <ranges>
#include <utility>

#include <sos/traits/transparent.hpp>


namespace sos {
    template<class Tested>
    concept empty_testable = requires(Tested&& tested) {
        std::ranges::empty(std::forward<Tested>(tested));
    };

    template<class Tested>
    concept nothrow_empty_testable = empty_testable<Tested> and requires(Tested&& tested) {
        { std::ranges::empty(std::forward<Tested>(tested)) } noexcept;
    };


    struct is_empty_t final : transparent {
        template<empty_testable Tested>
            [[nodiscard]] constexpr bool operator()(Tested&& tested) const
            noexcept(nothrow_empty_testable<Tested>)
        {
            return std::ranges::empty(std::forward<Tested>(tested));
        }
    };

    inline constexpr is_empty_t is_empty{};
}


#endif
