#ifndef SOS_REQUIRE_IS_REQUIREABLE_HPP
#define SOS_REQUIRE_IS_REQUIREABLE_HPP


#include <concepts>
#include <type_traits>

#include "sos/policy/is.hpp"
#include "sos/policy/policy.hpp"
#include "sos/policy/policies.hpp"
#include "sos/policy/dynamic_policy.hpp"

#include "sos/traits/is_debug_mode.hpp"


namespace sos {
    template<class Policy, class Predicate, class Value>
    inline constexpr bool is_requireable = (
        policy::policy<Policy> and std::predicate<Predicate const&, Value const&>
    );


    template<class Policy, class Predicate, class Value>
    inline constexpr bool is_trivially_requireable = (
        is_requireable<Policy, Predicate, Value> and (
            policy::is_unenforced<Policy> or
            (policy::is_asserts<Policy> and not traits::is_debug_mode)
        )
    );


    template<class Policy, class Predicate, class Value>
    inline constexpr bool is_nothrow_requireable = (
        is_trivially_requireable<Policy, Predicate, Value> or (
            not policy::is_throws<Policy> and
            not policy::dynamic_policy<Policy> and
            is_requireable<Policy, Predicate, Value> and
            std::is_nothrow_invocable_v<Predicate const&, Value const&>
        )
    );
}


#endif
