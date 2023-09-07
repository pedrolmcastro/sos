#ifndef SOS_PREDICATES_HAS_VALUE_HPP
#define SOS_PREDICATES_HAS_VALUE_HPP


#include <utility>

#include <sos/traits/transparent.hpp>
#include <sos/predicates/bool_cast.hpp>


namespace sos {
    template<class Holder>
    concept has_value_testable = requires(Holder&& holder) {
        { std::forward<Holder>(holder).has_value() } -> bool_castable;
    };

    template<class Holder>
    concept nothrow_has_value_testable = (
        has_value_testable<Holder> and
        requires(Holder&& holder) {
            { std::forward<Holder>(holder).has_value() } noexcept -> nothrow_bool_castable;
        }
    );


    struct has_value_t final : transparent {
        template<has_value_testable Holder>
        [[nodiscard]] constexpr bool operator()(Holder&& holder) const
            noexcept(nothrow_has_value_testable<Holder>)
        {
            return bool_cast(std::forward<Holder>(holder).has_value());
        }
    };

    inline constexpr has_value_t has_value{};
}


#endif
