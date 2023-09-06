#ifndef SOS_CHECK_CHECKABLE_HPP
#define SOS_CHECK_CHECKABLE_HPP


#include <concepts>
#include <type_traits>

#include <sos/check/policy.hpp>
#include <sos/traits/is_debug.hpp>
#include <sos/predicates/bool_cast.hpp>


namespace sos {
    template<class Policy, class Checked, class Predicate = bool_cast_t>
    concept noop_checkable = (
        std::same_as<Policy, unenforced_t> or
        (std::same_as<Policy, asserts_t> and not is_debug)
    );

    template<class Policy, class Checked, class Predicate = bool_cast_t>
    concept checkable = (
        noop_checkable<Policy, Checked, Predicate> or
        (policy<Policy> and std::predicate<Predicate, Checked>)
    );

    template<class Policy, class Checked, class Predicate = bool_cast_t>
    concept nothrow_checkable = (
        noop_checkable<Policy, Checked, Predicate> or
        (
            not std::same_as<Policy, throws_t> and
            checkable<Policy, Checked, Predicate> and
            std::is_nothrow_invocable_v<Predicate&&, Checked&&>
        )
    );
}


#endif
