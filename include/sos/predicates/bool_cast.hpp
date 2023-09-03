#ifndef SOS_PREDICATES_BOOL_CAST_HPP
#define SOS_PREDICATES_BOOL_CAST_HPP


#include <utility>

#include <sos/traits/transparent.hpp>
#include <sos/concepts/bool_castable.hpp>


namespace sos {
    struct bool_cast_t final : transparent {
        template<bool_castable From>
            [[nodiscard]] constexpr bool operator()(From&& from) const
            noexcept(nothrow_bool_castable<From>)
        {
            return static_cast<bool>(std::forward<From>(from));
        }
    };

    inline constexpr bool_cast_t bool_cast{};
}


#endif
