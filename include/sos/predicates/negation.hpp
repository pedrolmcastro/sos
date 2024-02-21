#ifndef SOS_PREDICATES_NEGATION_HPP
#define SOS_PREDICATES_NEGATION_HPP


#include <utility>
#include <concepts>
#include <functional>
#include <type_traits>
#include <initializer_list>

#include "sos/concepts/transparent.hpp"

#include "sos/traits/view.hpp"
#include "sos/traits/make_transparent.hpp"


namespace sos::predicates {
    /*
        Specifies that T can be wrapped with negation
        Semantics: T must be a predicate to at least one set of arguments
    */
    template<class T> concept negatable = (
        std::is_object_v<T> and
        std::destructible<T> and
        not std::is_const_v<T> and
        not std::is_volatile_v<T> and
        detail::traits::is_viewable<T>
    );


    /*
        Function object wrapper to negate Predicate like the std::not_fn return type but with:
        - Value getters
        - Default construction
        - In-place construction
        - Assignment operations
        - Same transparency as the Predicate

        https://en.cppreference.com/w/cpp/utility/functional/not_fn#Return_value
    */
    template<negatable Predicate> class negation final
        : public traits::make_transparent_if<concepts::transparent<Predicate>>
    {
        public:
        using value_type = Predicate;
        using view_type = detail::traits::view<value_type>;


        explicit negation() = default;
        negation(negation&&) = default;
        negation(negation const&) = default;

        template<class U = Predicate> explicit constexpr negation(U&& predicate)
            noexcept(std::is_nothrow_constructible_v<value_type, U>)
            requires(std::constructible_from<value_type, U>)
            : m_value{std::forward<U>(predicate)}
        {}

        template<class... Args> explicit constexpr negation(std::in_place_t, Args&&... args)
            noexcept(std::is_nothrow_constructible_v<value_type, Args...>)
            requires(std::constructible_from<value_type, Args...>)
            : m_value{std::forward<Args>(args)...}
        {}

        template<class U, class... Args>
        explicit constexpr negation(std::in_place_t, std::initializer_list<U> ilist, Args&&... args)
            noexcept(std::is_nothrow_constructible_v<value_type,std::initializer_list<U>&, Args...>)
            requires(std::constructible_from<value_type, std::initializer_list<U>&, Args...>)
            : m_value{ilist, std::forward<Args>(args)...}
        {}


        negation& operator=(negation&&) = default;
        negation& operator=(negation const&) = default;

        template<class U> constexpr negation& operator=(U&& predicate)
            noexcept(std::is_nothrow_assignable_v<value_type, U>)
            requires(std::assignable_from<value_type, U>)
        {
            m_value = std::forward<U>(predicate);
            return *this;
        }


        // Todo: Specialized swap


        // Todo: Use deducing this on operator() in C++23
        // Todo: Use use static operator() where possible in C++23

        template<class... Args>
        [[nodiscard]] constexpr decltype(auto) operator()(Args&&... args) &
            noexcept(std::is_nothrow_invocable_v<value_type&, Args...>)
            requires(std::predicate<value_type&, Args...>)
        {
            return not std::invoke(m_value, std::forward<Args>(args)...);
        }

        template<class... Args>
        [[nodiscard]] constexpr decltype(auto) operator()(Args&&... args) const&
            noexcept(std::is_nothrow_invocable_v<value_type const&, Args...>)
            requires(std::predicate<value_type const&, Args...>)
        {
            return not std::invoke(m_value, std::forward<Args>(args)...);
        }

        template<class... Args>
        [[nodiscard]] constexpr decltype(auto) operator()(Args&&... args) &&
            noexcept(std::is_nothrow_invocable_v<value_type&&, Args...>)
            requires(std::predicate<value_type&&, Args...>)
        {
            return not std::invoke(std::move(m_value), std::forward<Args>(args)...);
        }

        template<class... Args>
        [[nodiscard]] constexpr decltype(auto) operator()(Args&&... args) const&&
            noexcept(std::is_nothrow_invocable_v<value_type const&&, Args...>)
            requires(std::predicate<value_type const&&, Args...>)
        {
            return not std::invoke(std::move(m_value), std::forward<Args>(args)...);
        }


        [[nodiscard]] constexpr view_type value() const& noexcept {
            return m_value;
        }

        [[nodiscard]] constexpr value_type&& value() && noexcept {
            return std::move(m_value);
        }


        private:
        value_type m_value;
    };


    template<class Predicate> [[nodiscard]] constexpr auto make_negation(Predicate&& predicate)
        noexcept(noexcept(negation<std::decay_t<Predicate>>{std::forward<Predicate>(predicate)}))
        requires requires { negation<std::decay_t<Predicate>>{std::forward<Predicate>(predicate)}; }
    {
        return negation<std::decay_t<Predicate>>{std::forward<Predicate>(predicate)};
    }

    template<negatable Predicate, class... Args>
    [[nodiscard]] constexpr auto make_negation(Args&&... args)
        noexcept(noexcept(negation<Predicate>{std::in_place, std::forward<Args>(args)...}))
        requires requires { negation<Predicate>{std::in_place, std::forward<Args>(args)...}; }
    {
        return negation<Predicate>{std::in_place, std::forward<Args>(args)...};
    }

    template<negatable Predicate, class U, class... Args>
    [[nodiscard]] constexpr auto make_negation(std::initializer_list<U> ilist, Args&&... args)
        noexcept(noexcept(negation<Predicate>{std::in_place, ilist, std::forward<Args>(args)...}))
        requires requires { negation<Predicate>{std::in_place, ilist, std::forward<Args>(args)...}; }
    {
        return negation<Predicate>{std::in_place, ilist, std::forward<Args>(args)...};
    }


    template<class Predicate> [[nodiscard]] constexpr auto not_fn(Predicate&& predicate)
        noexcept(noexcept(make_negation(std::forward<Predicate>(predicate))))
        requires requires { make_negation(std::forward<Predicate>(predicate)); }
    {
        return make_negation(std::forward<Predicate>(predicate));
    }
}


#endif
