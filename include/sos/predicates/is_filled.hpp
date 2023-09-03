#ifndef SOS_PREDICATES_IS_FILLED_HPP
#define SOS_PREDICATES_IS_FILLED_HPP


#include <sos/traits/transparent.hpp>
#include <sos/predicates/is_empty.hpp>


namespace sos {
    struct is_filled_t final : transparent {
        template<empty_testable Tested>
            [[nodiscard]] constexpr bool operator()(Tested&& tested) const
            noexcept(nothrow_empty_testable<Tested>)
        {
            return not is_empty(tested);
        }
    };

    inline constexpr is_filled_t is_filled{};
}


#endif
