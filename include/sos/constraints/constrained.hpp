#ifndef SOS_CONSTRAINTS_CONSTRAINED_HPP
#define SOS_CONSTRAINTS_CONSTRAINED_HPP


#include <utility>
#include <concepts>
#include <type_traits>
#include <initializer_list>

#include "sos/concepts/default_initializable_regular_invocable.hpp"

#include "sos/policy/policy.hpp"

#include "sos/predicates/from_predicate.hpp"

#include "sos/require/require.hpp"
#include "sos/require/is_requireable.hpp"

#include "sos/traits/view.hpp"


namespace sos::constraints {
    template<class T, class Predicate> concept constrainable_with = (
        std::destructible<T> and
        std::destructible<Predicate> and
        detail::traits::is_viewable<T> and
        std::predicate<Predicate, T const&>
    );


    template<class Predicate, constrainable_with<Predicate> T> class [[nodiscard]] constrained {
    public:
        using predicate_type = Predicate;

        using value_type = T;
        using view_type = detail::traits::view<value_type>;


        constrained() = delete;

        // Todo: Check predicate after copy and move
        constrained(constrained&&) = default;
        constrained(constrained const&) = default;

        template<policy::policy Policy> explicit constexpr constrained(Policy const policy)
            noexcept(
                std::is_nothrow_default_constructible_v<value_type> and
                std::is_nothrow_default_constructible_v<predicate_type> and
                is_nothrow_requireable<Policy, predicate_type, value_type>
            )
            requires(
                std::default_initializable<value_type> and
                is_requireable<Policy, predicate_type, value_type> and
                concepts::default_initializable_predicate<predicate_type, value_type const&>
            )
            : m_value{}
        {
            require(policy, predicate_type{}, std::as_const(m_value));
        }

        template<policy::policy Policy, class U>
        constexpr constrained(Policy const policy, U&& value)
            noexcept(
                std::is_nothrow_constructible_v<value_type, U> and
                std::is_nothrow_default_constructible_v<predicate_type> and
                is_nothrow_requireable<Policy, predicate_type, value_type>
            )
            requires(
                std::constructible_from<value_type, U> and
                is_requireable<Policy, predicate_type, value_type> and
                concepts::default_initializable_predicate<predicate_type, value_type const&>
            )
            : m_value{std::forward<U>(value)}
        {
            require(policy, predicate_type{}, std::as_const(m_value));
        }

        template<policy::policy Policy>
        constexpr constrained(Policy const policy, predicates::from_predicate_t, predicate_type const& predicate)
            noexcept(
                std::is_nothrow_default_constructible_v<value_type> and
                is_nothrow_requireable<Policy, predicate_type, value_type>
            )
            requires(std::default_initializable<value_type> and is_requireable<Policy, predicate_type, value_type>)
            : m_value{}
        {
            require(policy, predicate, std::as_const(m_value));
        }

        template<policy::policy Policy, class U>
        constexpr constrained(Policy const policy, U&& value, predicate_type const& predicate)
            noexcept(
                std::is_nothrow_constructible_v<value_type, U> and
                is_nothrow_requireable<Policy, predicate_type, value_type>
            )
            requires(
                std::constructible_from<value_type, U> and
                is_requireable<Policy, predicate_type, value_type>
            )
            : m_value{std::forward<U>(value)}
        {
            require(policy, predicate, std::as_const(m_value));
        }

        template<policy::policy Policy, class... Args>
        constexpr constrained(Policy const policy, std::in_place_t, Args&&... args)
            noexcept(
                std::is_nothrow_constructible_v<value_type, Args...> and
                std::is_nothrow_default_constructible_v<predicate_type> and
                is_nothrow_requireable<Policy, predicate_type, value_type>
            )
            requires(
                std::constructible_from<value_type, Args...> and
                is_requireable<Policy, predicate_type, value_type> and
                concepts::default_initializable_predicate<predicate_type, value_type const&>
            )
            : m_value{std::forward<Args>(args)...}
        {
            require(policy, predicate_type{}, std::as_const(m_value));
        }

        template<policy::policy Policy, class U, class... Args>
        constexpr constrained(Policy const policy, std::in_place_t, std::initializer_list<U> ilist, Args&&... args)
            noexcept(
                std::is_nothrow_default_constructible_v<predicate_type> and
                is_nothrow_requireable<Policy, predicate_type, value_type> and
                std::is_nothrow_constructible_v<value_type, std::initializer_list<U>&, Args...>
            )
            requires(
                is_requireable<Policy, predicate_type, value_type> and
                std::constructible_from<value_type, std::initializer_list<U>&, Args...> and
                concepts::default_initializable_predicate<predicate_type, value_type const&>
            )
            : m_value{ilist, std::forward<Args>(args)...}
        {
            require(policy, predicate_type{}, std::as_const(m_value));
        }


        // Todo: Specialized swap
        // Todo: Assignment operators


        // Todo: Functor/monadic member functions


        [[nodiscard]] constexpr view_type value() const& noexcept {
            return m_value;
        }

        [[nodiscard]] constexpr value_type&& value() && noexcept {
            return std::move(m_value);
        }


    private:
        value_type m_value;
    };


    // Todo: factory functions
}


#endif
