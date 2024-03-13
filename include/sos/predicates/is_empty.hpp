#ifndef SOS_PREDICATES_IS_EMPTY_HPP
#define SOS_PREDICATES_IS_EMPTY_HPP


#include <ranges>
#include <type_traits>

#include "sos/predicates/negation.hpp"


namespace sos::predicates {
    using is_empty_t = std::remove_const_t<decltype(std::ranges::empty)>;
    inline constexpr is_empty_t is_empty;

    using is_not_empty_t = negation<is_empty_t>;
    inline constexpr is_not_empty_t is_not_empty;
}


#endif
