#ifndef SOS_CONSTANT_DETAIL_EVAL_HPP
#define SOS_CONSTANT_DETAIL_EVAL_HPP

#include "sos/constant/detail/warning.hpp"
#include "sos/contracts/evaluation_semantic.hpp"

#include <concepts>
#include <functional>

namespace sos::constant::detail {
    /**
     * @see https://en.cppreference.com/w/cpp/language/contracts#Handling_contract_violations
     */
    template<
        contracts::evaluation_semantic Semantic,
        auto Predicate,
        auto... Args
    >
        requires(
            std::predicate<decltype(Predicate), decltype(Args)...> and
            (Semantic == contracts::evaluation_semantic::enforce or
             Semantic == contracts::evaluation_semantic::ignore or
             Semantic == contracts::evaluation_semantic::observe or
             Semantic == contracts::evaluation_semantic::quick_enforce)
        )
    consteval void eval() noexcept {
        constexpr auto result{std::invoke(Predicate, Args...)};

        if constexpr (Semantic == contracts::evaluation_semantic::enforce or
                      Semantic == contracts::evaluation_semantic::quick_enforce)
        {
            static_assert(
                result,
                "Terminating constant evaluated contract assertion failed"
            );
        } else if constexpr (Semantic ==
                             contracts::evaluation_semantic::observe)
        {
            warning<result>();
        }
    }
}

#endif
