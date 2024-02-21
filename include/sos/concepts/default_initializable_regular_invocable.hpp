#ifndef SOS_CONCEPTS_DEFAULT_INITIALIZABLE_REGULAR_INVOCABLE_HPP
#define SOS_CONCEPTS_DEFAULT_INITIALIZABLE_REGULAR_INVOCABLE_HPP


#include <concepts>
#include <functional>
#include <type_traits>

#include "sos/traits/is_specialization_of.hpp"


namespace sos::concepts {
    /*
        Allow an opt-out of default_initializable_regular_invocable for types that don't model it using specializations

        Note: Any specializations defined shall be usable in constant expressions and have type const bool

        Todo: Disable specializations of std::copyable_function in C++26
        Todo: Disable specializations of std::move_only_function in C++23
    */
    template<std::default_initializable F, class... Args> requires(std::regular_invocable<F, Args...>)
    inline constexpr bool disable_default_initializable_regular_invocable{
        std::is_pointer_v<F> or
        std::is_member_function_pointer_v<F> or
        detail::traits::is_specialization_of<F, std::function>
    };


    /*
        Specifies that a default initialized instance of F is safely regular invocable with Args...

        Note:
        Safely invocable is a broad term here, meaning that invoking a default initialized instance of F doesn't trigger
        undefined behaviour nor throws std::bad_function_call or any equivalent exception

        https://en.cppreference.com/w/cpp/concepts/invocable
        https://en.cppreference.com/w/cpp/concepts#Equality_preservation
        https://en.cppreference.com/w/cpp/utility/functional/bad_function_call
    */
    template<class F, class... Args> concept default_initializable_regular_invocable = (
        std::default_initializable<F> and
        std::regular_invocable<F, Args...> and
        not disable_default_initializable_regular_invocable<F, Args...>
    );

    template<class F, class... Args> concept default_initializable_predicate = (
        std::predicate<F, Args...> and
        default_initializable_regular_invocable<F, Args...>
    );
}


#endif
