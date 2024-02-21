#ifndef SOS_REQUIRE_REQUIRE_HPP
#define SOS_REQUIRE_REQUIRE_HPP


#include <utility>
#include <variant>
#include <concepts>
#include <exception>
#include <functional>

#include "sos/policy/is.hpp"
#include "sos/policy/policies.hpp"
#include "sos/policy/dynamic_policy.hpp"

#include "sos/require/is_requireable.hpp"


namespace sos {
    template<class Policy, class Predicate, class Value>
    constexpr void require(Policy const policy, Predicate const& predicate, Value const& value)
        noexcept(is_nothrow_requireable<Policy, Predicate, Value>)
        requires(is_requireable<Policy, Predicate, Value>)
    {
        if constexpr (is_trivially_requireable<Policy, Predicate, Value>) {
            return;
        }

        if constexpr (policy::dynamic_policy<Policy>) {
            return std::visit([&predicate, &value](policy::static_policy auto policy) {
                require(policy, predicate, value);
            }, policy);
        }

        if (std::invoke(predicate, value)) [[likely]] {
            return;
        }

        if constexpr (policy::is_asserts<Policy> or policy::is_aborts<Policy>) {
            std::abort();
        }
        else if constexpr (policy::is_exits<Policy>) {
            std::exit(Policy::code);
        }
        else if constexpr (policy::is_quick_exits<Policy>) {
            std::quick_exit(Policy::code);
        }
        else if constexpr (policy::is_terminates<Policy>) {
            std::terminate();
        }
        else if constexpr (policy::is_throws<Policy>) {
            throw typename Policy::exception_type{};
        }
    }
}


#endif
