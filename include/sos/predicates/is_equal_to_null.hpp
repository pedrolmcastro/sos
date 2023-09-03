#ifndef SOS_PREDICATES_IS_EQUAL_TO_NULL_HPP
#define SOS_PREDICATES_IS_EQUAL_TO_NULL_HPP


#include <cstddef>
#include <utility>
#include <optional>

#include <sos/concepts/null.hpp>
#include <sos/traits/transparent.hpp>
#include <sos/predicates/bool_cast.hpp>
#include <sos/traits/null_instance.hpp>
#include <sos/concepts/oneway_equality_comparable_with_null.hpp>


namespace sos {
    template<null Null> struct is_equal_to_null final : transparent {
        template<oneway_equality_comparable_with_null<Null> Compared>
            [[nodiscard]] constexpr bool operator()(Compared&& compared) const
            noexcept(nothrow_oneway_equality_comparable_with_null<Compared, Null>)
        {
            return bool_cast(std::forward<Compared>(compared) == null_instance_v<Null>);
        }
    };

    constexpr is_equal_to_null<std::nullptr_t> is_equal_to_nullptr{};
    constexpr is_equal_to_null<std::nullopt_t> is_equal_to_nullopt{};
}


#endif
