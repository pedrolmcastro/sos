#ifndef SOS_CHECK_CHECK_HPP
#define SOS_CHECK_CHECK_HPP


#include <cassert>
#include <utility>
#include <concepts>
#include <exception>
#include <functional>

#include <sos/check/policy.hpp>
#include <sos/check/checkable.hpp>
#include <sos/check/failed_check.hpp>
#include <sos/predicates/bool_cast.hpp>


namespace sos {
    template<policy Policy, class Checked, class Predicate = bool_cast_t>
        constexpr void check(Policy, Checked&& checked, Predicate&& predicate = Predicate{})
        noexcept(nothrow_checkable<Policy, Checked, Predicate>)
        requires(checkable<Policy, Checked, Predicate>)
    {
        if constexpr (std::same_as<Policy, throws_t>) {
            if (
                not std::invoke(std::forward<Predicate>(predicate), std::forward<Checked>(checked))
            ) {
                throw failed_check{};
            }
        }

        else if constexpr (std::same_as<Policy, asserts_t>) {
            assert(std::invoke(std::forward<Predicate>(predicate), std::forward<Checked>(checked)));
        }

        else if constexpr (std::same_as<Policy, terminates_t>) {
            if (
                not std::invoke(std::forward<Predicate>(predicate), std::forward<Checked>(checked))
            ) {
                std::terminate();
            }
        }

        else {
            // No operation is performed if Policy is unenforced_t
            static_assert(std::same_as<Policy, unenforced_t>, "check called with unknown policy");
        }
    }
}


#endif
