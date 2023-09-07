#ifndef SOS_PREDICATES_IS_NOT_NULL_HPP
#define SOS_PREDICATES_IS_NOT_NULL_HPP


#include <cstddef>
#include <utility>
#include <optional>

#include <sos/traits/transparent.hpp>
#include <sos/predicates/bool_cast.hpp>
#include <sos/traits/null_instance.hpp>


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


    template<null Null> struct is_not_null final : transparent {
        template<oneway_inequality_comparable_with_null<Null> Compared>
        [[nodiscard]] constexpr bool operator()(Compared&& compared) const
            noexcept(nothrow_oneway_inequality_comparable_with_null<Compared, Null>)
        {
            return bool_cast(std::forward<Compared>(compared) != null_instance_v<Null>);
        }
    };

    inline constexpr is_not_null<std::nullptr_t> is_not_nullptr{};
    inline constexpr is_not_null<std::nullopt_t> is_not_nullopt{};
}


#endif
