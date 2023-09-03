#ifndef SOS_CONCEPTS_ONEWAY_INEQUALITY_COMPARABLE_WITH_NULL_HPP
#define SOS_CONCEPTS_ONEWAY_INEQUALITY_COMPARABLE_WITH_NULL_HPP


#include <cstddef>
#include <utility>
#include <optional>

#include <sos/concepts/null.hpp>
#include <sos/traits/null_instance.hpp>
#include <sos/concepts/bool_castable.hpp>


namespace sos {
    template<class Lhs, class Null>
    concept oneway_inequality_comparable_with_null = null<Null> and requires(Lhs&& lhs) {
        { std::forward<Lhs>(lhs) != null_instance_v<Null> } -> bool_castable;
    };


    template<class Lhs, class Null>
    concept nothrow_oneway_inequality_comparable_with_null = (
        oneway_inequality_comparable_with_null<Lhs, Null> and
        requires(Lhs&& lhs) {
            { std::forward<Lhs>(lhs) != null_instance_v<Null> } noexcept -> nothrow_bool_castable;
        }
    );


    template<class Lhs>
    concept oneway_inequality_comparable_with_nullptr = (
        oneway_inequality_comparable_with_null<Lhs, std::nullptr_t>
    );

    template<class Lhs>
    concept nothrow_oneway_inequality_comparable_with_nullptr = (
        nothrow_oneway_inequality_comparable_with_null<Lhs, std::nullptr_t>
    );


    template<class Lhs>
    concept oneway_inequality_comparable_with_nullopt = (
        oneway_inequality_comparable_with_null<Lhs, std::nullopt_t>
    );

    template<class Lhs>
    concept nothrow_oneway_inequality_comparable_with_nullopt = (
        nothrow_oneway_inequality_comparable_with_null<Lhs, std::nullopt_t>
    );
}


#endif
