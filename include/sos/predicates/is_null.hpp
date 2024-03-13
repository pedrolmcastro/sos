#ifndef SOS_PREDICATES_IS_NULL_HPP
#define SOS_PREDICATES_IS_NULL_HPP


#include <cstddef>
#include <utility>

#include "sos/concepts/equality_comparable_with.hpp"

#include "sos/predicates/negation.hpp"

#include "sos/traits/make_transparent.hpp"


namespace sos::predicates {
    // Transparent function object performing equality comparison with nullptr
    struct is_null_t final : traits::make_transparent {
        // Todo: Use static operator() in C++23
        template<detail::concepts::equality_comparable_with<std::nullptr_t> Compared>
        [[nodiscard]] constexpr decltype(auto) operator()(Compared&& compared) const
            noexcept(noexcept(std::forward<Compared>(compared) == nullptr))
        {
            return std::forward<Compared>(compared) == nullptr;
        }
    };

    inline constexpr is_null_t is_null;


    using is_not_null_t = negation<is_null_t>;
    inline constexpr is_not_null_t is_not_null;
}


#endif
