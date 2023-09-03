#ifndef SOS_CONCEPTS_HAS_VALUE_TESTABLE_HPP
#define SOS_CONCEPTS_HAS_VALUE_TESTABLE_HPP


#include <utility>

#include <sos/concepts/bool_castable.hpp>


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
}


#endif
