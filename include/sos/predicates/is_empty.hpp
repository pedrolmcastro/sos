#ifndef SOS_PREDICATES_IS_EMPTY_HPP
#define SOS_PREDICATES_IS_EMPTY_HPP


#include <ranges>
#include <utility>

#include <sos/traits/transparent.hpp>
#include <sos/concepts/empty_testable.hpp>


namespace sos {
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
