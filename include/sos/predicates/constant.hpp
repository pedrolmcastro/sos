#ifndef SOS_PREDICATES_CONSTANT_HPP
#define SOS_PREDICATES_CONSTANT_HPP

#include <type_traits>

namespace sos::predicates {
    template<bool Value> struct [[nodiscard]] constant final {
        using type = std::bool_constant<Value>;
        using value_type = bool;

        inline static constexpr value_type value{Value};

        [[nodiscard]] explicit constexpr operator type() const noexcept {
            return {};
        }

        [[nodiscard]] explicit constexpr operator value_type() const noexcept {
            return value;
        }

        template<class... Args>
        [[nodiscard]] constexpr type operator()(Args&&...) const noexcept {
            return {};
        }
    };

    using falsy_t = constant<false>;
    inline constexpr falsy_t falsy;

    using truthy_t = constant<true>;
    inline constexpr truthy_t truthy;
}

#endif
